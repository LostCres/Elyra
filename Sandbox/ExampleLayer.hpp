#pragma once

#include <Elyra.hpp>

class ExampleLayer : public Elyra::Layer {
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate(Elyra::TimeStep ts) override {
        EL_INFO("Delta time: {0} seconds", ts.GetSeconds());
    }

    void OnEvent(Elyra::Event& event) override {
        EL_TRACE("ExampleLayer::Event -> {0}", event.ToString());
    }
};
