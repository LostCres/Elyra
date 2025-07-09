#include "ECSrender.hpp"
 #define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Scripts.hpp"

ECSrender::ECSrender()
    : Layer("Sandbox") {}

void ECSrender::OnAttach() {

    m_Scene = Elyra::CreateRef<Elyra::Scene>();
    Elyra::SceneManager::SetActiveScene(m_Scene);
    Elyra::Material::SetDefaultShader(Elyra::Shader::Create("Assets/shaders/vertex.glsl","Assets/shaders/fragment.glsl"));

    auto globalUniforms = Elyra::UniformSet::Create();
    globalUniforms->Set("ambientColor", glm::vec3(0.2f));

    Elyra::Material::SetGlobalUniforms(globalUniforms);

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    auto cam1 = m_Scene->CreateEntity("cam1");
    cam1.AddComponent<Elyra::CameraComponent>().Primary = true;
    cam1.AddComponent<Elyra::CameraControllerComponent>();
    cam1.GetComponent<Elyra::TransformComponent>().Position = { 0.0f, 1.0f, 3.0f };
    cam1.GetComponent<Elyra::CameraControllerComponent>().Controller.SetCamera(&cam1.GetComponent<Elyra::CameraComponent>().Camera);
    cam1.GetComponent<Elyra::CameraComponent>().Camera.SetPosition(cam1.GetComponent<Elyra::TransformComponent>().Position);

    auto cam2 = m_Scene->CreateEntity("cam2");
    cam2.AddComponent<Elyra::CameraComponent>().Primary = false;
    cam2.AddComponent<Elyra::CameraControllerComponent>();
    cam2.GetComponent<Elyra::TransformComponent>().Position = { 0.0f, 1.0f, 3.0f };
    cam2.GetComponent<Elyra::CameraControllerComponent>().Controller.SetCamera(&cam2.GetComponent<Elyra::CameraComponent>().Camera);
    cam2.GetComponent<Elyra::CameraComponent>().Camera.SetPosition(cam2.GetComponent<Elyra::TransformComponent>().Position);

    m_Scene->SetActiveCamera(cam1);

    auto cubeMesh = Elyra::Primitives::Cube();
    auto material = Elyra::Material::Create();
    material->Set("u_BaseColor", glm::vec3(1.0f, 0.0f, 0.0f)); // Red
    material->SetTexture("u_Albedo", Elyra::Texture2D::Create("Assets/textures/brick.jpg"));

    auto cube = m_Scene->CreateEntity("Cube");
    cube.AddComponent<Elyra::MeshComponent>().MeshData      = cubeMesh;
    cube.AddComponent<Elyra::MaterialComponent>().MaterialData = material;
    cube.GetComponent<Elyra::TransformComponent>().Position = { 0.0f, 0.5f, 0.0f };
    cube.AddComponent<Elyra::ScriptableComponent>().Bind<SpinScript>();//script

    auto sphereMesh = Elyra::Primitives::Sphere();
    auto material2 = Elyra::Material::Create();
    material2->Set("u_BaseColor", glm::vec3(0.0f, 0.0f, 1.0f));// Blue 
    material2->SetTexture("u_Albedo", Elyra::Texture2D::Create("Assets/textures/metal.jpg"));

    auto sphere = m_Scene->CreateEntity("Sphere");
    sphere.AddComponent<Elyra::MeshComponent>().MeshData = sphereMesh;
    sphere.AddComponent<Elyra::MaterialComponent>().MaterialData = material2;
    sphere.GetComponent<Elyra::TransformComponent>().Position = {0.0f, 2.0f,0.0f};

    auto planeMesh = Elyra::Primitives::Plane(5.0f,5.0f);
    auto plane = m_Scene->CreateEntity("Plane");
    plane.AddComponent<Elyra::MeshComponent>().MeshData = planeMesh;
    plane.AddComponent<Elyra::MaterialComponent>().MaterialData = material2;

    for (auto& entity : m_Scene->GetAllEntities())
    {
        if (entity.HasComponent<Elyra::MaterialComponent>())
        {
            auto& matComp   = entity.GetComponent<Elyra::MaterialComponent>();
            matComp.MaterialData->Set("u_UseAlbedoTexture",matComp.MaterialData->HasTexture("u_Albedo"));
        }
    }
}

void ECSrender::OnDetach() {
    // Cleanup if needed
}

void ECSrender::OnUpdate(Elyra::TimeStep ts) {
    Elyra::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Elyra::RenderCommand::Clear();
    m_Scene->OnUpdate(ts);
}

void ECSrender::OnEvent(Elyra::Event& event) {
    m_Scene->OnEvent(event);

    if (event.GetEventType() == Elyra::EventType::KeyPressed)
    {
        if(static_cast<Elyra::KeyPressedEvent&>(event).GetKeyCode()==Elyra::Key_M)
        {
            auto cam1 = m_Scene->GetEntityByName("cam1");
            auto cam2 = m_Scene->GetEntityByName("cam2");

            auto current = m_Scene->GetActiveCamera();

            if (current == cam1)
                m_Scene->SetActiveCamera(cam2);
            else
                m_Scene->SetActiveCamera(cam1);
        }           
    }
}

void ECSrender::OnUIRender()
{
    auto a_camera = m_Scene->GetActiveCamera();
    auto speed = a_camera.GetComponent<Elyra::CameraControllerComponent>().Controller.GetSpeed();
    auto fov = a_camera.GetComponent<Elyra::CameraComponent>().Camera.GetFOV();
    auto transform = a_camera.GetComponent<Elyra::TransformComponent>();

    Elyra::UI::BeginPanel("Active Camera");
    if(Elyra::UI::SliderFloat("Move Speed", &speed, 1.0f, 10.0f))
        a_camera.GetComponent<Elyra::CameraControllerComponent>().Controller.SetSpeed(speed);
    if(Elyra::UI::SliderFloat("FOV", &fov, 1.0f, 100.0f))
        a_camera.GetComponent<Elyra::CameraComponent>().Camera.SetFOV(fov);
    Elyra::UI::Text("Camera: "+a_camera.GetComponent<Elyra::TagComponent>().Tag);
    Elyra::UI::Text("Position: (" + std::to_string(transform.Position.x) + ", " +
                     std::to_string(transform.Position.y) + ", " +
                     std::to_string(transform.Position.z) + ")");
    Elyra::UI::Text("Rotation: (" + std::to_string(transform.Rotation.x) + ", " +
                     std::to_string(transform.Rotation.y) + ", " +
                     std::to_string(transform.Rotation.z) + ")");
    Elyra::UI::EndPanel();

}
