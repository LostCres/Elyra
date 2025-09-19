#include "Primitives.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace Elyra::Primitives {

Ref<Mesh> Cube(float width, float height, float depth) {
    // position (3) + normal (3) + uv (2) = 8 floats per vertex
    const float w = width * 0.5f;
    const float h = height * 0.5f;
    const float d = depth * 0.5f;

     std::vector<float> vertices = {
        // Front
        -w, -h,  d,   0, 0, 1,   0, 0,
         w, -h,  d,   0, 0, 1,   1, 0,
         w,  h,  d,   0, 0, 1,   1, 1,
        -w,  h,  d,   0, 0, 1,   0, 1,

        // Back
         w, -h, -d,   0, 0, -1,   0, 0,
        -w, -h, -d,   0, 0, -1,   1, 0,
        -w,  h, -d,   0, 0, -1,   1, 1,
         w,  h, -d,   0, 0, -1,   0, 1,

        // Left
        -w, -h, -d,  -1, 0, 0,   0, 0,
        -w, -h,  d,  -1, 0, 0,   1, 0,
        -w,  h,  d,  -1, 0, 0,   1, 1,
        -w,  h, -d,  -1, 0, 0,   0, 1,

        // Right
         w, -h,  d,   1, 0, 0,   0, 0,
         w, -h, -d,   1, 0, 0,   1, 0,
         w,  h, -d,   1, 0, 0,   1, 1,
         w,  h,  d,   1, 0, 0,   0, 1,

        // Top
        -w,  h,  d,   0, 1, 0,   0, 0,
         w,  h,  d,   0, 1, 0,   1, 0,
         w,  h, -d,   0, 1, 0,   1, 1,
        -w,  h, -d,   0, 1, 0,   0, 1,

        // Bottom
        -w, -h, -d,   0, -1, 0,   0, 0,
         w, -h, -d,   0, -1, 0,   1, 0,
         w, -h,  d,   0, -1, 0,   1, 1,
        -w, -h,  d,   0, -1, 0,   0, 1
    };

    std::vector<uint32_t> indices = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Back face
        4, 5, 6, 6, 7, 4,
        // Left face
        8, 9,10,10,11, 8,
        // Right face
       12,13,14,14,15,12,
        // Top face
       16,17,18,18,19,16,
        // Bottom face
       20,21,22,22,23,20
    };


    return Mesh::Create(vertices, indices);
}

std::pair<std::vector<float>, std::vector<uint32_t>> GeneratePlaneData(float width, float length) {
    const float w = width * 0.5f;
    const float l = length * 0.5f;
    std::vector<float> vertices = {
        -w, 0.0f, -l,   0, 1, 0,     0, 0,
         w, 0.0f, -l,   0, 1, 0,     1, 0,
         w, 0.0f,  l,   0, 1, 0,     1, 1,
        -w, 0.0f,  l,   0, 1, 0,     0, 1
    };
    std::vector<uint32_t> indices = { 0, 1, 2, 2, 3, 0 };
    return {vertices, indices};
}

Ref<Mesh> Plane(float width, float length) {
    auto [vertices, indices] = GeneratePlaneData(width, length);
    return Mesh::Create(vertices, indices);
}

Ref<Mesh> Sphere(float radius, uint32_t segments, uint32_t rings) {
    std::vector<float> vertices;
    std::vector<uint32_t> indices;

    for (uint32_t y = 0; y <= rings; ++y) {
        for (uint32_t x = 0; x <= segments; ++x) {
            float xSegment = (float)x / segments;
            float ySegment = (float)y / rings;
            float xPos = radius * std::cos(xSegment * 2.0f * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>());
            float yPos = radius * std::cos(ySegment * glm::pi<float>());
            float zPos = radius * std::sin(xSegment * 2.0f * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>());

            glm::vec3 normal = glm::normalize(glm::vec3(xPos, yPos, zPos));
            vertices.insert(vertices.end(), {
                xPos, yPos, zPos,
                normal.x, normal.y, normal.z,
                xSegment, ySegment
            });
        }
    }

    for (uint32_t y = 0; y < rings; ++y) {
        for (uint32_t x = 0; x < segments; ++x) {
            uint32_t i0 = y * (segments + 1) + x;
            uint32_t i1 = i0 + segments + 1;

            indices.push_back(i0);
            indices.push_back(i1);
            indices.push_back(i0 + 1);

            indices.push_back(i0 + 1);
            indices.push_back(i1);
            indices.push_back(i1 + 1);
        }
    }

    return Mesh::Create(vertices, indices);
}

}
