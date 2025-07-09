#pragma once

#include "ElyraAPI.hpp"
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <cassert>
#include <string>
#include <type_traits>
#include <utility>
#include "ECS/Entity.hpp"
#include "ECS/Component.hpp"

namespace Elyra {

class Entity; // Forward declaration

// -------------------------------------
// Component Pool (templated per type)
// -------------------------------------
struct IComponentPool {
    virtual ~IComponentPool() = default;
};

template<typename T>
class ComponentPool final : public IComponentPool {
public:
    T& Emplace(EntityID id, T&& component) {
        auto [it, inserted] = m_Data.emplace(id, std::move(component));
        assert(inserted && "Component already exists on entity!");
        return it->second;
    }

    template<typename... Args>
    T& Emplace(EntityID id, Args&&... args) {
        auto [it, inserted] = m_Data.emplace(id, T(std::forward<Args>(args)...));
        assert(inserted && "Component already exists on entity!");
        return it->second;
    }

    T& Get(EntityID id) {
        assert(m_Data.find(id) != m_Data.end() && "Component missing on entity!");
        return m_Data.at(id);
    }

    bool Has(EntityID id) const {
        return m_Data.find(id) != m_Data.end();
    }

    void Remove(EntityID id) {
        m_Data.erase(id);
    }

private:
    std::unordered_map<EntityID, T> m_Data;
};

// -------------------------------------
// Scene - ECS registry
// -------------------------------------
class ELYRA_API Scene {
public:
    Scene() = default;

    // -------- Entity Management ----------
    Entity CreateEntity(const std::string& name = "Entity");
    void DestroyEntity(Entity entity);

    // -------- Component Accessors --------
    template<typename T, typename... Args>
    T& AddComponent(Entity entity, Args&&... args) {
        return GetOrCreatePool<T>().Emplace(entity.GetID(), std::forward<Args>(args)...);
    }

    template<typename T>
    T& GetComponent(Entity entity) {
        return GetPool<T>().Get(entity.GetID());
    }

    template<typename T>
    bool HasComponent(Entity entity) const {
        return GetPoolConst<T>().Has(entity.GetID());
    }

    template<typename T>
    void RemoveComponent(Entity entity) {
        GetPool<T>().Remove(entity.GetID());
    }

    std::vector<Entity> GetAllEntities();

    Entity GetEntityByName(const std::string& name) {
        for (EntityID id : m_Entities) {
            Entity entity(id, this);
            if (HasComponent<TagComponent>(entity)) {
                const auto& tag = GetComponent<TagComponent>(entity).Tag;
                if (tag == name)
                    return entity;
            }
        }

        // Optional: return an invalid Entity (ID 0) if not found
        return Entity(0, this);
    }

private:
    EntityID m_NextEntityID = 1;
    std::vector<EntityID> m_Entities; // ✨ Track all created entities

    std::unordered_map<std::type_index, std::unique_ptr<IComponentPool>> m_Pools;

    template<typename T>
    ComponentPool<T>& GetPool() {
        auto key = std::type_index(typeid(T));
        assert(m_Pools.find(key) != m_Pools.end() && "Component pool does not exist!");
        return static_cast<ComponentPool<T>&>(*m_Pools.at(key));
    }

    template<typename T>
    const ComponentPool<T>& GetPoolConst() const {
        auto key = std::type_index(typeid(T));
        assert(m_Pools.find(key) != m_Pools.end() && "Component pool does not exist!");
        return static_cast<const ComponentPool<T>&>(*m_Pools.at(key));
    }

    template<typename T>
    ComponentPool<T>& GetOrCreatePool() {
        auto key = std::type_index(typeid(T));
        auto it = m_Pools.find(key);
        if (it == m_Pools.end()) {
            auto pool = std::make_unique<ComponentPool<T>>();
            it = m_Pools.emplace(key, std::move(pool)).first;
        }
        return static_cast<ComponentPool<T>&>(*it->second);
    }
};

template<typename T, typename... Args>
T& Entity::AddComponent(Args&&... args) {
    return m_Scene->AddComponent<T>(*this, std::forward<Args>(args)...);
}

template<typename T>
T& Entity::GetComponent() {
    return m_Scene->GetComponent<T>(*this);
}

template<typename T>
bool Entity::HasComponent() const {
    return m_Scene->HasComponent<T>(*this);
}

template<typename T>
void Entity::RemoveComponent() {
    m_Scene->RemoveComponent<T>(*this);
}


} // namespace Elyra
