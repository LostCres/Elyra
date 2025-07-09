#ifdef ELYRA_PLATFORM_WINDOWS

#include <Core/Application.hpp>

extern Elyra::Application* Elyra::CreateApplication();

int main(int argc, char** argv) {
    Elyra::Log::Init();
    auto app = Elyra::CreateApplication();
    app->Run();
    delete app;
}

#endif
