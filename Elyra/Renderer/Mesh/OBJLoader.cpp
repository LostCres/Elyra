#include "Elyrapch.hpp"
#include <glm/glm.hpp>
#include "Renderer/Mesh/OBJLoader.hpp"
#include "Core/Log.hpp"

namespace Elyra {

    // -----------------------------------------------------------------------
    // Internal vertex key for deduplication
    // -----------------------------------------------------------------------
    struct OBJVertexKey {
        int posIdx, uvIdx, normIdx;

        bool operator==(const OBJVertexKey& o) const {
            return posIdx == o.posIdx && uvIdx == o.uvIdx && normIdx == o.normIdx;
        }
    };

    struct OBJVertexKeyHash {
        std::size_t operator()(const OBJVertexKey& k) const {
            // Simple packed hash
            std::size_t h = (std::size_t)(k.posIdx  + 1) * 73856093;
            h ^= (std::size_t)(k.uvIdx   + 1) * 19349663;
            h ^= (std::size_t)(k.normIdx + 1) * 83492791;
            return h;
        }
    };

    // -----------------------------------------------------------------------
    // Helpers
    // -----------------------------------------------------------------------

    // Parse "a/b/c", "a//c", "a/b", or "a" into (pos, uv, norm) 1-based indices.
    // Missing indices stay as 0 (we remap to -1 internally for "no uv/norm").
    static bool ParseFaceVertex(const std::string& token, int& pos, int& uv, int& norm) {
        pos = uv = norm = 0;
        std::istringstream ss(token);
        std::string part;

        // position
        if (!std::getline(ss, part, '/')) return false;
        if (!part.empty()) pos = std::stoi(part);

        // uv (optional)
        if (std::getline(ss, part, '/')) {
            if (!part.empty()) uv = std::stoi(part);
            // normal (optional)
            if (std::getline(ss, part, '/')) {
                if (!part.empty()) norm = std::stoi(part);
            }
        }
        return pos != 0;
    }

    // Resolve 1-based (or negative) OBJ index to 0-based.
    static int Resolve(int idx, int total) {
        if (idx > 0) return idx - 1;
        if (idx < 0) return total + idx;
        return -1; // missing
    }

    // -----------------------------------------------------------------------
    // OBJLoader::Load
    // -----------------------------------------------------------------------
    Ref<Mesh> OBJLoader::Load(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            EL_CORE_ERROR("OBJLoader: Cannot open file '{}'", filepath);
            return nullptr;
        }

        std::vector<glm::vec3> rawPositions;
        std::vector<glm::vec2> rawUVs;
        std::vector<glm::vec3> rawNormals;

        // Final interleaved output: [px,py,pz, nx,ny,nz, u,v]
        std::vector<float>    vertices;
        std::vector<uint32_t> indices;

        // Map unique (pos/uv/norm) combo → index in vertices[]
        std::unordered_map<OBJVertexKey, uint32_t, OBJVertexKeyHash> vertexCache;

        bool hasNormals = false;
        bool hasUVs     = false;

        std::string line;
        while (std::getline(file, line)) {
            // Strip carriage return (Windows line endings)
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty() || line[0] == '#') continue;

            std::istringstream ss(line);
            std::string prefix;
            ss >> prefix;

            if (prefix == "v") {
                glm::vec3 p;
                ss >> p.x >> p.y >> p.z;
                rawPositions.push_back(p);
            }
            else if (prefix == "vt") {
                glm::vec2 uv;
                ss >> uv.x >> uv.y;
                uv.y = 1.0f - uv.y; // Flip V — OBJ is top-left, OpenGL is bottom-left
                rawUVs.push_back(uv);
                hasUVs = true;
            }
            else if (prefix == "vn") {
                glm::vec3 n;
                ss >> n.x >> n.y >> n.z;
                rawNormals.push_back(n);
                hasNormals = true;
            }
            else if (prefix == "f") {
                // Collect all face vertex tokens and triangulate as a fan
                std::vector<std::string> tokens;
                std::string tok;
                while (ss >> tok) tokens.push_back(tok);

                if (tokens.size() < 3) continue;

                // Fan triangulation: (0,1,2), (0,2,3), (0,3,4) …
                for (size_t i = 1; i + 1 < tokens.size(); ++i) {
                    std::string corners[3] = { tokens[0], tokens[i], tokens[i + 1] };

                    for (const auto& corner : corners) {
                        int pi, ti, ni;
                        if (!ParseFaceVertex(corner, pi, ti, ni)) {
                            EL_CORE_WARN("OBJLoader: Skipping malformed face token '{}'", corner);
                            continue;
                        }

                        int posI  = Resolve(pi, (int)rawPositions.size());
                        int uvI   = Resolve(ti, (int)rawUVs.size());
                        int normI = Resolve(ni, (int)rawNormals.size());

                        OBJVertexKey key{ posI, uvI, normI };

                        auto it = vertexCache.find(key);
                        if (it != vertexCache.end()) {
                            indices.push_back(it->second);
                        } else {
                            uint32_t newIdx = static_cast<uint32_t>(vertices.size() / 8);

                            // Position
                            glm::vec3 pos = (posI >= 0 && posI < (int)rawPositions.size())
                                ? rawPositions[posI] : glm::vec3(0.0f);
                            // Normal
                            glm::vec3 nor = (normI >= 0 && normI < (int)rawNormals.size())
                                ? rawNormals[normI] : glm::vec3(0.0f, 1.0f, 0.0f);
                            // UV
                            glm::vec2 uv = (uvI >= 0 && uvI < (int)rawUVs.size())
                                ? rawUVs[uvI] : glm::vec2(0.0f);

                            vertices.insert(vertices.end(), {
                                pos.x, pos.y, pos.z,
                                nor.x, nor.y, nor.z,
                                uv.x,  uv.y
                            });

                            vertexCache[key] = newIdx;
                            indices.push_back(newIdx);
                        }
                    }
                }
            }
            // Other tokens (mtllib, usemtl, s, o, g) are silently ignored
        }

        if (vertices.empty() || indices.empty()) {
            EL_CORE_ERROR("OBJLoader: No geometry found in '{}'", filepath);
            return nullptr;
        }

        EL_CORE_INFO("OBJLoader: Loaded '{}' — {} vertices, {} triangles{}{}",
            filepath,
            vertices.size() / 8,
            indices.size() / 3,
            hasNormals ? "" : " [normals missing, using up]",
            hasUVs     ? "" : " [UVs missing, using 0,0]");

        return Mesh::Create(vertices, indices);
    }

} // namespace Elyra
