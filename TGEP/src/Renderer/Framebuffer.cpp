#include "pch.h"
#include "Framebuffer.h"
#include "RenderAPI/OpenGL/OpenGLFramebuffer.h"
#include "Renderer.h"


namespace TGEP
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSettings& settings)
	{
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:     ASSERT_CORE(false, "No Renderer selected"); return nullptr;
        case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLFramebuffer>(settings);
        case RendererAPI::API::DirectX:  ASSERT_CORE(false, "DirectX not implemented yet"); return nullptr;

        }

        ASSERT_CORE(false, "Unknown RendererAPI!");
        return nullptr;
	}
}