#include "Scene/Scene.hpp"
#include "Scene/CameraSystem.hpp"
#include "Scene/RenderSystem.hpp"
#include "Scene/ScriptSystem.hpp"


namespace Elyra {

    Entity Scene::CreateEntity(const std::string& name) {
        Entity entity(m_NextEntityID++, this);
        m_Entities.push_back(entity.GetID());
        AddComponent<TagComponent>(entity, name);
        AddComponent<TransformComponent>(entity);
        return entity;
    }

    void Scene::OnUpdate(TimeStep ts)
    {
        ScriptSystem::OnUpdate(this,ts);
        CameraSystem::OnUpdate(this, ts);
        RenderSystem::OnRender(this);
    }

    void Scene::OnEvent(Event& e)
    {
        CameraSystem::OnEvent(this, e);
        // ...forward to other systems if needed
    }


    void Scene::OnViewportResize(uint32_t width, uint32_t height)
    {
        if (width == 0 || height == 0) {
            EL_CORE_WARN("Invalid viewport dimensions: {}x{}", width, height);
            return;
        }
        
        m_ViewportWidth = width;
        m_ViewportHeight = height;

        CameraSystem::OnViewportResize(this, width, height);
    }


    void Scene::DestroyEntity(Entity entity) {
        auto it = std::find(m_Entities.begin(), m_Entities.end(), entity.GetID());
        if (it != m_Entities.end()) {
            // Remove all components
            m_Registry.RemoveAllComponents(entity);
            // Remove from entities list
            m_Entities.erase(it);
            
            // Reset active camera if this was it
            if (m_ActiveCamera == entity) {
                m_ActiveCamera = Entity(0, this);
            }
        }
    }

    void Scene::DestroyAllEntities() {
        for (auto id : m_Entities) {
            Entity entity(id, this);
            DestroyEntity(entity);
        }
        m_Entities.clear();
    }

    std::vector<Entity> Scene::GetAllEntities() {
        std::vector<Entity> result;
        for (auto id : m_Entities)
            result.emplace_back(id, this);
        return result;
    }

    Entity Scene::GetEntityByName(const std::string& name) {
        for (EntityID id : m_Entities) {
            Entity entity(id, this);
            if (HasComponent<TagComponent>(entity)) {
                const auto& tag = GetComponent<TagComponent>(entity).Tag;
                if (tag == name)
                    return entity;
            }
        }
        EL_CORE_ERROR("Scene:Enitiy not Found");
        return Entity(0, this); // Invalid
    }

    Scene::~Scene() {
        DestroyAllEntities();
        EL_CORE_INFO("Scene destroyed and all entities cleaned up.");
    }

} // namespace Elyra
