#include "Scene/CameraSystem.hpp"
#include "ECS/Component.hpp"
#include "Scene/Scene.hpp"

namespace Elyra {

void CameraSystem::OnUpdate(Scene* scene, TimeStep ts)
{
    Entity activeCamera = scene->GetActiveCamera();

    if (!scene->HasComponent<CameraComponent>(activeCamera) ||
        !scene->HasComponent<CameraControllerComponent>(activeCamera) ||
        !scene->HasComponent<TransformComponent>(activeCamera))
        return;

    auto& cam = scene->GetComponent<CameraComponent>(activeCamera);
    auto& ctrl = scene->GetComponent<CameraControllerComponent>(activeCamera);
    auto& transform = scene->GetComponent<TransformComponent>(activeCamera);

    ctrl.Controller.OnUpdate(ts);

    transform.Position = cam.Camera.GetPosition();
    transform.Rotation = cam.Camera.GetRotation();
    cam.Camera.SetPosition(transform.Position);
    cam.Camera.SetRotation(transform.Rotation);
}

void CameraSystem::OnViewportResize(Scene* scene, uint32_t width, uint32_t height)
{
    Entity activeCamera = scene->GetActiveCamera();
    if (!scene->HasComponent<CameraComponent>(activeCamera));
        return;
    auto& cam = scene->GetComponent<CameraComponent>(activeCamera);
    cam.Camera.SetViewportSize(width, height);
}

void CameraSystem::OnEvent(Scene* scene, Event& e)
{
     Entity activeCamera = scene->GetActiveCamera();

    if (!scene->HasComponent<CameraComponent>(activeCamera) ||
        !scene->HasComponent<CameraControllerComponent>(activeCamera))
        return;

    auto& ctrl = scene->GetComponent<CameraControllerComponent>(activeCamera);
    ctrl.Controller.OnEvent(e);
}

}
