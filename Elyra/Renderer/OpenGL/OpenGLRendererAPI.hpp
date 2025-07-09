#pragma once

#include "Renderer/Core/RendererAPI.hpp"

namespace Elyra {

    class OpenGLRendererAPI : public RendererAPI {
    public:
        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
    };

}
