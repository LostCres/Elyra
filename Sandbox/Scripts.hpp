#pragma once
#include "Elyra.hpp"

class SpinScript : public Elyra::ScriptableEntity {
public:
    void OnUpdate(Elyra::TimeStep ts) override {
        auto& transform = GetComponent<Elyra::TransformComponent>();
        transform.Rotation.y += ts * glm::radians(180.0f);
    }
};

class sphererotate : public Elyra::ScriptableEntity{
    public:
        void OnUpdate(Elyra::TimeStep ts) override{
            auto& transform = GetComponent<Elyra::TransformComponent>();
            transform.Rotation.y += ts * glm::radians(45.0f);
            transform.Position.y = 2 + (0.5f * sin(ts.Now()*2));
        }
};


 