#include "Elyrapch.hpp"
#include "Application.hpp"
#include "Log.hpp"
#include <glad/glad.h>

namespace Elyra {

    void Application::Run() {
        Log::Init();
        EL_CORE_INFO("Engine starting...");

        // Create() returns a std::unique_ptr<Window>
        m_Window = Window::Create({ "Elyra Engine", 1280, 720 });
        m_Window->SetEventCallback([](Event& e) {
            EL_CORE_TRACE("Event: {0}", e.ToString());
        });

        while (!m_Window->ShouldClose()) {
            glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Window->OnUpdate();
        }

        EL_CORE_INFO("Engine shutting down.");
    }

}
