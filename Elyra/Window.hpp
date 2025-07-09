#pragma once

#include <string>

struct GLFWwindow;

namespace Elyra {

    class Window {
    public:
        Window(const std::string& title, int width, int height);
        ~Window();

        void PollEvents() const;
        bool ShouldClose() const;
        void SwapBuffers() const;

    private:
        GLFWwindow* m_Window;
    };

}
