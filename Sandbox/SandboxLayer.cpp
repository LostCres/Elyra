#include "SandboxLayer.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SandboxLayer::SandboxLayer()
    : Layer("Sandbox"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {}

void SandboxLayer::OnAttach() {
    m_VertexArray = Elyra::VertexArray::Create();

    float vertices[3 * 3] = {
        0.0f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f,
       -0.5f,  0.5f, 0.0f
    };

    Elyra::Ref<Elyra::VertexBuffer> vertexBuffer;
    vertexBuffer = Elyra::VertexBuffer::Create(vertices, sizeof(vertices));

    Elyra::BufferLayout layout = {
        { Elyra::ShaderDataType::Float3, "a_Position" }
    };
    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t indices[3] = { 0, 1, 2 };
    Elyra::Ref<Elyra::IndexBuffer> indexBuffer;
    indexBuffer = Elyra::IndexBuffer::Create(indices, 3);
    m_VertexArray->SetIndexBuffer(indexBuffer);

    std::string vertexSrc = R"(
        #version 330 core
        layout(location = 0) in vec3 a_Position;
        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;
        void main() {
            gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
        }
    )";

    std::string fragmentSrc = R"(
        #version 330 core
        out vec4 color;
        void main() {
            color = vec4(1.0, 0.3, 0.6, 1.0);
        }
    )";

    m_Shader = Elyra::Shader::Create("Simple", vertexSrc, fragmentSrc);
}

void SandboxLayer::OnDetach() {
    // Cleanup if needed
}

void SandboxLayer::OnUpdate(Elyra::TimeStep ts) {
    Elyra::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Elyra::RenderCommand::Clear();

    if (Elyra::Input::IsKeyPressed(Elyra::Key_W)) {
        EL_WARN("TAB key is pressed!");
    }

    Elyra::Renderer::BeginScene(m_Camera);

    glm::mat4 transform = glm::mat4(1.0f);
    Elyra::Renderer::Submit(m_Shader, m_VertexArray, transform);

    Elyra::Renderer::EndScene();
}

void SandboxLayer::OnEvent(Elyra::Event& event) {
    if (event.GetEventType() == Elyra::EventType::KeyPressed)
    {
        Elyra::KeyPressedEvent& keyEvent = static_cast<Elyra::KeyPressedEvent&>(event);
        EL_INFO("KeyPressed: {}",static_cast<int>(keyEvent.GetKeyCode()));
    }

    if (event.GetEventType() == Elyra::EventType::MouseButtonPressed)
    {
        Elyra::MouseButtonPressedEvent& mouseEvent = static_cast<Elyra::MouseButtonPressedEvent&>(event);
        EL_INFO("MouseButtonPressed: {}", static_cast<int>(mouseEvent.GetMouseButton()));
    }
}

void SandboxLayer::OnUIRender()
{
    Elyra::UI::BeginPanel("Controls");

    static bool enabled = true;
    static float size = 0.5f;
    static std::string name = "Elyra";

    Elyra::UI::Text("Hello, " + name);
    Elyra::UI::Checkbox("Enable feature", &enabled);
    Elyra::UI::SliderFloat("Size", &size, 0.0f, 1.0f);
    Elyra::UI::InputText("Name", name);
    if (Elyra::UI::Button("Click Me"))
    {
        EL_INFO("Button clicked with name: {}", name);
    }

    Elyra::UI::EndPanel();

}
