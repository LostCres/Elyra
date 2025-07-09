#include "ECSDebugLayer.hpp"
#include "Elyra.hpp"

ECSDebugLayer::ECSDebugLayer() : Layer("ECSDebugLayer") {}

void ECSDebugLayer::OnAttach() {
    m_Scene = Elyra::SceneManager::GetActiveScene();
}

void ECSDebugLayer::OnUpdate(Elyra::TimeStep ts) {
    
}

void ECSDebugLayer::OnUIRender() {
    Elyra::UI::BeginPanel("Camera");
    for (auto& entity : m_Scene->GetAllEntities())
    {
        if(entity.HasComponent<Elyra::CameraComponent>())
        {
            auto& transform = entity.GetComponent<Elyra::TransformComponent>();
            Elyra::UI::Text("Camera: " + entity.GetComponent<Elyra::TagComponent>().Tag);
            Elyra::UI::Text("Position: (" + std::to_string(transform.Position.x) + ", " +
                            std::to_string(transform.Position.y) + ", " +
                            std::to_string(transform.Position.z) + ")");
            Elyra::UI::Text("Rotation: (" + std::to_string(transform.Rotation.x) + ", " +
                            std::to_string(transform.Rotation.y) + ", " +
                            std::to_string(transform.Rotation.z) + ")"); 
        }
         
    }

    Elyra::UI::EndPanel();
}
