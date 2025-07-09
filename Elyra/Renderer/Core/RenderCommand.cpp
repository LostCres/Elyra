#include "Elyrapch.hpp"
#include "Renderer/Core/RenderCommand.hpp"
#include "Renderer/OpenGL/OpenGLRendererAPI.hpp"

namespace Elyra {

    Scope<RendererAPI> RenderCommand::s_RenderAPI = CreateScope<OpenGLRendererAPI>();

}
