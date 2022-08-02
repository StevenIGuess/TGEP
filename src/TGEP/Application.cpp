#include "pch.h"
#include "Application.h"
#include "Input.h"
#include "Events/KeyCodes.h"
#include "Windows/OpenGL/OpenGLWindow.h"
#include "Layers/OpenGLInfoLayer.h"
#include "Renderer/Renderer.h"


namespace TGEP {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        ASSERT_CORE(!s_Instance, "APPLICATION ALREADY EXISTS");
        s_Instance = this;

        //create windows and set callbacks
        m_Window = std::unique_ptr<Window>(OpenGLWindow::Create());
        m_Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));

        //create all layer and overlays
        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        OpenGLInfoLayer* openGLInfoLayer = new OpenGLInfoLayer();
        PushOverlay(openGLInfoLayer);

#pragma region TEMPORARY DATA TRIANGLE

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

        float vertices[9] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };


        uint32_t indices[3] = {
            0, 1, 2
        };
        
        BufferLayout layout = {
            { ShaderDataType::Float3 }
        };

#pragma endregion

        m_VertexArray.reset(VertexArray::Create());
        printf("%s", "Created vertex array\n");

        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        printf("%s", "Created vertex buffer\n");
        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        printf("%s", "Added vertex buffer to vertex array\n");

        
        m_IndexBuffer.reset(IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));
        printf("%s", "Created index buffer\n");
        m_VertexArray->SetIndexBuffer (m_IndexBuffer);
        printf("%s", "Added index buffer to vertex array\n");
        m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
        printf("%s", "Created shader\n");


#pragma region TEMPORARY DATA SQUARE

        std::string squareVertexSrc = R"(
        #version 460 core

        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec4 aCol;

        out vec4 vCol;

        void main() 
        {

            vCol = aCol;
            gl_Position = vec4(aPos, 1.0);
        }   
        )";

        std::string squareFragmentSrc = R"(
        #version 460 core

        out vec4 FragColor;
        in vec4 vCol;

        void main()
        {
            FragColor = vCol;
        }

        )";

        float squareVertices[4 * 7] = {
            -0.5f, -0.5f, 0.0f,   0.0f, 0.7f, 0.6f, 1.0f,
             0.5f, -0.5f, 0.0f,   0.0f, 0.7f, 0.6f, 1.0f,
             0.5f,  0.5f, 0.0f,   0.0f, 0.7f, 0.6f, 1.0f,
            -0.5f,  0.5f, 0.0f,   0.1f, 0.7f, 0.6f, 1.0f
        };


        uint32_t squareIndices[6] = {
            0, 1, 2,
            2, 3, 0
        };
        
        BufferLayout squareLayout = {
            { ShaderDataType::Float3 },
            { ShaderDataType::Float4 }
        };

#pragma endregion


        m_SquareVertexArray.reset(VertexArray::Create());
        printf("%s", "Created square vertex array\n");

        m_SquareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        printf("%s", "Created square vertex buffer\n");
        m_SquareVertexBuffer->SetLayout(squareLayout);
        m_SquareVertexArray->AddVertexBuffer(m_SquareVertexBuffer);
        printf("%s", "Added sqaure vertex buffer to square vertex array\n");

        
        m_SquareIndexBuffer.reset(IndexBuffer::Create(squareIndices, (sizeof(squareIndices) / sizeof(uint32_t))));
        printf("%s", "Created square index buffer\n");
        m_SquareVertexArray->SetIndexBuffer (m_SquareIndexBuffer);
        printf("%s", "Added square index buffer to suare vertex array\n");
        m_SquareShader.reset(Shader::Create(squareVertexSrc, squareFragmentSrc));
        printf("%s", "Created square shader\n");

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

            RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
            RenderCommand::Clear();

            
            /****Render Code****/
            Renderer::BeginScene();

            m_SquareShader->Bind(); //Temporary 
            Renderer::Push(m_SquareVertexArray);

            m_Shader->Bind(); //Temporary 
            Renderer::Push(m_VertexArray);

            Renderer::EndScene();
            /****Render Code****/
            

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