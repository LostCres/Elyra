#pragma once
#include "Elyra.hpp"
#include "Window.hpp"
#include "Layer/LayerStack.hpp"

#include <glad/glad.h>
namespace Elyra {

    class ELYRA_API Application {
    public:
        Application();
        virtual ~Application();

        virtual void Run();

        virtual void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);


    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    };
    Application* CreateApplication();
}