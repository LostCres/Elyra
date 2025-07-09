#pragma once
#include "Elyrapch.hpp"

namespace Elyra {

class UIManager
{
public:
    // Initialize UI system with native window pointer (GLFWwindow*)
    static void Init(void* nativeWindow);

    static void Shutdown();

    static void Begin();  // Begin UI frame
    static void End();    // End UI frame and render

    // Internal: returns ImGuiContext*
    static void* GetNativeContext();
};

} // namespace Elyra