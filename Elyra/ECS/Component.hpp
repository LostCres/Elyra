#pragma once
#include <glm/glm.hpp>
#include <string>
#include "ElyraAPI.hpp"
namespace Elyra {

    struct ELYRA_API TagComponent {
        std::string Tag;
        TagComponent() = default;
        TagComponent(std::string tag) : Tag(std::move(tag)) {}
    };

    struct ELYRA_API TransformComponent {
        glm::vec3 Position{0.0f};
        glm::vec3 Rotation{0.0f};
        glm::vec3 Scale{1.0f};
    };
}