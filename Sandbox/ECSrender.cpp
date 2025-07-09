#include "ECSrender.hpp"
 #define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

ECSrender::ECSrender()
    : Layer("Sandbox"), m_CameraController(45.0f, 1280.0f / 720.0f, 0.01f, 100.0f) {}        //m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)

void ECSrender::OnAttach() {

    auto cubeMesh = Elyra::Primitives::Cube();
    auto sphereMesh = Elyra::Primitives::Sphere();  
    auto cubeShader = Elyra::Shader::Create("Assets/shaders/Cube.vert","Assets/shaders/Cube.frag");

    // Simulate ECS: create a cube entity with components
    m_Scene = std::make_shared<Elyra::Scene>();
    Elyra::SceneManager::SetActiveScene(m_Scene);

    auto cube = m_Scene->CreateEntity("Cube");
    cube.GetComponent<Elyra::MeshComponent>().MeshData      = cubeMesh;
    cube.GetComponent<Elyra::MaterialComponent>().ShaderData  = cubeShader;
    cube.GetComponent<Elyra::TransformComponent>().Position = { 0.0f, 0.0f, 0.0f };

    auto sphere = m_Scene->CreateEntity("Sphere");
    sphere.GetComponent<Elyra::MeshComponent>().MeshData = sphereMesh;
    sphere.GetComponent<Elyra::MaterialComponent>().ShaderData = cubeShader;
    sphere.GetComponent<Elyra::TransformComponent>().Position = {0.0f, 2.0f,0.0f};
}

void ECSrender::OnDetach() {
    // Cleanup if needed
}

void ECSrender::OnUpdate(Elyra::TimeStep ts) {

    m_CameraController.OnUpdate(ts);
    Elyra::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Elyra::RenderCommand::Clear();

    Elyra::Renderer::BeginScene(m_CameraController.GetCamera());
    m_CameraController.SetSpeed(speed);
    m_Campos = m_CameraController.GetCamera().GetPosition();

    for (auto& entity : m_Scene->GetAllEntities())
    {
        if (   entity.HasComponent<Elyra::TransformComponent>()
            && entity.HasComponent<Elyra::MeshComponent>()
            && entity.HasComponent<Elyra::MaterialComponent>())
        {
            auto& transform = entity.GetComponent<Elyra::TransformComponent>();
            auto& meshComp  = entity.GetComponent<Elyra::MeshComponent>();
            auto& matComp   = entity.GetComponent<Elyra::MaterialComponent>();

            Elyra::Renderer::Submit(
                matComp.ShaderData,
                meshComp.MeshData->GetVertexArray(),
                transform.GetTransform()
            );
        }
    }

    m_Scene->GetEntityByName("Cube").GetComponent<Elyra::TransformComponent>().Rotation.y += ts * glm::radians(90.0f);

    Elyra::Renderer::EndScene();
}

void ECSrender::OnEvent(Elyra::Event& event) {
    m_CameraController.OnEvent(event);  // <--- forward events

    if (event.GetEventType() == Elyra::EventType::WindowResize)
    {
        Elyra::WindowResizeEvent& Size = static_cast<Elyra::WindowResizeEvent&>(event);
        auto width = static_cast<uint32_t>(Size.GetWidth());
        auto height = static_cast<uint32_t>(Size.GetHeight());
        Elyra::Renderer::OnWindowResize(width,height);
        m_CameraController.OnResize((float)Size.GetWidth(),(float)Size.GetHeight());
    }
}

void ECSrender::OnUIRender()
{
    Elyra::UI::BeginPanel("Camera");
    Elyra::UI::SliderFloat("Move speed", &speed, 1.0f, 10.0f);
    Elyra::UI::Text("Pos: " + glm::to_string(m_Campos));
    Elyra::UI::EndPanel();

}
