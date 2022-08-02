#include "pch.h"
#include "RenderCommand.h"

#include "RenderAPI/OpenGL/OpenGLRendererAPI.h"

namespace TGEP
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI; //temporary, later will be dynamically set
}