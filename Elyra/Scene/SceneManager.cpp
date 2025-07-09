#include "Scene/SceneManager.hpp"

namespace Elyra {

// ‑‑‑‑‑‑‑‑‑‑ single global definition – allocates memory
Ref<Scene> SceneManager::s_ActiveScene = nullptr;

void SceneManager::SetActiveScene(const Ref<Scene>& scene)
{
    s_ActiveScene = scene;
}

Ref<Scene> SceneManager::GetActiveScene()
{
    return s_ActiveScene;
}

} // namespace Elyra
