#pragma once
#include "ElyraAPI.hpp"
#include "Events/Event.hpp"
#include "Elyrapch.hpp"
#include "Core/Core.hpp"

struct GLFWwindow;

namespace Elyra {

    struct WindowProps {
        std::string Title;
        unsigned int Width, Height;

        WindowProps(const std::string& title = "Elyra Engine",
                    unsigned int width = 1280,
                    unsigned int height = 720)
            : Title(title), Width(width), Height(height) {}
    };

    class ELYRA_API Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

        virtual void* GetNativeWindow() const = 0;

        virtual bool ShouldClose() const = 0;

        static Scope<Window> Create(const WindowProps& props = WindowProps());

    };

}
