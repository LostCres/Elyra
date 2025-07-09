#pragma once
#include "Elyra.hpp"

class ECSDebugLayer : public Elyra::Layer {
public:
    ECSDebugLayer();
    void OnAttach() override;
    void OnUpdate(Elyra::TimeStep ts) override;
    void OnUIRender() override;

private:
    Elyra::Scene m_Scene;
    Elyra::Entity m_TestEntity;
};