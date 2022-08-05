#include "pch.h"
#include "Shader.h"

#include "Renderer.h"
#include "../RenderAPI/OpenGl/OpenGLShader.h"

namespace TGEP
{
    Shader* Shader::Create(const std::string &path)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:     ASSERT_CORE(false, "No Renderer selected"); return nullptr;
            case RendererAPI::API::OpenGL:   return new OpenGLShader(path);
            case RendererAPI::API::DirectX:  ASSERT_CORE(false, "DirectX not implemented yet"); return nullptr;
            
        }

        ASSERT_CORE(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Shader* Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:     ASSERT_CORE(false, "No Renderer selected"); return nullptr;
            case RendererAPI::API::OpenGL:   return new OpenGLShader(vertexSrc, fragmentSrc);
            case RendererAPI::API::DirectX:  ASSERT_CORE(false, "DirectX not implemented yet"); return nullptr;
            
        }

        ASSERT_CORE(false, "Unknown RendererAPI!");
        return nullptr;
    }
}