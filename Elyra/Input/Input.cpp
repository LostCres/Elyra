#include "Input.hpp"
#include "Core/Application.hpp"  // to access the Window and GLFWwindow*
#include <GLFW/glfw3.h>

namespace Elyra {

    static GLFWwindow* GetGLFWWindow() {
        return static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    }

    bool Input::IsKeyPressed(int keycode) {
        auto window = GetGLFWWindow();
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(int button) {
        auto window = GetGLFWWindow();
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> Input::GetMousePosition() {
        auto window = GetGLFWWindow();
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return {(float)xpos, (float)ypos};
    }

    float Input::GetMouseX() {
        auto pos = GetMousePosition();
        return pos.first;
    }

    float Input::GetMouseY() {
        auto pos = GetMousePosition();
        return pos.second;
    }

}
