#include <Elyra.hpp>
#include "SandboxLayer.hpp"
#include "ECSDebugLayer.hpp"

class Sandbox : public Elyra::Application {
public:
    Sandbox(const Elyra::WindowProps& Props):Application(Props) {

        EL_INFO("Sandbox Starting.");
        PushLayer(new SandboxLayer());
        PushLayer(new ECSDebugLayer());

    }

    ~Sandbox() override{
        EL_INFO("Sandbox Shutting Down.");
    }
};

Elyra::Application* Elyra::CreateApplication() {
    WindowProps Props;
    Props.Title = "Sandbox";
    return new Sandbox(Props);
}
