#pragma once
#include "Elyrapch.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ElyraAPI.hpp"
#include "Core/Core.hpp"
#include "Renderer/Mesh/Mesh.hpp"
#include "Renderer/Shader/Shader.hpp"
#include "Renderer/Camera/PerspectiveCamera.hpp"
#include "Renderer/Camera/PerspectiveCameraController.hpp"
#include "Renderer/Material/Material.hpp"
#include "Script/ScriptableEntity.hpp"

namespace Elyra {

    struct ELYRA_API TagComponent {
        std::string Tag;
        TagComponent() = default;
        TagComponent(const std::string tag) : Tag(std::move(tag)) {}
    };

    struct ELYRA_API ScriptableComponent {
        ScriptableEntity* Instance = nullptr;

        ScriptableEntity* (*InstantiateScript)();
        void (*DestroyScript)(ScriptableComponent*);

        template<typename T>
        void Bind() {
            InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
            DestroyScript = [](ScriptableComponent* comp) {
                delete comp->Instance;
                comp->Instance = nullptr;
            };
        }
    };

    struct ELYRA_API TransformComponent {
        glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Scale    = { 1.0f, 1.0f, 1.0f };

        TransformComponent() = default;
        TransformComponent(const glm::vec3& position)
            : Position(position) {}

        glm::mat4 GetTransform() const {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position);
            transform = glm::rotate(transform, Rotation.x, {1, 0, 0});
            transform = glm::rotate(transform, Rotation.y, {0, 1, 0});
            transform = glm::rotate(transform, Rotation.z, {0, 0, 1});
            return glm::scale(transform, Scale);
        }
    };

    struct ELYRA_API CameraComponent
    {
        PerspectiveCamera Camera;
        bool Primary = false;

        // Default: a sensible 45° FOV, 16:9 aspect, 0.1–100 clip range
        CameraComponent()
            : Camera(45.0f, 16.0f / 9.0f, 0.1f, 100.0f) {}

        // Custom configuration
        CameraComponent(float fovY, float aspect, float nearClip, float farClip,
                        bool primary = false)
            : Camera(fovY, aspect, nearClip, farClip), Primary(primary) {}
    };

    struct ELYRA_API CameraControllerComponent
    {
        PerspectiveCameraController Controller;

        CameraControllerComponent() = default;
    };


    struct MeshComponent {
        Ref<Mesh> MeshData;

        MeshComponent() = default;
        MeshComponent(const Ref<Mesh>& mesh)
            : MeshData(mesh) {}
    };

    struct ShaderComponent {
        Ref<Shader> ShaderData;

        ShaderComponent() = default;
        ShaderComponent(const Ref<Shader>& shader)
            : ShaderData(shader) {}
    };

    struct MaterialComponent {
        Ref<Material> MaterialData;

        MaterialComponent() = default;
        MaterialComponent(const Ref<Material>& material)
            : MaterialData(material) {}
    };
    
}