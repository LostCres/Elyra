#include "ECSrender.hpp"
 #define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

ECSrender::ECSrender()
    : Layer("Sandbox"), m_CameraController(45.0f, 1280.0f / 720.0f, 0.01f, 100.0f) {}        //m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)

void ECSrender::OnAttach() {

    static std::vector<float> cubeVertices = {
        // Position          // Normal        // TexCoord
        -0.5f, -0.5f, -0.5f,  0.f, 0.f, -1.f,  0.f, 0.f,
        0.5f, -0.5f, -0.5f,  0.f, 0.f, -1.f,  1.f, 0.f,
        0.5f,  0.5f, -0.5f,  0.f, 0.f, -1.f,  1.f, 1.f,
        -0.5f,  0.5f, -0.5f,  0.f, 0.f, -1.f,  0.f, 1.f,

        -0.5f, -0.5f,  0.5f,  0.f, 0.f, 1.f,   0.f, 0.f,
        0.5f, -0.5f,  0.5f,  0.f, 0.f, 1.f,   1.f, 0.f,
        0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f,   1.f, 1.f,
        -0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f,   0.f, 1.f,
    };

    static std::vector<uint32_t> cubeIndices = {
        // Back face
        0, 1, 2, 2, 3, 0,
        // Front face
        4, 5, 6, 6, 7, 4,
        // Left face
        4, 0, 3, 3, 7, 4,
        // Right face
        1, 5, 6, 6, 2, 1,
        // Bottom face
        4, 5, 1, 1, 0, 4,
        // Top face
        3, 2, 6, 6, 7, 3
    };
    auto cubeMesh = Elyra::Mesh::Create(cubeVertices, cubeIndices);   
    auto cubeShader = Elyra::Shader::Create("shaders/Cube.vert","shaders/Cube.frag");

    // Simulate ECS: create a cube entity with components
    m_Scene = std::make_shared<Elyra::Scene>();
    auto cube = m_Scene->CreateEntity("Cube");

    cube.GetComponent<Elyra::MeshComponent>().MeshData      = cubeMesh;
    cube.GetComponent<Elyra::MaterialComponent>().s_Shader  = cubeShader;
    cube.GetComponent<Elyra::TransformComponent>().Position = { 0.0f, 0.0f, 0.0f };
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
                matComp.s_Shader,
                meshComp.MeshData->GetVertexArray(),
                transform.GetTransform()
            );
        }
    }

    // if (auto cube = m_Scene->GetEntityByName("Cube")) {
    //     auto& transform = cube.GetComponent<Elyra::TransformComponent>();
    //     transform.Rotation.y += ts * glm::radians(90.0f);
    // }
    m_Scene->GetEntityByName("Cube").GetComponent<Elyra::TransformComponent>().Rotation.y += ts * glm::radians(90.0f);

    Elyra::Renderer::EndScene();
}

void ECSrender::OnEvent(Elyra::Event& event) {
    m_CameraController.OnEvent(event);  // <--- forward events
}

void ECSrender::OnUIRender()
{
    Elyra::UI::BeginPanel("Camera");
    Elyra::UI::SliderFloat("Move speed", &speed, 1.0f, 10.0f);
    Elyra::UI::Text("Pos: " + glm::to_string(m_Campos));
    Elyra::UI::EndPanel();

}
