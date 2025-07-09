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
    float speed = 5;
    glm::vec3 m_Campos;
    Elyra::Ref<Elyra::Shader> m_Shader;
    Elyra::PerspectiveCameraController m_CameraController;
    Elyra::Ref<Elyra::VertexArray> m_Cube;
};
