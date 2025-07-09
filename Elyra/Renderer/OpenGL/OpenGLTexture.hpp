#pragma once
#include <glad/glad.h>
#include "Renderer/Texture/Texture.hpp"

namespace Elyra {

class OpenGLTexture2D : public Texture2D {
public:
    OpenGLTexture2D(const std::string& path);
    ~OpenGLTexture2D();

    uint32_t GetWidth() const override { return m_Width; }
    uint32_t GetHeight() const override { return m_Height; }
    uint32_t GetRendererID() const override { return m_RendererID; }

    void Bind(uint32_t slot = 0) const override;

    bool operator==(const Texture2D& other) const override {
        return m_RendererID == other.GetRendererID();
    }

private:
    std::string m_Path;
    uint32_t m_Width, m_Height;
    uint32_t m_RendererID;
    GLenum m_InternalFormat, m_DataFormat;
};

}
