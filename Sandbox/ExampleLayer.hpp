#pragma once

#include <Elyra.hpp>

class ExampleLayer : public Elyra::Layer {
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override {
        EL_TRACE("ExampleLayer::Update");
    }

    void OnEvent(Elyra::Event& event) override {
        EL_TRACE("ExampleLayer::Event -> {0}", event.ToString());
    }
};
