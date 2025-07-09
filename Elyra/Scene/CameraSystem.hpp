#pragma once

#include "Scene/Scene.hpp"
#include "Events/Event.hpp"

namespace Elyra {

class CameraSystem {
public:
    static void OnUpdate(Scene* scene, TimeStep ts);
    static void OnViewportResize(Scene* scene, uint32_t width, uint32_t height);
    static void OnEvent(Scene* scene, Event& e);

};

}
