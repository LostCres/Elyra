#include "ECSrender.hpp"
#include <glm/glm.hpp>
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
    Elyra::Material::SetDefaultShader(Elyra::Shader::Create("Default","Assets/shaders/vertex.glsl","Assets/shaders/fragment.glsl"));

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
    sphere.AddComponent<Elyra::ScriptableComponent>().Bind<sphererotate>();//script

    auto planeMesh = Elyra::Primitives::Plane(5.0f,5.0f);
    auto plane = m_Scene->CreateEntity("Plane");
    plane.AddComponent<Elyra::MeshComponent>().MeshData = planeMesh;
    plane.AddComponent<Elyra::MaterialComponent>().MaterialData = material2;

    // --- OBJ loader demo ---
    // Try to load Assets/cube.obj; fall back to a procedural cube if the file is absent.
    auto treeMesh = Elyra::Mesh::Load("Assets/obj/tree.obj");
    auto leafMesh = Elyra::Mesh::Load("Assets/obj/leaf.obj");
    if (!treeMesh||!leafMesh) {
        EL_WARN("OBJ load failed — falling back to procedural cube.");
        treeMesh = Elyra::Primitives::Cube();
    }
    auto treeMaterial = Elyra::Material::Create();
    treeMaterial->Set("u_BaseColor", glm::vec3(0.5f, 0.3f, 0.1f)); // brown
    auto leafMaterial = Elyra::Material::Create();
    leafMaterial->Set("u_BaseColor", glm::vec3(0.2f, 0.9f, 0.3f)); // lime green

    auto treeEntity = m_Scene->CreateEntity("Tree");
    treeEntity.AddComponent<Elyra::MeshComponent>().MeshData       = treeMesh;
    treeEntity.AddComponent<Elyra::MaterialComponent>().MaterialData = treeMaterial;
    treeEntity.GetComponent<Elyra::TransformComponent>().Position    = { 2.5f, 0.5f, 0.0f };

    auto leafEntity = m_Scene->CreateEntity("Leaf");
    leafEntity.AddComponent<Elyra::MeshComponent>().MeshData       = leafMesh;
    leafEntity.AddComponent<Elyra::MaterialComponent>().MaterialData = leafMaterial;
    leafEntity.GetComponent<Elyra::TransformComponent>().Position    = { 2.5f, 0.5f, 0.0f };
    // -----------------------

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
    if (m_Scene) {
        m_Scene->DestroyAllEntities();
        EL_CORE_INFO("All entities destroyed in ECSrender.");
    }
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
        auto& keyEvent = static_cast<Elyra::KeyPressedEvent&>(event);
        if(keyEvent.GetKeyCode() == Elyra::Key_M)
        {
            auto cam1 = m_Scene->GetEntityByName("cam1");
            auto cam2 = m_Scene->GetEntityByName("cam2");
            
            if (!cam1 || !cam2) {
                EL_CORE_ERROR("Failed to find cameras!");
                return;
            }

            auto current = m_Scene->GetActiveCamera();
            auto next = (current == cam1) ? cam2 : cam1;
            
            if (next.HasComponent<Elyra::CameraComponent>()) {
                m_Scene->SetActiveCamera(next);
                EL_CORE_INFO("Switched to camera: {}", next.GetComponent<Elyra::TagComponent>().Tag);
            }
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
