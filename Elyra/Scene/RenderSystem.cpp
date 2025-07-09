#include "Scene/RenderSystem.hpp"
#include "ECS/Component.hpp"
#include "Renderer/Core/Renderer.hpp"
#include "Scene/Scene.hpp"

namespace Elyra {

void RenderSystem::OnRender(Scene* scene)
{
    Entity cameraEntity = scene->GetActiveCamera();
    if (!cameraEntity)
        return;

    auto& camComp = scene->GetComponent<CameraComponent>(cameraEntity);
    auto& camera = camComp.Camera;

    Renderer::BeginScene(camera);

    for (auto& entity : scene->GetAllEntities())
    {
        if (   entity.HasComponent<TransformComponent>()
            && entity.HasComponent<MeshComponent>()
            && entity.HasComponent<MaterialComponent>())
        {
            auto& transform = entity.GetComponent<TransformComponent>();
            auto& meshComp  = entity.GetComponent<MeshComponent>();
            auto& matComp   = entity.GetComponent<MaterialComponent>();
            Elyra::Renderer::Submit(
                matComp.MaterialData,
                meshComp.MeshData->GetVertexArray(),
                transform.GetTransform()
            );
        }
    }

    Renderer::EndScene();
}

}
