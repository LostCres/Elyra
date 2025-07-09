#pragma once
#include "ElyraAPI.hpp"
#include "Renderer/Mesh/Mesh.hpp"

namespace Elyra::Primitives {

    ELYRA_API Ref<Mesh> Cube(float width = 1.0f, float height = 1.0f, float depth = 1.0f);
    ELYRA_API Ref<Mesh> Plane(float width = 1.0f, float length = 1.0f);
    ELYRA_API Ref<Mesh> Sphere(float radius = 0.5f, uint32_t segments = 16, uint32_t rings = 16);

}
