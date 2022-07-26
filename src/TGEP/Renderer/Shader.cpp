#include "pch.h"
#include "Shader.h"

#include "Renderer.h"
#include "../RenderAPI/OpenGl/OpenGLShader.h"

namespace TGEP
{
    Shader* Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        switch(Renderer::GetRendererAPI())
        {
            case RendererAPI::None:     ASSERT_CORE(false, "No Renderer selected") return nullptr;
            case RendererAPI::OpenGL:   return new OpenGLShader(vertexSrc, fragmentSrc);
            case RendererAPI::DirectX:  ASSERT_CORE(false, "DirectX not implemented yet") return nullptr;
            
        }

        ASSERT_CORE(false, "Unknown RendererAPI!")
        return nullptr;
    }
}