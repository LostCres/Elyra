#pragma once
#include <cstdint>
#include "ElyraAPI.hpp"

namespace Elyra {

class Scene; // forward

using EntityID = uint32_t;

class ELYRA_API Entity {
public:
    Entity() = default;
    Entity(EntityID id, Scene* scene) : m_ID(id), m_Scene(scene) {}

    template<typename T, typename... Args>
    T& AddComponent(Args&&... args);

    template<typename T>
    T& GetComponent();

    template<typename T>
    bool HasComponent() const;

    template<typename T>
    void RemoveComponent();

    EntityID GetID() const { return m_ID; }
    operator bool() const { return m_ID != 0; }
    bool operator==(const Entity& other) const { return m_ID == other.m_ID; }

private:
    EntityID m_ID = 0;
    Scene*   m_Scene = nullptr;
};

} // namespace Elyra
