#include "pch.h"
#include "OpenGLContext.h"


namespace TGEP
{

    OpenGLContext::OpenGLContext(GLFWwindow* window) : m_Window(window)
    {
        ASSERT_CORE(window, "Window is null");
    }

    void OpenGLContext::Init()
    {
        PROFILE_FUNCTION()
        glfwMakeContextCurrent(m_Window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        ASSERT_CORE(status, "FAILED TO LOAD GLAD");

    }

    void OpenGLContext::SwapBuffers()
    {
        PROFILE_FUNCTION()
        glfwSwapBuffers(m_Window);
    }
}