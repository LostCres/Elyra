#pragma once
#include "ElyraAPI.hpp"
#include "Renderer/VertexArray.hpp"
#include "Renderer/Buffer.hpp"
#include "Core/Core.hpp"

namespace Elyra {

    class ELYRA_API CubeMesh {
    public:
        static Ref<VertexArray> Create();
    };

}