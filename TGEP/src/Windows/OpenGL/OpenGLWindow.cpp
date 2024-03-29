#include "pch.h"
#include "OpenGLWindow.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Input.h"
#include "RenderApi/OpenGl/OpenGLContext.h"


namespace TGEP
{
    Input* Input::s_Instance = new Input();

    static bool GLFWInitalized = false;

    static void GLFWErrorCallback(int error, const char* desc)
    {
        printf("%s%i\n%s%s\n", "GLFWERROR: ", error, "DESCRIPTION: ", desc);
    }

    Window* OpenGLWindow::Create(const WindowProperties& properties)
    {
        return new OpenGLWindow(properties);
    }

    OpenGLWindow::OpenGLWindow(const WindowProperties& properties)
    {
        Init(properties);
    }

    OpenGLWindow::~OpenGLWindow()
    {
        PROFILE_FUNCTION()
        Shutdown();
    }

    void OpenGLWindow::Init(const WindowProperties& properties)
    {
        PROFILE_FUNCTION()
        m_Data.Title = properties.Title;
        m_Data.Width = properties.Width;
        m_Data.Height = properties.Height;



        if (!GLFWInitalized)
        {
            int success = glfwInit();
            ASSERT_CORE(success, "glfwInit() in window.cpp failed");
            glfwSetErrorCallback(GLFWErrorCallback);

            GLFWInitalized = true;
        }

        m_Window = glfwCreateWindow((int)properties.Width, (int)properties.Height, m_Data.Title.c_str(), nullptr, nullptr);

        m_Context = new OpenGLContext(m_Window);

        m_Context->Init();

        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        //GLFW callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                data.Width = width;
                data.Height = height;

                WindowResizedEvent event(width, height);
                data.EventCallback(event);
            });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                WindowCloseEvent event;
                data.EventCallback(event);
            });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                switch (action)
                {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, true);
                    data.EventCallback(event);
                    break;
                }
                }
            });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                KeyTypedEvent event(keycode);
                data.EventCallback(event);
            });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                switch (action)
                {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                }
            });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                MouseScrolledEvent event((float)xOffset, (float)yOffset);
                data.EventCallback(event);
            });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                MouseMovedEvent event((float)xPos, (float)yPos);
                data.EventCallback(event);
            });


    }

    void OpenGLWindow::Shutdown()
    {
        PROFILE_FUNCTION()
        glfwDestroyWindow(m_Window);
    }

    void OpenGLWindow::OnUpdate()
    {
        PROFILE_FUNCTION()
        glfwPollEvents();
        m_Context->SwapBuffers();

    }

    void OpenGLWindow::SetVSync(bool enabled)
    {
        PROFILE_FUNCTION()
        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }

        m_Data.VSync = enabled;
    }

    bool OpenGLWindow::IsVsync() const
    {
        return m_Data.VSync;
    }
}