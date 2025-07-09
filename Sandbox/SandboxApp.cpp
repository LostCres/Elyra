#include <Elyra.hpp>
#include "ExampleLayer.hpp"

class SandboxApp : public Elyra::Application {
public:
    SandboxApp() {
        EL_INFO("SandboxApp Created!");
        PushLayer(new ExampleLayer());

    }

    ~SandboxApp() override = default;
};

// Entry point for Elyra
Elyra::Application* Elyra::CreateApplication() {
    return new SandboxApp();
}
