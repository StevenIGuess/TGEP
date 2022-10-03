#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "../RenderAPI/OpenGl/OpenGLBuffer.h"


namespace TGEP
{

    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:     ASSERT_CORE(false, "No Renderer selected") return nullptr;
        case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLVertexBuffer>(size);
        case RendererAPI::API::DirectX:  ASSERT_CORE(false, "DirectX not implemented yet") return nullptr;

        }

        ASSERT_CORE(false, "Unknown RendererAPI!")
            return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(float* verticies, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:     ASSERT_CORE(false, "No Renderer selected") return nullptr;
        case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLVertexBuffer>(verticies, size);
        case RendererAPI::API::DirectX:  ASSERT_CORE(false, "DirectX not implemented yet") return nullptr;

        }

        ASSERT_CORE(false, "Unknown RendererAPI!")
            return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:     ASSERT_CORE(false, "No Renderer selected") return nullptr;
        case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLIndexBuffer>(indices, count);
        case RendererAPI::API::DirectX:  ASSERT_CORE(false, "DirectX not implemented yet") return nullptr;

        }

        ASSERT_CORE(false, "Unknown RendererAPI!")
            return nullptr;
    }
}