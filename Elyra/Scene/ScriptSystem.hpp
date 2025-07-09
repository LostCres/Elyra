#pragma once
#include "Scene/Scene.hpp"
#include "Script/ScriptableEntity.hpp"

namespace Elyra {

class ScriptSystem
{
public:
    static void OnUpdate(Scene* scene, TimeStep ts)
    {
        for (auto& entity : scene->GetAllEntities())
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
};

} // namespace Elyra
