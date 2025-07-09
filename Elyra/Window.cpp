#include "Window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Elyra {

    Window::Window(const std::string& title, int width, int height) {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW\n";
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!m_Window) {
            std::cerr << "Failed to create window\n";
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD\n";
            return;
        }

        glViewport(0, 0, width, height);
    }

    Window::~Window() {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Window::PollEvents() const {
        glfwPollEvents();
    }

    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(m_Window);
    }

    void Window::SwapBuffers() const {
        glfwSwapBuffers(m_Window);
    }

}
