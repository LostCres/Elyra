#include "Renderer/Texture/Texture.hpp"
#include "Renderer/OpenGL/OpenGLTexture.hpp"

namespace Elyra {

Ref<Texture2D> Texture2D::Create(const std::string& path) {
    return CreateRef<OpenGLTexture2D>(path);
}

}
