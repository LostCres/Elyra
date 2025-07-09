#include "VertexArray.hpp"
#include "OpenGL/OpenGLVertexArray.hpp"

namespace Elyra {

    Ref<VertexArray> VertexArray::Create() {
        return CreateRef<OpenGLVertexArray>();
    }

}
