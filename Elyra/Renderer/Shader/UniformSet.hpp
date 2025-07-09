#pragma once
#include "ElyraAPI.hpp"
#include "Renderer/Shader/Shader.hpp"
#include "Renderer/Texture/Texture.hpp"
#include "Elyrapch.hpp"
#include <glm/glm.hpp>

namespace Elyra {

    class ELYRA_API UniformSet {
    public:

        static Ref<UniformSet> Create();

        void Set(const std::string& name, float value);
        void Set(const std::string& name, const glm::vec3& value);
        void Set(const std::string& name, const glm::vec4& value);
        void Set(const std::string& name, int value);
        void Set(const std::string& name, bool value);
        void SetTexture(const std::string& name, const Ref<Texture2D>& texture);

        void ResetTextureSlot();

        void Apply(const Ref<Shader>& shader) const;

    private:
        std::unordered_map<std::string, float> m_Floats;
        std::unordered_map<std::string, glm::vec3> m_Vec3s;
        std::unordered_map<std::string, glm::vec4> m_Vec4s;
        std::unordered_map<std::string, int> m_Ints;
        std::unordered_map<std::string, bool> m_Bools;
        std::unordered_map<std::string, Ref<Texture2D>> m_Textures;
    };

} // namespace Elyra
