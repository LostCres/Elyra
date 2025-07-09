#pragma once
#include "Elyra.hpp"
#include "Window.hpp"

#include <glad/glad.h>
namespace Elyra {

    class ELYRA_API Application {
    public:
        Application();
        virtual ~Application();

        virtual void Run();

        virtual void OnEvent(Event& e);
    protected:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };
    Application* CreateApplication();
}