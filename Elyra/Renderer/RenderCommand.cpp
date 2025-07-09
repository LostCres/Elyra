#include "Elyrapch.hpp"
#include "RenderCommand.hpp"
#include "OpenGL/OpenGLRendererAPI.hpp"

namespace Elyra {

    Scope<RendererAPI> RenderCommand::s_RenderAPI = CreateScope<OpenGLRendererAPI>();

}
