#include "Application.hpp"
#include "Window.hpp"
#include "Log.hpp"
#include <glad/glad.h>

namespace Elyra {

    void Application::Run() {
        Log::Init();
        EL_CORE_INFO("Engine starting...");
        Window window("Elyra Engine", 1280, 720);

        while (!window.ShouldClose()) {
            glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            window.PollEvents();
            window.SwapBuffers();
        }
        EL_CORE_INFO("Engine shutting down.");
    }

}
