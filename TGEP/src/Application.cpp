#include "pch.h"
#include "Application.h"
#include "Input.h"
#include "Events/KeyCodes.h"
#include "Windows/OpenGL/OpenGLWindow.h"
#include "Renderer/Renderer.h"
#include "Renderer/Camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace TGEP {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        PROFILE_FUNCTION()
        ASSERT_CORE(!s_Instance, "APPLICATION ALREADY EXISTS");
        s_Instance = this;


        //create windows and set callbacks
        WindowProperties windowProperties;
        m_Window = std::unique_ptr<Window>(OpenGLWindow::Create(windowProperties));
        m_Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));
        m_Window->SetVSync(false);

        Renderer::Init();

        //create all layer and overlays
        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        OpenGLInfoLayer* openGLInfoLayer = new OpenGLInfoLayer();
        PushOverlay(openGLInfoLayer);
    }

    Application::~Application()
    {

    }

    void Application::PushLayer(Layer* layer)
    {
        PROFILE_FUNCTION();
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        PROFILE_FUNCTION();
        m_LayerStack.PushLayer(overlay);
        overlay->OnAttach();
    }

    void Application::OnEvent(Event& e)
    {
        PROFILE_FUNCTION();
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FUNC(Application::OnWindowResize));


        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
            {
                break;
            }
        }
    }

    void Application::Run()
    {
        PROFILE_FUNCTION();
        while (m_Running)
        {
            float time = (float)glfwGetTime(); // replace with independent time function
            DeltaTime deltaTime = time - m_LastFrameTime;
            m_LastFrameTime = time;

            //call OnUpdate() for each layer
            if (!m_Minimized)
            {
                PROFILE_SCOPED("Layer->OnUpdate");
                for (Layer* layer : m_LayerStack)
                {
                    layer->OnUpdate(deltaTime);
                }
            }

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
            {
                PROFILE_SCOPED("Layer->OnImGuiRender");
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            //update window
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;

        return true;
    }

    bool Application::OnWindowResize(WindowResizedEvent& e)
    {
        PROFILE_FUNCTION();
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;

        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }

}