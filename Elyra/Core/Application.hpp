#pragma once
#include "Elyra.hpp"
#include "Window.hpp"

namespace Elyra {

    class ELYRA_API Application {
    public:
        void Run();
    private:
        std::unique_ptr<Window> m_Window;
    };

}