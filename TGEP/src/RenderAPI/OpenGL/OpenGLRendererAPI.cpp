#include "pch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace TGEP
{
    void OpenGLRendererAPI::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.x, color.y, color.z, color.w);

    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& va)
    {
        glDrawElements(GL_TRIANGLES, va->GetIndexBuffer()->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
    }

}