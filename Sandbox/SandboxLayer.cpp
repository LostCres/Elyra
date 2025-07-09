#include "SandboxLayer.hpp"
 #define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

SandboxLayer::SandboxLayer()
    : Layer("Sandbox") {}

void SandboxLayer::OnAttach() {

}

void SandboxLayer::OnDetach() {
    // Cleanup if needed
}

void SandboxLayer::OnUpdate(Elyra::TimeStep ts) {
    
}

void SandboxLayer::OnEvent(Elyra::Event& event) {

    if (event.GetEventType() == Elyra::EventType::KeyPressed)
    {
        Elyra::KeyPressedEvent& keyEvent = static_cast<Elyra::KeyPressedEvent&>(event);
        EL_INFO("KeyPressed: {}", static_cast<int>(keyEvent.GetKeyCode()));
    }

    if (event.GetEventType() == Elyra::EventType::MouseButtonPressed)
    {
        Elyra::MouseButtonPressedEvent& mouseEvent = static_cast<Elyra::MouseButtonPressedEvent&>(event);
        EL_INFO("MouseButtonPressed: {}", static_cast<int>(mouseEvent.GetMouseButton()));
    }
}

void SandboxLayer::OnUIRender()
{

}
