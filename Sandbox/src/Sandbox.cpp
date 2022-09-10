#include <TGEP.h>
#include <TGEPNetworking.h>
#include <Profiling.h>
#include "imgui/imgui.h"

enum class MessageTypes : uint32_t
{
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage,
    StringMessage
};


//do networking here
class TGEPClient : public TGEP::net::client_interface<MessageTypes>
{
public:
    void PingServer()
    {
        TGEP::net::message<MessageTypes> msg;
        msg.header.id = MessageTypes::ServerPing;

        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

        msg << timeNow;

        LOG("Pinging Server...\n");
        Send(msg);
    }

    void SendTest(int message)
    {
        TGEP::net::message<MessageTypes> msg;
        msg.header.id = MessageTypes::StringMessage;

        msg << message;

        LOG("%s%X%s", "Sending message [", message, "] to Server...\n");
        Send(msg);
    }

};


class TestLayer : public TGEP::Layer
{
public:
    TestLayer() : TGEP::Layer("TestLayer"), m_Camera(-1.6, 1.6f, -0.9f, 0.9f, -1.0f, 1.0f) 
    {
        //setup networking
        c.reset(new TGEPClient);

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
        TGEPGLSCast(TextureShader)->Bind();
        TGEPGLSCast(TextureShader)->UploadUniform("u_Texture", 0);
    }

    void OnUpdate(TGEP::DeltaTime deltaTime) override
    {
        m_IsConnected = c->IsConnected();
        t0 = m_Profiler->get_cpu_cycles();
        m_DeltaTime = deltaTime;
        TGEP::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        TGEP::RenderCommand::Clear();

        if (!m_IsConnected) { return; }

        if (!(c->Incoming().empty()))
        {
            auto msg = c->Incoming().pop_front().msg;

            //handle headers
            switch (msg.header.id)
            {
            case MessageTypes::ServerPing:
            {
                std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
                std::chrono::system_clock::time_point timeThen;
                msg >> timeThen;

                double ping = std::chrono::duration<double>(timeNow - timeThen).count();

                LOG("%s%lfs\n", "Reply from server: time:", ping);
            }
            case MessageTypes::ServerMessage:
            {
                int message;
                msg >> message;

                LOG("%s%X\n", "Reply from server: ", message);
            }
            }
        }


        TGEP::Renderer::BeginScene(m_Camera);

        m_Camera.SetPosition(m_Position);

        auto SquareShader = m_ShaderLibary.Get("Square");
        auto TextureShader = m_ShaderLibary.Get("Texture");

        TGEPGLSCast(SquareShader)->Bind();
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
                    TGEPGLSCast(SquareShader)->UploadUniform("u_Color", m_FirstColor);
                }else
                {
                    TGEPGLSCast(SquareShader)->UploadUniform("u_Color", m_SecondColor);
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

        dt = m_Profiler->get_cpu_cycles() - t0;
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
            case TGEP::Key::Escape :
            {
                if(m_Settings)
                {
                    m_Settings = false;
                    return true;
                } else 
                {
                    m_Settings = true;
                    return true;
                }
            }
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
        if(!m_IsConnected)
        {
            ImGui::Begin("Not connected to server!");
            ImGui::Text("Go to Settings(esc) and connect to a server!");
            ImGui::End();
        }

        if(m_Settings)
        {
            ImGui::Begin("Settings", &m_Settings);
            std::stringstream DT;
            DT << "Delta Time(ms): " << m_DeltaTime << "\n"; 
            std::stringstream FPS;
            FPS << "FPS: " << 1 / m_DeltaTime << "\n";
            ImGui::TextColored(ImVec4(0,1,1,1), "Performance");
            ImGui::Text(DT.str().c_str());
            ImGui::Text(FPS.str().c_str());

            ImGui::Separator();

            ImGui::TextColored(ImVec4(0,1,1,1), "Network Settings");

            if(m_IsConnected) 
            {
                ImGui::Text("Server status: Connected!");
            }
            if(!m_IsConnected) 
            {
                ImGui::Text("Server status: Disconnected!");
            }

            ImGui::InputText("Server Ip", m_ServerAddress, 17);
            ImGui::InputInt("Server port", &m_ServerPort);

            if(ImGui::Button("Connect to server"))
            {
                if(m_IsConnected) 
                {
                    ImGui::End();
                    return;
                }
                ConnectToServer();
                ImGui::End();
                return;
            }

            if (m_IsConnected)
            {
                if (ImGui::Button("Send Message"))
                {
                    c->SendTest(0x0001);
                    ImGui::End();
                    return;
                }
                if (ImGui::Button("Ping server"))
                {
                    c->PingServer();
                    ImGui::End();
                    return;
                }
            }

            ImGui::Separator();
            ImGui::TextColored(ImVec4(0,1,1,1), "General Settings");

            ImGui::ColorEdit4("FirstColor", (float*)&m_FirstColor);
            ImGui::ColorEdit4("SecondColor", (float*)&m_SecondColor);

            ImGui::Separator();
            ImGui::TextColored(ImVec4(0,1,1,1), "Advanced Settings");

            if (ImGui::TreeNode("Advanced performance info"))
            {
                if(advancedProfiling)
                {
                    std::stringstream totalVmem;
                    totalVmem << "Total available Vmemory: " << m_Profiler->get_total_vmem() / 1000000 << "Mb\n";

                    std::stringstream usedVmem;
                    usedVmem << "Used Vmemory: " << m_Profiler->get_used_vmem() / 1000000 << "Mb\n";

                    std::stringstream totalRam;
                    totalRam << "Total available RAM: " << m_Profiler->get_total_ram() / 1000000 << "Mb\n";

                    std::stringstream usedRam;
                    usedRam << "Used RAM: " << m_Profiler->get_used_ram() / 1000000 << "Mb\n";

                    std::stringstream updateCycles;
                    updateCycles << "Update CPU Cycles: " << dt / 1000 << "k\n";

                    std::stringstream numCpu;
                    numCpu << "CPU cores: " << m_NumCpus << "\n";

                    
                    ImGui::Text(totalVmem.str().c_str());
                    ImGui::Text(usedVmem.str().c_str());
                    ImGui::Text(totalRam.str().c_str());
                    ImGui::Text(usedRam.str().c_str());
                    ImGui::Text(updateCycles.str().c_str());
                    ImGui::Text(numCpu.str().c_str());
                } else
                {
                    if(ImGui::Button("Turn on advanced performance info"))
                    {
                        advancedProfiling = true;
                    }
                    ImGui::TextColored(ImVec4(1,0,0,1), "WARNING: This might impact performance");
                }
                ImGui::TreePop();
            }

            ImGui::End();
        }
    }

