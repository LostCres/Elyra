#include "ECS/Scene.hpp"
#include "ECS/Entity.hpp"
#include <utility>

namespace Elyra {

Entity Scene::CreateEntity(const std::string& name) {
    Entity entity(m_NextEntityID++, this);
    // Every entity gets a tag + transform by default
    AddComponent<TagComponent>(entity, name);
    AddComponent<TransformComponent>(entity);
    return entity;
}

void Scene::DestroyEntity(Entity entity) {
    // For a simple demo we won't remove components from every pool —
    // they can stay or be garbage‑collected when pools are cleared.
    (void)entity; // TODO: proper removal if needed
}

} // namespace Elyra
