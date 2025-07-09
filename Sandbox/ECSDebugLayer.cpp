#include "ECSDebugLayer.hpp"
#include "Elyra.hpp"

ECSDebugLayer::ECSDebugLayer() : Layer("ECSDebugLayer") {}

void ECSDebugLayer::OnAttach() {
    m_Scene = Elyra::SceneManager::GetActiveScene();
    m_TestEntity = m_Scene->GetEntityByName("Cube");
}

void ECSDebugLayer::OnUpdate(Elyra::TimeStep ts) {
    
}

void ECSDebugLayer::OnUIRender() {
    Elyra::UI::BeginPanel("ECS Debug");

    auto& transform = m_TestEntity.GetComponent<Elyra::TransformComponent>();
    Elyra::UI::Text("Entity ID: " + std::to_string(m_TestEntity.GetID()));
    Elyra::UI::Text("Position: (" + std::to_string(transform.Position.x) + ", " +
                     std::to_string(transform.Position.y) + ", " +
                     std::to_string(transform.Position.z) + ")");
    Elyra::UI::Text("Rotation: (" + std::to_string(transform.Rotation.x) + ", " +
                     std::to_string(transform.Rotation.y) + ", " +
                     std::to_string(transform.Rotation.z) + ")");
    Elyra::UI::EndPanel();
}
