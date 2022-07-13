#include "Application.h"
#include "Input.h"
#include "Log.h"

namespace TGEP {
    

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        ASSERT_CORE(!s_Instance, "APPLICATION ALREADY EXISTS");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));
    }

    Application::~Application()
    {

    }

    void Application::PushLayer(Layer *layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *overlay)
    {
        m_LayerStack.PushLayer(overlay);
        overlay->OnAttach();
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::OnWindowClose));

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
        while (m_Running)
        {

            //call OnUpdate() for each layer
            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }

            LOG_CORE_INFO("KEY 'A' PRESSED = {0}", Input::IsKeyPressed(GLFW_KEY_A));
            auto[x, y] = Input::GetMousePosition();
            LOG_CORE_WARN("MOUSE POS = {0}, {1}", x, y);

            //update window
            m_Window->OnUpdate();
            //clear color 
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent &e)
    {
        m_Running = false;

        return true;
    }

}