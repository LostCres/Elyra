#include "Scene/RenderSystem.hpp"
#include "ECS/Component.hpp" // Changed from Components.hpp to Component.hpp
#include "Renderer/Core/Renderer.hpp"
#include "Scene/Scene.hpp"
namespace Elyra {

    void RenderSystem::OnRender(Scene* scene) {
        auto camera = scene->GetActiveCamera();
        if (!camera.HasComponent<CameraComponent>()) {
            return;
        }

        auto& cameraComponent = camera.GetComponent<CameraComponent>();
        Renderer::BeginScene(cameraComponent.Camera);        
        for (auto& entity : scene->GetAllEntities()) {
            if (entity.HasComponent<MeshComponent>() && entity.HasComponent<MaterialComponent>()) {
                auto& mesh = entity.GetComponent<MeshComponent>();
                auto& material = entity.GetComponent<MaterialComponent>();
                auto& transform = entity.GetComponent<TransformComponent>();

                if (mesh.MeshData && material.MaterialData) {
                    material.MaterialData->Bind();
                    Renderer::Submit(material.MaterialData, mesh.MeshData->GetVertexArray(), transform.GetTransform());
                }
            }
        }
        Renderer::EndScene();
    }

}
