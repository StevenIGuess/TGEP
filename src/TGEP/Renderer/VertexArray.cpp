#include "VertexArray.h"
#include "pch.h"
#include "RenderAPI/OpenGL/OpenGLVertexArray.h"
#include "Renderer/Renderer.h"

namespace TGEP {

    VertexArray* VertexArray::Create()
    {
        switch(Renderer::GetRendererAPI())
        {
            case RendererAPI::None:     ASSERT_CORE(false, "No Renderer selected") return nullptr;
            case RendererAPI::OpenGL:   return new OpenGLVertexArray();
            case RendererAPI::DirectX:  ASSERT_CORE(false, "DirectX not implemented yet") return nullptr;
            
        }

        ASSERT_CORE(false, "Unknown RendererAPI!")
        return nullptr;
    }
}