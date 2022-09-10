#include "SandboxLayer.h"
#include <TGEP.h>
#include "imgui/imgui.h"


SandboxLayer::SandboxLayer() : TGEP::Layer("TestLayer"), m_Camera(-1.6, 1.6f, -0.9f, 0.9f, -1.0f, 1.0f)
{
    //Create VA object
	m_SquareVertexArray.reset(TGEP::VertexArray::Create());

    //Init VA 
    InitVA();
    
}

//Called once per frame.
void SandboxLayer::OnUpdate(TGEP::DeltaTime deltaTime)
{
    //Update Deltatime and profiler
    t0 = m_Profiler->get_cpu_cycles();
    m_DeltaTime = deltaTime;

    //Clear Screen
    TGEP::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
    TGEP::RenderCommand::Clear();

    TGEP::Renderer::BeginScene(m_Camera);
    m_Camera.SetPosition(m_Position);

    //---Render code begin here---

    TGEP::Ref<TGEP::Shader> SquareShader = m_ShaderLibary.Get("Square");
    TGEP::Ref<TGEP::Shader> TextureShader = m_ShaderLibary.Get("Texture");

    DrawBoard(SquareShader);
    UpdatePlayers(TextureShader);

    //---Render code end here---

    TGEP::Renderer::EndScene();
    dt = m_Profiler->get_cpu_cycles() - t0;
}

//Event handeling
void SandboxLayer::OnEvent(TGEP::Event& e)
{
    TGEP::EventDispatcher dispatcher(e);
    dispatcher.Dispatch<TGEP::KeyPressedEvent>(BIND_EVENT_FUNC(SandboxLayer::OnKeyPressed));
}

//Used for drawing ImGui Windows
void SandboxLayer::OnImGuiRender()
{

}

//Handle Keypress
bool SandboxLayer::OnKeyPressed(TGEP::KeyPressedEvent& e)
{

}

//Updates Player Positions and Draws the Players
void SandboxLayer::UpdatePlayers(TGEP::Ref<TGEP::Shader> shader)
{
    glm::mat4 transformQueen = 
            glm::translate(glm::mat4(1.0f), glm::vec3(m_SquarePosition.x + (m_SquareScale.x * m_QueenPosition.x),
            m_SquarePosition.y + (m_SquareScale.y * m_QueenPosition.y), 0.0f)) *
            glm::scale(glm::mat4(1.0f), m_SquareScale);


    glm::mat4 transformEnemyQueen = 
            glm::translate(glm::mat4(1.0f), glm::vec3(m_SquarePosition.x + (m_SquareScale.x * m_EnemyQueenPosition.x),
            m_SquarePosition.y + (m_SquareScale.y * m_EnemyQueenPosition.y), 0.0f)) *
            glm::scale(glm::mat4(1.0f), m_SquareScale);

    m_QueenTexture->Bind();
    TGEP::Renderer::Push(m_SquareVertexArray, shader, transformQueen);
    m_EnemyQueenTexture->Bind();
    TGEP::Renderer::Push(m_SquareVertexArray, shader, transformEnemyQueen);
}

//Draws the board
void SandboxLayer::DrawBoard(TGEP::Ref<TGEP::Shader> shader)
{
    TGEPGLSCast(shader)->Bind();
    for (int j = 0; j < num_squares_y; j++)
    {
        for (int i = 0; i < num_squares_x; i++)
        {

            float squareOffsetX = OffsetMulitplier * m_SquareScale.x;
            float squareOffsetY = OffsetMulitplier * m_SquareScale.y;
            glm::vec3 pos(i * squareOffsetX + m_SquarePosition.x, j * squareOffsetY + m_SquarePosition.y, 0.0f);
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), m_SquareScale);
            if ((i + j) % 2 == 0)
            {
                TGEPGLSCast(shader)->UploadUniform("u_Color", m_FirstColor);
            }
            else
            {
                TGEPGLSCast(shader)->UploadUniform("u_Color", m_SecondColor);
            }

            TGEP::Renderer::Push(m_SquareVertexArray, shader, transform);
        }
    }
}

//Inits VA with data
void SandboxLayer::InitVA()
{
    TGEP::Ref<TGEP::VertexBuffer> SVB;
    SVB.reset(TGEP::VertexBuffer::Create(m_SquareVertices, sizeof(m_SquareVertices)));
    SVB->SetLayout(m_SquareLayout);
    m_SquareVertexArray->AddVertexBuffer(SVB);

    TGEP::Ref<TGEP::IndexBuffer> SIB;
    SIB.reset(TGEP::IndexBuffer::Create(m_SquareIndices, (sizeof(m_SquareIndices) / sizeof(uint32_t))));
    m_SquareVertexArray->SetIndexBuffer(SIB);

    auto SquareShader = m_ShaderLibary.Load("assets/Shader/Square.glsl");
    auto TextureShader = m_ShaderLibary.Load("assets/Shader/Texture.glsl");

    m_EnemyQueenTexture = TGEP::Texture2D::Create("assets/textures/queen.png");
    m_QueenTexture = TGEP::Texture2D::Create("assets/textures/queen.png");
    TGEPGLSCast(TextureShader)->Bind();
    TGEPGLSCast(TextureShader)->UploadUniform("u_Texture", 0);
}