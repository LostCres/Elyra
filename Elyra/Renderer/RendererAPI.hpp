#pragma once
#include "ElyraAPI.hpp"
#include "Core/Core.hpp"
#include <glm/glm.hpp>
#include "Renderer/VertexArray.hpp"

namespace Elyra {

    class ELYRA_API RendererAPI {
    public:
        enum class API {
            None = 0,
            OpenGL = 1
        };

    public:
        virtual ~RendererAPI() = default;

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

        static API GetAPI() { return s_API; }

    protected:
        static API s_API;
    };

}
