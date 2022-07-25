#include "Application.h"
#include "Input.h"
#include "Events/KeyCodes.h"
#include "Windows/OpenGL/OpenGLWindow.h"
#include "Layers/OpenGLInfoLayer.h"

namespace TGEP {
    

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        ASSERT_CORE(!s_Instance, "APPLICATION ALREADY EXISTS");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(OpenGLWindow::Create());
        m_Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        OpenGLInfoLayer* openGLInfoLayer = new OpenGLInfoLayer();
        PushOverlay(openGLInfoLayer);

        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        glGenBuffers(1, &m_VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

        float vertices[9] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        glGenBuffers(1, &m_IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

        unsigned int indices[3] = {
            0, 1, 2
        };

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        std::string vertexSrc = R"(
        #version 460 core

        layout (location = 0) in vec3 aPos;

        out vec3 vColor;

        void main() 
        {

            vColor = aPos;
            gl_Position = vec4(aPos, 1.0);
        }   
        )";

        std::string fragmentSrc = R"(
        #version 460 core

        out vec4 FragColor;
        in vec3 vColor;

        void main()
        {
            FragColor = vec4(vColor * 0.5 + 0.5, 1.0);
        }

        )";

        m_Shader.reset(new OpenGLShader(vertexSrc, fragmentSrc));
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
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            //call OnUpdate() for each layer
            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            //update window
            m_Window->OnUpdate();

        }
    }

    bool Application::OnWindowClose(WindowCloseEvent &e)
    {
        m_Running = false;

        return true;
    }

}