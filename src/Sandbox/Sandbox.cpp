#include <TGEP.h>

class TestLayer : public TGEP::Layer
{
public:
    TestLayer() : TGEP::Layer("TestLayer"), m_Camera(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f) 
    {
        std::string vertexSrc = R"(
        #version 460 core

        layout (location = 0) in vec3 aPos;
        uniform mat4 u_ViewProjection;

        out vec3 vColor;

        void main() 
        {

            vColor = aPos;
            gl_Position = u_ViewProjection * vec4(aPos, 1.0);
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
        
        TGEP::BufferLayout layout = {
            { TGEP::ShaderDataType::Float3 }
        };

        m_VertexArray.reset(TGEP::VertexArray::Create());

        std::shared_ptr<TGEP::VertexBuffer> VB;
        VB.reset(TGEP::VertexBuffer::Create(vertices, sizeof(vertices)));
        VB->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(VB);

        std::shared_ptr<TGEP::IndexBuffer> IB;
        IB.reset(TGEP::IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));
        m_VertexArray->SetIndexBuffer (IB);

        m_Shader.reset(TGEP::Shader::Create(vertexSrc, fragmentSrc));


        std::string squareVertexSrc = R"(
        #version 460 core

        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec4 aCol;
        uniform mat4 u_ViewProjection;

        out vec4 vCol;

        void main() 
        {

            vCol = aCol;
            gl_Position = u_ViewProjection * vec4(aPos, 1.0);
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
        
        TGEP::BufferLayout squareLayout = {
            { TGEP::ShaderDataType::Float3 },
            { TGEP::ShaderDataType::Float4 }
        };


        m_SquareVertexArray.reset(TGEP::VertexArray::Create());

        std::shared_ptr<TGEP::VertexBuffer> SVB;
        SVB.reset(TGEP::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        SVB->SetLayout(squareLayout);
        m_SquareVertexArray->AddVertexBuffer(SVB);

        std::shared_ptr<TGEP::IndexBuffer> SIB;
        SIB.reset(TGEP::IndexBuffer::Create(squareIndices, (sizeof(squareIndices) / sizeof(uint32_t))));
        m_SquareVertexArray->SetIndexBuffer (SIB);

        m_SquareShader.reset(TGEP::Shader::Create(squareVertexSrc, squareFragmentSrc));
    }

    void OnUpdate() override
    {
        if(TGEP::Input::IsKeyPressed(TGEP::Key::W))
        {
            m_Position.y += 0.01f;
        }
        if(TGEP::Input::IsKeyPressed(TGEP::Key::S))
        {
            m_Position.y -= 0.01f;
        }
        if(TGEP::Input::IsKeyPressed(TGEP::Key::A))
        {
            m_Position.x -= 0.01f;
        }
        if(TGEP::Input::IsKeyPressed(TGEP::Key::D))
        {
            m_Position.x += 0.01f;
        }
        if(TGEP::Input::IsKeyPressed(TGEP::Key::Q))
        {
            m_Rotation += 0.01f;
        }
        if(TGEP::Input::IsKeyPressed(TGEP::Key::E))
        {
            m_Rotation -= 0.01f;
        }

        TGEP::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        TGEP::RenderCommand::Clear();

        
        /****Render Code****/
        TGEP::Renderer::BeginScene(m_Camera);

        m_Camera.SetPosition(m_Position);
        m_Camera.SetRotation(m_Rotation);

        TGEP::Renderer::Push(m_SquareVertexArray, m_SquareShader);

        TGEP::Renderer::Push(m_VertexArray, m_Shader);

        TGEP::Renderer::EndScene();
        /****Render Code****/
    }

private:
    std::shared_ptr<TGEP::Shader> m_Shader;
    std::shared_ptr<TGEP::VertexArray> m_VertexArray;

    std::shared_ptr<TGEP::Shader> m_SquareShader;
    std::shared_ptr<TGEP::VertexArray> m_SquareVertexArray;

    TGEP::OrthoCamera m_Camera;

    glm::vec3 m_Position = glm::vec3(0.0f);
    float m_Rotation = 0.0f;
};

class Sandbox : public TGEP::Application
{
public:

    Sandbox()
    {
        TestLayer* testLayer = new TestLayer();
        PushLayer(testLayer);
    }

    ~Sandbox()
    {

    }
    

};

TGEP::Application* TGEP::CreateApplication()
{
    return new Sandbox();
}