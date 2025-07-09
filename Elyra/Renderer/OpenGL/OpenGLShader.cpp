#include "Elyrapch.hpp"
#include "OpenGLShader.hpp"
#include <glad/glad.h>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include "Core/Log.hpp"

namespace Elyra {

    static GLenum ShaderTypeFromString(const std::string& type) {
        if (type == "vertex")   return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;
        EL_CORE_ASSERT(false, "Unknown shader type: {0}", type);
        return 0;
    }

    OpenGLShader::OpenGLShader(const std::string& filepath) {
        std::ifstream in(filepath, std::ios::in | std::ios::binary);
        std::string source;
        if (in) {
            in.seekg(0, std::ios::end);
            size_t size = in.tellg();
            source.resize(size);
            in.seekg(0);
            in.read(&source[0], size);
            in.close();
        } else {
            EL_CORE_ASSERT(false, "Failed to open shader file: {0}", filepath);
        }

        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind('.');
        auto count = (lastDot == std::string::npos) ? filepath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filepath.substr(lastSlash, count);

        auto shaderSources = PreProcess(source);
        Compile(shaderSources);
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_Name(name) {
        std::unordered_map<GLenum, std::string> sources = {
            {GL_VERTEX_SHADER, vertexSrc},
            {GL_FRAGMENT_SHADER, fragmentSrc}
        };
        Compile(sources);
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind() const {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const {
        glUseProgram(0);
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source) {
        std::unordered_map<GLenum, std::string> shaderSources;

        const char* typeToken = "#type";
        size_t pos = source.find(typeToken, 0);
        while (pos != std::string::npos) {
            size_t eol = source.find_first_of("\r\n", pos);
            EL_CORE_ASSERT(eol != std::string::npos, "Syntax error");
            size_t begin = pos + strlen(typeToken);
            std::string type = source.substr(begin, eol - begin);
            GLenum shaderType = ShaderTypeFromString(type);

            size_t nextLine = source.find_first_not_of("\r\n", eol);
            size_t nextType = source.find(typeToken, nextLine);
            shaderSources[shaderType] = source.substr(nextLine,
                nextType == std::string::npos ? source.size() - nextLine : nextType - nextLine);

            pos = nextType;
        }

        return shaderSources;
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
        GLuint program = glCreateProgram();
        std::vector<GLenum> shaderIDs;

        for (auto& [type, source] : shaderSources) {
            GLuint shader = glCreateShader(type);
            const char* src = source.c_str();
            glShaderSource(shader, 1, &src, nullptr);
            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE) {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
                glDeleteShader(shader);

                EL_CORE_ERROR("{0}", infoLog.data());
                EL_CORE_ASSERT(false, "Shader compilation failure");
                return;
            }

            glAttachShader(program, shader);
            shaderIDs.push_back(shader);
        }

        glLinkProgram(program);
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
            glDeleteProgram(program);

            for (auto id : shaderIDs)
                glDeleteShader(id);

            EL_CORE_ERROR("{0}", infoLog.data());
            EL_CORE_ASSERT(false, "Shader link failure");
            return;
        }

        for (auto id : shaderIDs) {
            glDetachShader(program, id);
            glDeleteShader(id);
        }

        m_RendererID = program;
    }

    void OpenGLShader::SetInt(const std::string& name, int value) {
        UploadUniformInt(name, value);
    }

    void OpenGLShader::SetFloat(const std::string& name, float value) {
        UploadUniformFloat(name, value);
    }

    void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value) {
        UploadUniformFloat3(name, value);
    }

    void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value) {
        UploadUniformFloat4(name, value);
    }

    void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value) {
        UploadUniformMat4(name, value);
    }

    void OpenGLShader::UploadUniformInt(const std::string& name, int value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformFloat(const std::string& name, float value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

}
