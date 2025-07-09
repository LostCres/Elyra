#pragma once

namespace Elyra {

// ========== ComponentPool ==========

template<typename T>
template<typename... Args>
T& ComponentPool<T>::Emplace(EntityID id, Args&&... args) {
    auto [it, inserted] = m_Data.emplace(id, T(std::forward<Args>(args)...));
    EL_CORE_ASSERT(inserted, "Component already exists!");
    return it->second;
}

template<typename T>
T& ComponentPool<T>::Get(EntityID id) {
    EL_CORE_ASSERT(m_Data.contains(id), "Component missing!");
    return m_Data.at(id);
}

template<typename T>
bool ComponentPool<T>::Has(EntityID id) const {
    return m_Data.contains(id);
}

template<typename T>
void ComponentPool<T>::Remove(EntityID id) {
    m_Data.erase(id);
}

// ========== Registry ==========

template<typename T, typename... Args>
T& Registry::AddComponent(EntityID id, Args&&... args) {
    return GetOrCreatePool<T>().Emplace(id, std::forward<Args>(args)...);
}

template<typename T>
T& Registry::GetComponent(EntityID id) {
    return GetPool<T>().Get(id);
}

template<typename T>
bool Registry::HasComponent(EntityID id) const {
    return GetPoolConst<T>().Has(id);
}

template<typename T>
void Registry::RemoveComponent(EntityID id) {
    GetPool<T>().Remove(id);
}

template<typename T>
ComponentPool<T>& Registry::GetOrCreatePool() {
    auto key = std::type_index(typeid(T));
    auto it = m_Pools.find(key);
    if (it == m_Pools.end()) {
        it = m_Pools.emplace(key, std::make_unique<ComponentPool<T>>()).first;
    }
    return static_cast<ComponentPool<T>&>(*it->second);
}

template<typename T>
ComponentPool<T>& Registry::GetPool() {
    auto key = std::type_index(typeid(T));
    EL_CORE_ASSERT(m_Pools.contains(key), "Component pool does not exist!");
    return static_cast<ComponentPool<T>&>(*m_Pools.at(key));
}

template<typename T>
const ComponentPool<T>& Registry::GetPoolConst() const {
    auto key = std::type_index(typeid(T));
    EL_CORE_ASSERT(m_Pools.contains(key), "Component pool does not exist!");
    return static_cast<const ComponentPool<T>&>(*m_Pools.at(key));
}

} // namespace Elyra
