#pragma once
#include "ECS/Entity.hpp"

namespace Elyra {

template<typename T, typename... Args>
T& Scene::AddComponent(Entity entity, Args&&... args) {
    return m_Registry.AddComponent<T>(entity.GetID(), std::forward<Args>(args)...);
}

template<typename T>
T& Scene::GetComponent(Entity entity) {
    return m_Registry.GetComponent<T>(entity.GetID());
}

template<typename T>
bool Scene::HasComponent(Entity entity) const {
    return m_Registry.HasComponent<T>(entity.GetID());
}

template<typename T>
void Scene::RemoveComponent(Entity entity) {
    m_Registry.RemoveComponent<T>(entity.GetID());
}

} // namespace Elyra
