#include "Renderer/Material/Material.hpp"

namespace Elyra {

    Ref<Shader> Material::s_DefaultShader = nullptr;

    Material::Material()
    {
        m_Shader = s_DefaultShader;
    }

    Ref<Material> Material::Create() {
        return CreateRef<Material>();
    }

    Ref<Material> Material::Create(const Ref<Shader>& shader) {
        Ref<Material> material = CreateRef<Material>();
        material->SetShader(shader);
        return material;
    }


    void Material::SetDefaultShader(const Ref<Shader>& shader) {
        s_DefaultShader = shader;
    }

    Ref<Shader> Material::GetDefaultShader() {
        return s_DefaultShader;
    }

    Ref<UniformSet> Material::s_GlobalUniforms = nullptr;

    void Material::SetGlobalUniforms(const Ref<UniformSet>& uniforms) {
        s_GlobalUniforms = uniforms;
    }

    void Material::Bind() const {
        m_Shader->Bind();

        ApplyProperties(); // Apply material properties only (not per-object)

        if (s_GlobalUniforms) {
            s_GlobalUniforms->ResetTextureSlot();
            s_GlobalUniforms->Apply(m_Shader);
        }
    }

    void Material::ApplyProperties() const {
        for (const auto& [name, value] : m_Floats)
            m_Shader->SetFloat(name, value);

        for (const auto& [name, value] : m_Vec3s)
            m_Shader->SetFloat3(name, value);

        for (const auto& [name, value] : m_Vec4s)
            m_Shader->SetFloat4(name, value);

        uint32_t slot = 0;
        for (const auto& [name, texture] : m_Textures) {
            texture->Bind(slot);
            m_Shader->SetInt(name, slot);
            slot++;
        }
    }

    bool Material::HasTexture(const std::string& name) const {
        return m_Textures.contains(name);
    }

    void Material::Set(const std::string& name, float value) {
        m_Floats[name] = value;
    }

    void Material::Set(const std::string& name, const glm::vec3& value) {
        m_Vec3s[name] = value;
    }

    void Material::Set(const std::string& name, const glm::vec4& value) {
        m_Vec4s[name] = value;
    }

    void Material::SetTexture(const std::string& name, const Ref<Texture2D>& texture) {
        m_Textures[name] = texture;

    }
}
