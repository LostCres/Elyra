#pragma once
#include "ElyraAPI.hpp"
#include "Renderer/Shader/Shader.hpp"
#include "Elyrapch.hpp"
#include <glm/glm.hpp>

namespace Elyra {

class ELYRA_API Material {
public:
    Material();
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
    //void SetTexture(const std::string& name, const Ref<Texture>& texture);

    void ApplyProperties() const;

private:
    Ref<Shader> m_Shader;
    static Ref<Shader> s_DefaultShader;

    std::unordered_map<std::string, float> m_Floats;
    std::unordered_map<std::string, glm::vec3> m_Vec3s;
    std::unordered_map<std::string, glm::vec4> m_Vec4s;
    //std::unordered_map<std::string, Ref<Texture>> m_Textures;
};

}
