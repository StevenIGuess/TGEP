#include "OpenGLContext.h"
#include "../../pch.h"
#include "../../Log.h"

#include <GLFW/glfw3.h>

namespace TGEP
{

    OpenGLContext::OpenGLContext(GLFWwindow* window) : m_Window(window)
    {
        ASSERT_CORE(window, "Window is null");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_Window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        ASSERT_CORE(status, "FAILED TO LOAD GLAD");

        LOG_CORE_INFO("OpenGL Renderer: {0} {1} OpenGl Version: {2}", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_Window);
    }
}