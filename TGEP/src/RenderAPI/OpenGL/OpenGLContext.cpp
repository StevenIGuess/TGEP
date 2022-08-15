#include "OpenGLContext.h"
#include "pch.h"

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

    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_Window);
    }
}