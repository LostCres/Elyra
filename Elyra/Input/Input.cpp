// Input.cpp
#include "Input.hpp"
#include "Core/Application.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/EventDispatcher.hpp"

namespace Elyra {

    bool Input::s_KeyStates[EL_KEY_LAST] = {};
    bool Input::s_MouseButtonStates[EL_MOUSE_BUTTON_LAST] = {};
    float Input::s_MouseX = 0.0f;
    float Input::s_MouseY = 0.0f;

    void Input::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>([](KeyPressedEvent& e) {
            s_KeyStates[e.GetKeyCode()] = true;
            return false;
        });
        dispatcher.Dispatch<KeyReleasedEvent>([](KeyReleasedEvent& e) {
            s_KeyStates[e.GetKeyCode()] = false;
            return false;
        });
        dispatcher.Dispatch<MouseButtonPressedEvent>([](MouseButtonPressedEvent& e) {
            s_MouseButtonStates[e.GetMouseButton()] = true;
            return false;
        });
        dispatcher.Dispatch<MouseButtonReleasedEvent>([](MouseButtonReleasedEvent& e) {
            s_MouseButtonStates[e.GetMouseButton()] = false;
            return false;
        });
        dispatcher.Dispatch<MouseMovedEvent>([](MouseMovedEvent& e) {
            s_MouseX = e.GetX();
            s_MouseY = e.GetY();
            return false;
        });
    }

    bool Input::IsKeyPressed(int keycode) {
        return s_KeyStates[keycode];
    }

    bool Input::IsMouseButtonPressed(int button) {
        return s_MouseButtonStates[button];
    }

    std::pair<float, float> Input::GetMousePosition() {
        return { s_MouseX, s_MouseY };
    }

    float Input::GetMouseX() { return s_MouseX; }
    float Input::GetMouseY() { return s_MouseY; }

}
