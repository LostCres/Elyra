#pragma once
#include "ElyraAPI.hpp"
#include "Core/core.hpp"     // whatever defines Ref<>
#include "ECS/Scene.hpp"

namespace Elyra {

class ELYRA_API SceneManager
{
public:
    // Set once – e.g., when your SceneLayer is attached
    static void SetActiveScene(const Ref<Scene>& scene);

    // Any layer/system can call this safely
    static Ref<Scene> GetActiveScene();

private:
    static Ref<Scene> s_ActiveScene;   // <‑‑ declaration only
};

} // namespace Elyra
