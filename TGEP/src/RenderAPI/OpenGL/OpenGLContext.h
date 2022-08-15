#pragma once 

#include "../../Renderer/RenderContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace TGEP
{
    class OpenGLContext : public RenderContext
    {
    public:

        OpenGLContext(GLFWwindow* window);

        virtual void Init() override;
        virtual void SwapBuffers() override;
    private:

        GLFWwindow* m_Window;
    };

}