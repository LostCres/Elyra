#include "Elyrapch.hpp"
#include "Application.hpp"
#include "Log.hpp"

namespace Elyra {

    Application::Application() {
        Log::Init();

        m_Window = Window::Create({ "Elyra Engine", 1280, 720 });
        m_Window->SetEventCallback([this](Event& e) {
            OnEvent(e);
        });
    }

    Application::~Application() = default;

    void Application::Run() {
        EL_CORE_INFO("Engine starting...");

        while (!m_Window->ShouldClose() && m_Running) {
            glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Window->OnUpdate();
        }

        EL_CORE_INFO("Engine shutting down.");
    }

    void Application::OnEvent(Event& e) {
        EL_CORE_TRACE("Event: {}", e.ToString());

        if (e.GetEventType() == EventType::WindowClose)
            m_Running = false;
    }

}
