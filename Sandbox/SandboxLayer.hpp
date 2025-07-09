#pragma once

#include <Elyra.hpp>

class SandboxLayer : public Elyra::Layer {
public:
    SandboxLayer();
    virtual ~SandboxLayer() = default;

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(Elyra::TimeStep ts) override;
    void OnUIRender() override;
    void OnEvent(Elyra::Event& e) override;

private:
    
};
