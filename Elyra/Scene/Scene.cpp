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
        m_ViewportWidth = width;
        m_ViewportHeight = height;

        CameraSystem::OnViewportResize(this, width, height);
    }


    void Scene::DestroyEntity(Entity entity) {
        // TODO: Implement removal logic if needed
        (void)entity;
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

} // namespace Elyra
