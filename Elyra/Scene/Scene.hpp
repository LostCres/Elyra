#pragma once
#include "ElyraAPI.hpp"
#include "Elyrapch.hpp"
#include "ECS/Registry.hpp"
#include "ECS/Component.hpp"
#include "Core/TimeStep.hpp"
#include "Events/Event.hpp"

namespace Elyra {

class Entity; // Forward declare only — no full include needed

class ELYRA_API Scene {
public:
    Scene() = default;
    ~Scene(); // Explicitly declare the destructor

    Entity CreateEntity(const std::string& name = "Entity");
    void DestroyEntity(Entity entity);
    void DestroyAllEntities();

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

    void OnUpdate(TimeStep ts);

    void OnEvent(Event& e);

    void OnViewportResize(uint32_t width, uint32_t height);


    Entity GetActiveCamera() const { return m_ActiveCamera; }
    void SetActiveCamera(Entity camera) { m_ActiveCamera = camera; }

    void SetViewportSize(uint32_t width, uint32_t height)
    {
        m_ViewportWidth = width;
        m_ViewportHeight = height;
    }

    uint32_t GetViewportWidth() const { return m_ViewportWidth; }
    uint32_t GetViewportHeight() const { return m_ViewportHeight; }

private:
    uint32_t m_ViewportWidth = 1280, m_ViewportHeight = 720;
    Entity m_ActiveCamera;
    EntityID m_NextEntityID = 1;
    std::vector<EntityID> m_Entities;
    Registry m_Registry;
};


} // namespace Elyra
#include "ECS/Entity.inl"
#include "Scene.inl"
