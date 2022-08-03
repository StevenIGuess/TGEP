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
        uniform mat4 u_Transform;

        out vec3 vColor;

        void main() 
        {

            vColor = aPos;
            gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0);
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

        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;


        void main() 
        {
            gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0);
        }   
        )";

        std::string squareFragmentSrc = R"(
        #version 460 core

        out vec4 FragColor;
        uniform vec4 u_Color;

        void main()
        {
            FragColor = u_Color;
        }

        )";

        float squareVertices[4 * 7] = {
            -0.5f, -0.5f, 0.0f, 
             0.5f, -0.5f, 0.0f, 
             0.5f,  0.5f, 0.0f, 
            -0.5f,  0.5f, 0.0f
        };


        uint32_t squareIndices[6] = {
            0, 1, 2,
            2, 3, 0
        };
        
        TGEP::BufferLayout squareLayout = {
            { TGEP::ShaderDataType::Float3 }
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

    void OnUpdate(TGEP::DeltaTime deltaTime) override
    {
        m_DeltaTime = deltaTime;

        if(TGEP::Input::IsKeyPressed(TGEP::Key::W))
        {
            m_Position.y += CameraMoveSpeed * m_DeltaTime;
        }
        if(TGEP::Input::IsKeyPressed(TGEP::Key::S))
        {
            m_Position.y -= CameraMoveSpeed * m_DeltaTime;
        }
        if(TGEP::Input::IsKeyPressed(TGEP::Key::A))
        {
            m_Position.x -= CameraMoveSpeed * m_DeltaTime;
        }
        if(TGEP::Input::IsKeyPressed(TGEP::Key::D))
        {
            m_Position.x += CameraMoveSpeed * m_DeltaTime;
        }
        if(TGEP::Input::IsKeyPressed(TGEP::Key::Q))
        {
            m_Rotation += CameraRotSpeed * m_DeltaTime;
        }
        if(TGEP::Input::IsKeyPressed(TGEP::Key::E))
        {
            m_Rotation -= CameraRotSpeed * m_DeltaTime;
        }

        TGEP::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        TGEP::RenderCommand::Clear();

        
        /****Render Code****/
        TGEP::Renderer::BeginScene(m_Camera);

        

        m_Camera.SetPosition(m_Position);
        m_Camera.SetRotation(m_Rotation);

        
        for(int j = 0; j < 8; j++)
        {
            for(int i = 0; i < 8; i++)
            {
                glm::vec3 calculatedScale = glm::vec3((m_SquareScale.x * 9) / 10, (m_SquareScale.y * 16) / 10, 0.0f);
                float squareOffsetX = OffsetMulitplier * calculatedScale.x;
                float squareOffsetY = OffsetMulitplier * calculatedScale.y;
                glm::vec3 pos(i * squareOffsetX  + m_SquarePosition.x, j * squareOffsetY + m_SquarePosition.y, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), calculatedScale);
                if((i+j) % 2 == 0)
                {
                    m_SquareShader->UploadUniform("u_Color", m_FirstColor);
                }else
                {
                    m_SquareShader->UploadUniform("u_Color", m_SecondColor);
                }
                TGEP::Renderer::Push(m_SquareVertexArray, m_SquareShader, transform);
            }
        }

        //TGEP::Renderer::Push(m_VertexArray, m_Shader);

        TGEP::Renderer::EndScene();
        /****Render Code****/
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
            ImGui::SliderFloat("CameraMoveSpeed", &CameraMoveSpeed, 0.0f, 5.0f);
            ImGui::SliderFloat("CameraRotSpeed", &CameraRotSpeed, 0.0f, 5.0f);

            ImGui::TextColored(ImVec4(1,1,0,1), "Game Data");
            ImGui::BeginChild("Scrolling");

            ImGui::SliderFloat3("Camera position", (float*)&m_Position, -10.0f, 10.0f);
            ImGui::SliderFloat("Camera roation", &m_Rotation, -1000.0f, 1000.0f);

            ImGui::SliderFloat3("Square position", (float*)&m_SquarePosition, -10.0f, 10.0f);
            ImGui::SliderFloat3("Square scale", (float*)&m_SquareScale, 0.1f, 1.0f);
            ImGui::SliderFloat("Offset", &OffsetMulitplier, 1.0f, 2.0f);

            ImGui::ColorEdit4("FirstColor", (float*)&m_FirstColor);
            ImGui::ColorEdit4("SecondColor", (float*)&m_SecondColor);

            ImGui::EndChild();
            ImGui::End();
        }
    }

private:
    std::shared_ptr<TGEP::Shader> m_Shader;
    std::shared_ptr<TGEP::VertexArray> m_VertexArray;

    std::shared_ptr<TGEP::Shader> m_SquareShader;
    std::shared_ptr<TGEP::VertexArray> m_SquareVertexArray;

    TGEP::OrthoCamera m_Camera;

    glm::vec3 m_Position = glm::vec3(0.0f);
    float m_Rotation = 0.0f;
    float m_DeltaTime = 0.0f;

    float CameraRotSpeed = 2.0f;
    float CameraMoveSpeed = 2.0f;

    bool m_TGEP_info = true;

    glm::vec3 m_SquarePosition = glm::vec3(0.0f);
    glm::vec3 m_SquareScale = glm::vec3(0.1f);

    glm::vec4 m_FirstColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 m_SecondColor = glm::vec4(1.0f);

    float OffsetMulitplier = 1.0f;

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