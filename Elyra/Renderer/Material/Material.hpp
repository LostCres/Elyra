#pragma once
#include "ElyraAPI.hpp"
#include "Renderer/Shader/Shader.hpp"
#include "Renderer/Texture/Texture.hpp"
#include "Renderer/Shader/UniformSet.hpp"
#include "Elyrapch.hpp"
#include <glm/glm.hpp>

namespace Elyra {

class ELYRA_API Material {
public:
    Material();
    ~Material(); // Explicitly declare the destructor
    static Ref<Material> Create();
    static Ref<Material> Create(const Ref<Shader>& shader);

    static void SetDefaultShader(const Ref<Shader>& shader);
    static Ref<Shader> GetDefaultShader();

    void Bind() const;

    void SetShader(const Ref<Shader>& shader){m_Shader = shader;}
    Ref<Shader> GetShader() const { return m_Shader; }

    // Set only static/shared properties like base color, tiling, metallic, etc.
    void Set(const std::string& name, float value);
    void Set(const std::string& name, const glm::vec3& value);
    void Set(const std::string& name, const glm::vec4& value);
    void SetTexture(const std::string& name, const Ref<Texture2D>& texture);

    static void SetGlobalUniforms(const Ref<UniformSet>& uniforms); //for global uniforms
    static Ref<UniformSet> GetGlobalUniform() {return s_GlobalUniforms;}

    bool HasTexture(const std::string& name) const;

    void ApplyProperties() const;
    void ClearProperties();

private:
    Ref<Shader> m_Shader;
    static Ref<Shader> s_DefaultShader;

    static Ref<UniformSet> s_GlobalUniforms;

    std::unordered_map<std::string, float> m_Floats;
    std::unordered_map<std::string, glm::vec3> m_Vec3s;
    std::unordered_map<std::string, glm::vec4> m_Vec4s;
    std::unordered_map<std::string, Ref<Texture2D>> m_Textures;
};

}
