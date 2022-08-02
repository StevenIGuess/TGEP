#include "pch.h"
#include "Renderer.h"

namespace TGEP 
{
    void Renderer::BeginScene()
    {

    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Push(const std::shared_ptr<VertexArray> &va)
    {
        va->Bind();
        RenderCommand::DrawIndexed(va);
    }
}