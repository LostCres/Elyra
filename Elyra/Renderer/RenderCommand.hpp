#pragma once
#include "ElyraAPI.hpp"
#include "Core/Core.hpp"
#include "Renderer/RendererAPI.hpp"

namespace Elyra {

    class ELYRA_API RenderCommand {
    public:
        static void Init() {
            // Init the API — optional code for OpenGL setup here
        }

        static void SetClearColor(const glm::vec4& color) {
            s_RenderAPI->SetClearColor(color);
        }

        static void Clear() {
            s_RenderAPI->Clear();
        }

        static void DrawIndexed(const Ref<VertexArray>& vertexArray) {
            s_RenderAPI->DrawIndexed(vertexArray);
        }

    private:
        static Scope<RendererAPI> s_RenderAPI;
    };

}
