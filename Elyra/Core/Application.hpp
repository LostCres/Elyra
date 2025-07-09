#pragma once

#include <glad/glad.h>

#include "Elyra.hpp"
#include "Window.hpp"
#include "Layer/LayerStack.hpp"
#include "Input/Input.hpp"

namespace Elyra {

    class ELYRA_API Application {
    public:
        Application();
        virtual ~Application();

        virtual void Run();

        virtual void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        Window& GetWindow() { return *m_Window; }

        static Application& Get() { return *s_Instance; }

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;

        static Application* s_Instance;
    };
    Application* CreateApplication();
}