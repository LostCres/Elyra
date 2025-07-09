#include "UI/UIManager.hpp"
#include "glad/glad.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include "Core/Log.hpp"

namespace Elyra {

static ImGuiContext* s_Context = nullptr;

void UIManager::Init(void* nativeWindow)
{
    EL_CORE_ASSERT(nativeWindow, "Native window pointer is null!");

    IMGUI_CHECKVERSION();
    s_Context = ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard
                    | ImGuiConfigFlags_DockingEnable;   // Docking on, viewports off by default

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(nativeWindow), true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void UIManager::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(s_Context);
    s_Context = nullptr;
}

void UIManager::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UIManager::End()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Multi‑viewport support (disabled by default via Init; but handle gracefully)
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup);
    }
}

void* UIManager::GetNativeContext()
{
    return s_Context;
}

} // namespace Elyra
