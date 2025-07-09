#include <Elyra.hpp>
#include "SandboxLayer.hpp"

class Sandbox : public Elyra::Application {
public:
    Sandbox(const Elyra::WindowProps& Props):Application(Props) {
        PushLayer(new SandboxLayer());
    }

    ~Sandbox() override = default;
};

Elyra::Application* Elyra::CreateApplication() {
    WindowProps Props;
    Props.Title = "Sandbox";
    return new Sandbox(Props);
}
