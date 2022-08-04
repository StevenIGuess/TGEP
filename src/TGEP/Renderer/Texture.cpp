#include "pch.h"
#include "Texture.h"
#include "Renderer.h"

#include "../RenderAPI/OpenGL/OpenGLShader.h"
#include "../RenderAPI/OpenGL/OpenGLTexture.h"

namespace TGEP
{
    Ref<Texture2D> Texture2D::Create(const std::string &path)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:     ASSERT_CORE(false, "No Renderer selected"); return nullptr;
            case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLTexture2D>(path);
            case RendererAPI::API::DirectX:  ASSERT_CORE(false, "DirectX not implemented yet"); return nullptr;
            
        }

        ASSERT_CORE(false, "Unknown RendererAPI!");
        return nullptr;
    }
}