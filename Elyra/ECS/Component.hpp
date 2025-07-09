#pragma once
#include "Elyrapch.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ElyraAPI.hpp"
#include "Renderer/Mesh/Mesh.hpp"
#include "Renderer/Shader.hpp"

namespace Elyra {

    struct ELYRA_API TagComponent {
        std::string Tag;
        TagComponent() = default;
        TagComponent(const std::string tag) : Tag(std::move(tag)) {}
    };

    struct ELYRA_API TransformComponent {
        glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Scale    = { 1.0f, 1.0f, 1.0f };

        TransformComponent() = default;
        TransformComponent(const glm::vec3& position)
            : Position(position) {}

        glm::mat4 GetTransform() const {
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, { 1, 0, 0 })
                               * glm::rotate(glm::mat4(1.0f), Rotation.y, { 0, 1, 0 })
                               * glm::rotate(glm::mat4(1.0f), Rotation.z, { 0, 0, 1 });

            return glm::translate(glm::mat4(1.0f), Position)
                 * rotation
                 * glm::scale(glm::mat4(1.0f), Scale);
        }
    };

    struct MeshComponent {
        std::shared_ptr<Mesh> MeshData;

        MeshComponent() = default;
        MeshComponent(const std::shared_ptr<Mesh>& mesh)
            : MeshData(mesh) {}
    };

    struct MaterialComponent {
        std::shared_ptr<Shader> ShaderData;

        MaterialComponent() = default;
        MaterialComponent(const std::shared_ptr<Shader>& shader)
            : ShaderData(shader) {}
    };
    
}