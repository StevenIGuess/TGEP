#include <TGEP.h>
#include <winsock2.h>

class TestLayer : public TGEP::Layer
{
public:
    TestLayer() : TGEP::Layer("TestLayer"), m_Camera(-1.6, 1.6f, -0.9f, 0.9f, -1.0f, 1.0f) 
    {

        WSADATA wsa;

        SOCKET s;
	
        printf("\n%s\n", "Initialising Winsock...");
        if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
        {
            printf("%s%d\n", "Failed. Winsock Error Code : ",WSAGetLastError());
        }
        
        printf("%s\n", "Initialised Winsock.");

        if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
        {
            printf("%s%d\n", "Could not create socket : " , WSAGetLastError());
        }

        printf("%s\n", "Created Socket.");

        #pragma region VA data
        float squareVertices[4 * 5] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        uint32_t squareIndices[6] = {
            0, 1, 2,
            2, 3, 0
        };
        
        TGEP::BufferLayout squareLayout = {
            { TGEP::ShaderDataType::Float3 },
            { TGEP::ShaderDataType::Float2 }
        };
        
        #pragma endregion

        m_SquareVertexArray.reset(TGEP::VertexArray::Create());

        TGEP::Ref<TGEP::VertexBuffer> SVB;
        SVB.reset(TGEP::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        SVB->SetLayout(squareLayout);
        m_SquareVertexArray->AddVertexBuffer(SVB);

        TGEP::Ref<TGEP::IndexBuffer> SIB;
        SIB.reset(TGEP::IndexBuffer::Create(squareIndices, (sizeof(squareIndices) / sizeof(uint32_t))));
        m_SquareVertexArray->SetIndexBuffer (SIB);

        auto SquareShader = m_ShaderLibary.Load("assets/Shader/Square.glsl");
        auto TextureShader = m_ShaderLibary.Load("assets/Shader/Texture.glsl");

        m_EnemyQueenTexture = TGEP::Texture2D::Create("assets/textures/queen.png");
        m_QueenTexture = TGEP::Texture2D::Create("assets/textures/queen.png");
        GLShaderCast(TextureShader)->Bind();
        GLShaderCast(TextureShader)->UploadUniform("u_Texture", 0);
    }

    void OnUpdate(TGEP::DeltaTime deltaTime) override
    {
        m_DeltaTime = deltaTime;
        TGEP::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        TGEP::RenderCommand::Clear();


        /****Render Code****/
        TGEP::Renderer::BeginScene(m_Camera);

        m_Camera.SetPosition(m_Position);

        auto SquareShader = m_ShaderLibary.Get("Square");
        auto TextureShader = m_ShaderLibary.Get("Texture");

        GLShaderCast(SquareShader)->Bind();
        for(int j = 0; j < num_squares_y; j++)
        {
            for(int i = 0; i < num_squares_x; i++)
            {

                float squareOffsetX = OffsetMulitplier * m_SquareScale.x;
                float squareOffsetY = OffsetMulitplier * m_SquareScale.y;
                glm::vec3 pos(i * squareOffsetX  + m_SquarePosition.x, j * squareOffsetY + m_SquarePosition.y, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), m_SquareScale);
                if((i+j) % 2 == 0)
                {
                    GLShaderCast(SquareShader)->UploadUniform("u_Color", m_FirstColor);
                }else
                {
                    GLShaderCast(SquareShader)->UploadUniform("u_Color", m_SecondColor);
                }

                TGEP::Renderer::Push(m_SquareVertexArray, SquareShader, transform);
            }
        }

        glm::mat4 transformQueen = glm::translate(glm::mat4(1.0f),
                                   glm::vec3(m_SquarePosition.x + (m_SquareScale.x * m_QueenPosition.x),
                                             m_SquarePosition.y + (m_SquareScale.y  * m_QueenPosition.y),
                                             0.0f)) *
                                   glm::scale(glm::mat4(1.0f), m_SquareScale);
        glm::mat4 transformEnemyQueen = glm::translate(glm::mat4(1.0f),
                                   glm::vec3(m_SquarePosition.x + (m_SquareScale.x * m_EnemyQueenPosition.x),
                                             m_SquarePosition.y + (m_SquareScale.y  * m_EnemyQueenPosition.y),
                                             0.0f)) *
                                   glm::scale(glm::mat4(1.0f), m_SquareScale);

        m_QueenTexture->Bind();
        TGEP::Renderer::Push(m_SquareVertexArray, TextureShader, transformQueen);
        m_EnemyQueenTexture->Bind();
        TGEP::Renderer::Push(m_SquareVertexArray, TextureShader, transformEnemyQueen);

        TGEP::Renderer::EndScene();
        /****Render Code****/
    }
    
