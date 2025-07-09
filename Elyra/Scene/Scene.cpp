#include "Scene/Scene.hpp"

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
        for (auto& entity : GetAllEntities())
        {
            if (!entity.HasComponent<ScriptableComponent>())
                continue;

            auto& sc = entity.GetComponent<ScriptableComponent>();

            if (!sc.Instance)
            {
                sc.Instance = sc.InstantiateScript();
                sc.Instance->m_Entity = entity;
                sc.Instance->OnCreate();
            }

            sc.Instance->OnUpdate(ts);
        }
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
