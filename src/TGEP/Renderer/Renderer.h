#pragma once

#include "RenderCommand.h"

namespace TGEP 
{

    class Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();

        static void Push(const std::shared_ptr<VertexArray> &va);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    };  
}