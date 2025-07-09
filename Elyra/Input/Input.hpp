#pragma once
#include "ElyraAPI.hpp"
#include "Elyrapch.hpp"
#include "KeyCodes.hpp"  // Your key and mouse button enums or defines

namespace Elyra {

    class ELYRA_API Input {
    public:
        static bool IsKeyPressed(int keycode);
        static bool IsMouseButtonPressed(int button);
        static std::pair<float, float> GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };

}
