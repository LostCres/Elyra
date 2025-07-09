#pragma once
#include "Elyra.hpp"

class SpinScript : public Elyra::ScriptableEntity {
public:
    void OnUpdate(Elyra::TimeStep ts) override {
        auto& transform = GetComponent<Elyra::TransformComponent>();
        transform.Rotation.y += ts * glm::radians(180.0f);
    }
};
