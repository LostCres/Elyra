#pragma once

#include <Elyra.hpp>

class SandboxLayer : public Elyra::Layer {
public:
    SandboxLayer();
    virtual ~SandboxLayer() = default;

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(Elyra::TimeStep ts) override;
    void OnImGuiRender(ImGuiContext* context) override;
    void OnEvent(Elyra::Event& e) override;

private:
    Elyra::Ref<Elyra::Shader> m_Shader;
    Elyra::Ref<Elyra::VertexArray> m_VertexArray;
    Elyra::OrthographicCamera m_Camera;
};
