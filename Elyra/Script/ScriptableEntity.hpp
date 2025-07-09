#pragma once
#include "Scene/Scene.hpp"
#include "ECS/Entity.hpp"
#include "Core/TimeStep.hpp"

namespace Elyra {

class ScriptableEntity
    {
    public:
        virtual ~ScriptableEntity() = default;

        template<typename T>
        T& GetComponent()
        {
            return m_Entity.GetComponent<T>();
        }

        template<typename T>
        bool HasComponent()
        {
            return m_Entity.HasComponent<T>();
        }

    protected:
        virtual void OnCreate() {}
        virtual void OnUpdate(TimeStep ts) {}
        virtual void OnDestroy() {}

    private:
        Entity m_Entity;

        friend class Scene; // Scene can set the entity handle
    };

}