    virtual void OnEvent(TGEP::Event &e)
    {
        TGEP::EventDispatcher dispatcher(e);

        dispatcher.Dispatch<TGEP::KeyPressedEvent>(BIND_EVENT_FUNC(TestLayer::OnKeyPressed));
    }

    bool OnKeyPressed(TGEP::KeyPressedEvent &e)
    {
        switch (e.GetKeyCode())
        {
            case TGEP::Key::W : 
            {
                if(m_QueenPosition.y == m_EnemyQueenPosition.y - 1 && m_QueenPosition.x == m_EnemyQueenPosition.x) { return true; }
                if(m_QueenPosition.y < num_squares_y - 1)
                {
                    m_QueenPosition.y += 1;
                }
                return true;
            }
            case TGEP::Key::A :
            {
                if(m_QueenPosition.x == m_EnemyQueenPosition.x + 1 && m_QueenPosition.y == m_EnemyQueenPosition.y) { return true; }
                if(m_QueenPosition.x > 0)
                {
                    m_QueenPosition.x -= 1;
                }
                return true;
            }
            case TGEP::Key::S :
            {
                if(m_QueenPosition.y == m_EnemyQueenPosition.y + 1 && m_QueenPosition.x == m_EnemyQueenPosition.x) { return true; }
                if(m_QueenPosition.y > 0)
                {
                    m_QueenPosition.y -= 1;
                }
                return true;
            }
            case TGEP::Key::D :
            {
                if(m_QueenPosition.x == m_EnemyQueenPosition.x - 1 && m_QueenPosition.y == m_EnemyQueenPosition.y) { return true; }
                if(m_QueenPosition.x < num_squares_x - 1)
                {
                    m_QueenPosition.x += 1;
                }
                return true;
            }
        }
        return false;
    }

    virtual void OnImGuiRender() override
    {
        if(m_TGEP_info)
        {
            ImGui::Begin("Debug window", &m_TGEP_info);
            std::stringstream DT;
            DT << "Delta Time(ms): " << m_DeltaTime << "\n"; 
            std::stringstream FPS;
            FPS << "FPS: " << 1 / m_DeltaTime << "\n";
            ImGui::Text(DT.str().c_str());
            ImGui::Text(FPS.str().c_str());

            ImGui::TextColored(ImVec4(1,1,0,1), "Game Data");
            ImGui::BeginChild("Scrolling");

            ImGui::ColorEdit4("FirstColor", (float*)&m_FirstColor);
            ImGui::ColorEdit4("SecondColor", (float*)&m_SecondColor);

            ImGui::EndChild();
            ImGui::End();
        }
    }

private:
    TGEP::ShaderLibary m_ShaderLibary;
    TGEP::Ref<TGEP::VertexArray> m_SquareVertexArray;

    TGEP::OrthoCamera m_Camera;

    glm::vec3 m_Position = glm::vec3(0.0f);
    float m_DeltaTime = 0.0f;

    bool m_TGEP_info = true;

    glm::vec3 m_SquarePosition = glm::vec3(0.0f);
    glm::vec3 m_SquareScale = glm::vec3(0.1f);

    glm::vec4 m_FirstColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 m_SecondColor = glm::vec4(1.0f);

    glm::ivec2 m_QueenPosition = glm::ivec2(0);
    glm::ivec2 m_EnemyQueenPosition = glm::ivec2(5);

    float OffsetMulitplier = 1.0f;

    int num_squares_x = 8;
    int num_squares_y = 8;

    TGEP::Ref<TGEP::Texture2D> m_QueenTexture, m_EnemyQueenTexture;

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