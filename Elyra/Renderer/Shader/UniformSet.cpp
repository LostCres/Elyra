#include "Renderer/Shader/UniformSet.hpp"
#include "Renderer/Shader/Shader.hpp"
#include "Renderer/Texture/Texture.hpp"

namespace Elyra {

    uint32_t m_CurrentTextureSlot = 0;

    Ref<UniformSet> UniformSet::Create()
    {
        return CreateRef<UniformSet>();
    }

    void UniformSet::Apply(const Ref<Shader>& shader) const {
        for (const auto& [name, value] : m_Floats)
            shader->SetFloat(name, value);

        for (const auto& [name, value] : m_Vec3s)
            shader->SetFloat3(name, value);

        for (const auto& [name, value] : m_Vec4s)
            shader->SetFloat4(name, value);

        for (const auto& [name, value] : m_Bools)
            shader->SetBool(name, value);

        for (const auto& [name, texture] : m_Textures) {
            texture->Bind(m_CurrentTextureSlot);
            shader->SetInt(name, m_CurrentTextureSlot);
            m_CurrentTextureSlot++;
        }
    }

    void UniformSet::Set(const std::string& name, float value) {
        m_Floats[name] = value;
    }

    void UniformSet::Set(const std::string& name, const glm::vec3& value) {
        m_Vec3s[name] = value;
    }

    void UniformSet::Set(const std::string& name, const glm::vec4& value) {
        m_Vec4s[name] = value;
    }

    void UniformSet::Set(const std::string& name, bool value) {
        m_Bools[name] = value;
    }

    void UniformSet::SetTexture(const std::string& name, const Ref<Texture2D>& texture) {
        m_Textures[name] = texture;
    }

    void UniformSet::ResetTextureSlot() {
        m_CurrentTextureSlot = 0;
    }

}
