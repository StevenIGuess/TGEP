#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "../RenderAPI/OpenGl/OpenGLBuffer.h"


namespace TGEP
{
    VertexBuffer* VertexBuffer::Create(float* verticies, uint32_t size)
    {
        switch(Renderer::GetRendererAPI())
        {
            case RendererAPI::None:     ASSERT_CORE(false, "No Renderer selected") return nullptr;
            case RendererAPI::OpenGL:   return new OpenGLVertexBuffer(verticies, size);
            case RendererAPI::DirectX:  ASSERT_CORE(false, "DirectX not implemented yet") return nullptr;
            
        }

        ASSERT_CORE(false, "Unknown RendererAPI!")
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t *indices, uint32_t count)
    {
        switch(Renderer::GetRendererAPI())
        {
            case RendererAPI::None:     ASSERT_CORE(false, "No Renderer selected") return nullptr;
            case RendererAPI::OpenGL:   return new OpenGLIndexBuffer(indices, count);
            case RendererAPI::DirectX:  ASSERT_CORE(false, "DirectX not implemented yet") return nullptr;
            
        }

        ASSERT_CORE(false, "Unknown RendererAPI!")
        return nullptr;
    }
}