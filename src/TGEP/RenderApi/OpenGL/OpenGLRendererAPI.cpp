#include "pch.h"
#include "OpenGLRendererAPI.h"

namespace TGEP 
{
    void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color)
    {
        glClearColor(color.x, color.y, color.z, color.w);
        
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray> &va)
    {
        glDrawElements(GL_TRIANGLES, va->GetIndexBuffer()->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
    }
}