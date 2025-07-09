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
        // Front face
        -w, -h,  d,   0, 0, 1,    0, 0,
         w, -h,  d,   0, 0, 1,    1, 0,
         w,  h,  d,   0, 0, 1,    1, 1,
        -w,  h,  d,   0, 0, 1,    0, 1,
        // Back face
        -w, -h, -d,   0, 0, -1,   1, 0,
         w, -h, -d,   0, 0, -1,   0, 0,
         w,  h, -d,   0, 0, -1,   0, 1,
        -w,  h, -d,   0, 0, -1,   1, 1
    };

    std::vector<uint32_t> indices = {
        // Front
        0, 1, 2, 2, 3, 0,
        // Back
        4, 5, 6, 6, 7, 4,
        // Left
        4, 0, 3, 3, 7, 4,
        // Right
        1, 5, 6, 6, 2, 1,
        // Top
        3, 2, 6, 6, 7, 3,
        // Bottom
        4, 5, 1, 1, 0, 4
    };

    return Mesh::Create(vertices, indices);
}

Ref<Mesh> Plane(float width, float length) {
    const float w = width * 0.5f;
    const float l = length * 0.5f;
    std::vector<float> vertices = {
        // Position         // Normal       // UV
        -w, 0.0f, -l,   0, 1, 0,     0, 0,
         w, 0.0f, -l,   0, 1, 0,     1, 0,
         w, 0.0f,  l,   0, 1, 0,     1, 1,
        -w, 0.0f,  l,   0, 1, 0,     0, 1
    };

    std::vector<uint32_t> indices = {
        0, 1, 2, 2, 3, 0
    };

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
