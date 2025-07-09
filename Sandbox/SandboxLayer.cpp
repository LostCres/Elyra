#include "SandboxLayer.hpp"
 #define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

SandboxLayer::SandboxLayer()
    : Layer("Sandbox"), m_CameraController(45.0f, 1280.0f / 720.0f, 0.01f, 100.0f) {}        //m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)

void SandboxLayer::OnAttach() {

    m_Cube = Elyra::CubeMesh::Create();
    
    m_Shader = Elyra::Shader::Create("shaders/Cube.vert","shaders/Cube.frag");
}

void SandboxLayer::OnDetach() {
    // Cleanup if needed
}

void SandboxLayer::OnUpdate(Elyra::TimeStep ts) {

    m_CameraController.OnUpdate(ts);
    Elyra::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Elyra::RenderCommand::Clear();

    Elyra::Renderer::BeginScene(m_CameraController.GetCamera());
    m_CameraController.SetSpeed(speed);
    m_Campos = m_CameraController.GetCamera().GetPosition();

    glm::mat4 transform = glm::mat4(1.0f);
    Elyra::Renderer::Submit(m_Shader, m_Cube, transform);

    Elyra::Renderer::EndScene();
}

void SandboxLayer::OnEvent(Elyra::Event& event) {
    m_CameraController.OnEvent(event);  // <--- forward events

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
    Elyra::UI::BeginPanel("Camera");
    Elyra::UI::SliderFloat("Move speed", &speed, 1.0f, 10.0f);
    Elyra::UI::Text("Pos: " + glm::to_string(m_Campos));
    Elyra::UI::EndPanel();

}
