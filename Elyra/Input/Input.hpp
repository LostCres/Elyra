#pragma once
#include "ElyraAPI.hpp"
#include "Elyrapch.hpp"
#include "Core/KeyCodes.hpp"  // Your key and mouse button enums or defines
#include "Events/Event.hpp"

namespace Elyra {

    class ELYRA_API Input {
    public:
        static void OnEvent(Event& e);

        static bool IsKeyPressed(int keycode);
        static bool IsMouseButtonPressed(int button);
        static std::pair<float, float> GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    private:
        static bool s_KeyStates[EL_KEY_LAST];
        static bool s_MouseButtonStates[EL_MOUSE_BUTTON_LAST];
        static float s_MouseX, s_MouseY;
    };

}
