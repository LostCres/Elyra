#include "ECS/Scene.hpp"
#include "ECS/Entity.hpp"
#include <utility>

namespace Elyra {

Entity Scene::CreateEntity(const std::string& name) {
    Entity entity(m_NextEntityID++, this);
    // Every entity gets a tag + transform by default
    m_Entities.push_back(entity.GetID());
    AddComponent<TagComponent>(entity, name);
    AddComponent<TransformComponent>(entity);
    AddComponent<MeshComponent>(entity);
    AddComponent<MaterialComponent>(entity);
    return entity;
}

void Scene::DestroyEntity(Entity entity) {
    // For a simple demo we won't remove components from every pool —
    // they can stay or be garbage‑collected when pools are cleared.
    (void)entity; // TODO: proper removal if needed
}

std::vector<Entity> Scene::GetAllEntities() {
    std::vector<Entity> result;
    for (auto id : m_Entities)
        result.emplace_back(id, this);
    return result;
}


} // namespace Elyra