    void ConnectToServer()
    {
        c->Connect(m_ServerAddress, m_ServerPort);
    }

private:

    TGEP::Ref<TGEPClient> c;

    TGEP::Ref<TGEP::Profiling> m_Profiler = std::make_shared<TGEP::Profiling>();
    uint64_t t0 = 0;
    uint64_t dt = 0;
    int m_NumCpus = m_Profiler->get_num_processors();
    bool advancedProfiling = false;

    char m_ServerAddress[17] = "127.0.0.1";
    int m_ServerPort = 2556;

    bool m_IsConnected = false;

    TGEP::ShaderLibary m_ShaderLibary;
    TGEP::Ref<TGEP::VertexArray> m_SquareVertexArray;

    TGEP::OrthoCamera m_Camera;

    glm::vec3 m_Position = glm::vec3(0.0f);
    float m_DeltaTime = 0.0f;

    bool m_Settings = false;

    glm::vec3 m_SquarePosition = glm::vec3(0.0f);
    glm::vec3 m_SquareScale = glm::vec3(0.1f);

    glm::vec4 m_FirstColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 m_SecondColor = glm::vec4(1.0f);

    glm::ivec2 m_QueenPosition = glm::ivec2(0);
    glm::ivec2 m_EnemyQueenPosition = glm::ivec2(5);

    float OffsetMulitplier = 1.0f;

    int num_squares_x = 100;
    int num_squares_y = 10;

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
    TGEP::Application* sandbox = new Sandbox();
    return sandbox;
}
