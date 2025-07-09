#pragma once

#include "Elyrapch.hpp"
#include "Core/Log.hpp"
#include "ECS/Entity.hpp"

namespace Elyra {

struct IComponentPool {
    virtual ~IComponentPool() = default;
};

template<typename T>
class ComponentPool final : public IComponentPool {
public:
    template<typename... Args>
    T& Emplace(EntityID id, Args&&... args);

    T& Get(EntityID id);
    bool Has(EntityID id) const;
    void Remove(EntityID id);

private:
    std::unordered_map<EntityID, T> m_Data;
};

class Registry {
public:
    template<typename T, typename... Args>
    T& AddComponent(EntityID id, Args&&... args);

    template<typename T>
    T& GetComponent(EntityID id);

    template<typename T>
    bool HasComponent(EntityID id) const;

    template<typename T>
    void RemoveComponent(EntityID id);

private:
    std::unordered_map<std::type_index, std::unique_ptr<IComponentPool>> m_Pools;

    template<typename T>
    ComponentPool<T>& GetOrCreatePool();

    template<typename T>
    ComponentPool<T>& GetPool();

    template<typename T>
    const ComponentPool<T>& GetPoolConst() const;
};

} // namespace Elyra

#include "ECS/Registry.inl"
