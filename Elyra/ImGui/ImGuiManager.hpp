#pragma once
#include <memory>
#include <imgui.h>

struct GLFWwindow;

namespace Elyra {

class ImGuiManager {
public:
    static void Init(GLFWwindow* window);   // call once at engine start‑up
    static void Shutdown();                 // call at engine shutdown
    static void BeginFrame();               // call every frame, before sandbox layers
    static void EndFrame();
    static void OnImGuiRender();                 // call every frame, after sandbox layers
};

} // namespace Elyra
