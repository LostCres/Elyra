#include "Renderer/Core/VertexArray.hpp"
#include "Renderer/OpenGL/OpenGLVertexArray.hpp"

namespace Elyra {

    Ref<VertexArray> VertexArray::Create() {
        return CreateRef<OpenGLVertexArray>();
    }

}
