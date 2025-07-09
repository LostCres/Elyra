#include "Elyrapch.hpp"
#include "Shader.hpp"
#include "Renderer/Core/Renderer.hpp"
#include "Renderer/OpenGL/OpenGLShader.hpp"
#include "Core/Log.hpp"

namespace Elyra {

    Ref<Shader> Shader::Create(const std::string& filepath) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                EL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLShader>(filepath);
        }

        EL_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                EL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        EL_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& vertexPath, const std::string& fragmentPath) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                EL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLShader>(vertexPath, fragmentPath);
        }

        EL_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
