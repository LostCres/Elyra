#pragma once
#include "Entity.hpp"

namespace Elyra {

    template<typename T, typename... Args>
    T& Entity::AddComponent(Args&&... args) {
        return m_Scene->template AddComponent<T>(*this, std::forward<Args>(args)...);
    }

    template<typename T>
    T& Entity::GetComponent() {
        return m_Scene->template GetComponent<T>(*this);
    }

    template<typename T>
    bool Entity::HasComponent() const {
        return m_Scene->template HasComponent<T>(*this);
    }

    template<typename T>
    void Entity::RemoveComponent() {
        m_Scene->template RemoveComponent<T>(*this);
    }

} // namespace Elyra
