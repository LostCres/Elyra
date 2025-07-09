#pragma once
#include <glad/glad.h>
#include "Elyrapch.hpp"
#include "Renderer/Shader.hpp"
#include <glm/glm.hpp>
#include "Core/Core.hpp"

namespace Elyra {

    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& filepath);
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath);

        ~OpenGLShader();

        void Bind() const override;
        void Unbind() const override;

        const std::string& GetName() const override { return m_Name; }

        void SetInt(const std::string& name, int value) override;
        void SetFloat(const std::string& name, float value) override;
        void SetFloat3(const std::string& name, const glm::vec3& value) override;
        void SetFloat4(const std::string& name, const glm::vec4& value) override;
        void SetMat4(const std::string& name, const glm::mat4& value) override;

    private:
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

        void UploadUniformInt(const std::string& name, int value);
        void UploadUniformFloat(const std::string& name, float value);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
        void UploadUniformMat4(const std::string& name, const glm::mat4& value);

    private:
        uint32_t m_RendererID;
        std::string m_Name;
    };

}
