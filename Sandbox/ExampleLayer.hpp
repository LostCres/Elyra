#pragma once

#include <Elyra.hpp>
#include<string>

class ExampleLayer : public Elyra::Layer {
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate(Elyra::TimeStep ts) override {
        //EL_INFO("Delta time: {0} seconds", ts.GetSeconds());
    }

    void OnEvent(Elyra::Event& e) override {
        if (e.GetEventType() == Elyra::EventType::KeyPressed)
        {
            Elyra::KeyPressedEvent& keyEvent = static_cast<Elyra::KeyPressedEvent&>(e);
            EL_INFO("KeyPressed: {}",static_cast<int>(keyEvent.GetKeyCode()));
        }

        if (e.GetEventType() == Elyra::EventType::MouseButtonPressed)
        {
            Elyra::MouseButtonPressedEvent& mouseEvent = static_cast<Elyra::MouseButtonPressedEvent&>(e);
            EL_INFO("MouseButtonPressed: {}", static_cast<int>(mouseEvent.GetMouseButton()));
        }

        // Forward to base
        Layer::OnEvent(e);
    }
};
