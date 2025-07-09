#include <Elyra.hpp>

class SandboxApp : public Elyra::Application {
public:
    SandboxApp() {
        EL_INFO("SandboxApp Created!");
    }

    ~SandboxApp() override = default;
};

// Entry point for Elyra
Elyra::Application* Elyra::CreateApplication() {
    return new SandboxApp();
}
