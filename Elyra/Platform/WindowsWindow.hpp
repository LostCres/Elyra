#pragma once
#include "Core/Window.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Elyra {

    class WindowsWindow : public Window {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        unsigned int GetWidth() const override { return m_Data.Width; }
        unsigned int GetHeight() const override { return m_Data.Height; }

        void SetEventCallback(const EventCallbackFn& callback) override {
            m_Data.EventCallback = callback;
        }

        void* GetNativeWindow() const override { return m_Window; }
        
        bool ShouldClose() const override;

    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

        GLFWwindow* m_Window;

        struct WindowData {
            std::string Title;
            unsigned int Width, Height;
            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };

}
