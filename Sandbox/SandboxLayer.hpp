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
    float m_LastFrameTime = 0.0f;
    bool m_ViewportFocused = false;
    bool m_ViewportHovered = false;
    glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
};
