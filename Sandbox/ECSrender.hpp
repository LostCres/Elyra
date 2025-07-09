#pragma once

#include <Elyra.hpp>

class ECSrender : public Elyra::Layer {

public:
    ECSrender();
    virtual ~ECSrender() = default;

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(Elyra::TimeStep ts) override;
    void OnUIRender() override;
    void OnEvent(Elyra::Event& e) override;

private:
    std::shared_ptr<Elyra::Scene> m_Scene;
};
