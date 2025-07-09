#pragma once
#include "ElyraAPI.hpp"
#include "Elyrapch.hpp"
#include "ECS/Registry.hpp"
#include "ECS/Component.hpp"

namespace Elyra {

class Entity; // Forward declare only — no full include needed

class ELYRA_API Scene {
public:
    Scene() = default;

    Entity CreateEntity(const std::string& name = "Entity");
    void DestroyEntity(Entity entity);

    template<typename T, typename... Args>
    T& AddComponent(Entity entity, Args&&... args);

    template<typename T>
    T& GetComponent(Entity entity);

    template<typename T>
    bool HasComponent(Entity entity) const;

    template<typename T>
    void RemoveComponent(Entity entity);

    Entity GetEntityByName(const std::string& name);
    std::vector<Entity> GetAllEntities();

private:
    EntityID m_NextEntityID = 1;
    std::vector<EntityID> m_Entities;
    Registry m_Registry;
};


} // namespace Elyra
#include "ECS/Entity.inl"
#include "Scene.inl"
