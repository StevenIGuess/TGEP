#include "Window.h"

namespace TGEP 
{
    static bool GLFWInitalized = false;

    Window* Window::Create(const WindowProperties& properties)
    {
        return new Window(properties);
    }

    Window::Window(const WindowProperties& properties)
    {
        Init(properties);
    }

    Window::~Window()
    {
        Shutdown();
    }

    void Window::Init(const WindowProperties& properties)
    {
        m_Data.Title = properties.Title;
        m_Data.Width = properties.Width;
        m_Data.Height = properties.Height;

        LOG_CORE_INFO("CREATED WINDOW '{0}' ({1}, {2})", properties.Title, properties.Width, properties.Height);

        if(!GLFWInitalized)
        {
            int success = glfwInit();
            ASSERT_CORE(success, "glfwInit() in window.cpp failed");

            GLFWInitalized = true;
        }

        m_Window = glfwCreateWindow((int)properties.Width, (int)properties.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
    }

    void Window::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void Window::SetVSync(bool enabled)
    {
        if (enabled)
        {
            glfwSwapInterval(1);
        } else
        {
            glfwSwapInterval(0);
        }

        m_Data.VSync = enabled;
    }

    bool Window::IsVsync() const
    {
        return m_Data.VSync;
    }
}