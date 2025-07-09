#include "Elyrapch.hpp"
#include "Application.hpp"
#include "TimeStep.hpp"
#include "Log.hpp"
#include "Input/Input.hpp"

Elyra::Application* Elyra::Application::s_Instance = nullptr;

namespace Elyra {

    Application::Application(const WindowProps& props) {
        Log::Init();

        s_Instance = this;

        m_Window = Window::Create(props);
        m_Window->SetEventCallback([this](Event& e) {
            OnEvent(e);
        });
        
        ImGuiManager::Init(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()));
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

            if (Elyra::Input::IsKeyPressed(Elyra::Key::Key_Escape)) {
                m_Running = false;
                EL_CORE_INFO("Escape pressed: Closing Application.");
            }

            for (auto& layer : m_LayerStack) {
                layer->OnUpdate(deltaTime);
            }

            ImGuiManager::BeginFrame();
            ImGuiContext* context = ImGui::GetCurrentContext();
            for (auto& layer : m_LayerStack)
                layer->OnImGuiRender(context);
            ImGuiManager::EndFrame();

            m_Window->OnUpdate();
        }

        EL_CORE_INFO("Engine shutting down.");
    }

    void Application::OnEvent(Event& e) {
        EL_CORE_TRACE("Event: {}", e.ToString());

        // Forward input-related events to the Input system
        Input::OnEvent(e);   

        // Handle global engine-level events
        if (e.GetEventType() == EventType::WindowClose)
            m_Running = false;

        // Propagate to layers (in reverse order)
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
