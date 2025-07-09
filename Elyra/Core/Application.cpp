#include "Elyrapch.hpp"
#include "Application.hpp"
#include "TimeStep.hpp"
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

        TimeStep lastTime = TimeStep::Now();

        while (!m_Window->ShouldClose() && m_Running) {
            glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            TimeStep currentTime = TimeStep::Now();
            TimeStep deltaTime = currentTime - lastTime;
            lastTime = currentTime;

            EL_CORE_INFO("Delta Time: {0} ms", deltaTime.GetMilliseconds());

            for (auto& layer : m_LayerStack) {
                layer->OnUpdate(deltaTime);
            }

            m_Window->OnUpdate();
        }

        EL_CORE_INFO("Engine shutting down.");
    }

    void Application::OnEvent(Event& e) {
        EL_CORE_TRACE("Event: {}", e.ToString());

        if (e.GetEventType() == EventType::WindowClose)
            m_Running = false;
        
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            (*--it)->OnEvent(e);
            if (e.Handled) break;
        }

    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay) {
        m_LayerStack.PushOverlay(overlay);
    }


}
