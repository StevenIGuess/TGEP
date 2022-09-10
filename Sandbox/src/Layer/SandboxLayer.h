#pragma once
#include <TGEP.h>
#include <Profiling.h>

class SandboxLayer : public TGEP::Layer
{
public:
    SandboxLayer();

    void OnUpdate(TGEP::DeltaTime deltaTime) override;


    virtual void OnEvent(TGEP::Event& e);

    
    virtual void OnImGuiRender() override;


private:

    //Helper functions 
    void InitVA();
    void DrawBoard(TGEP::Ref<TGEP::Shader> shader);
    void UpdatePlayers(TGEP::Ref<TGEP::Shader> shader);


    //Event functions
    bool OnKeyPressed(TGEP::KeyPressedEvent& e);

    //Profiling
    TGEP::Ref<TGEP::Profiling> m_Profiler = std::make_shared<TGEP::Profiling>();
    uint64_t t0 = 0;
    uint64_t dt = 0;
    int m_NumCpus = m_Profiler->get_num_processors();
    bool advancedProfiling = false;
    float m_DeltaTime = 0.0f;

    //Shader and VA
    TGEP::ShaderLibary m_ShaderLibary;
    TGEP::Ref<TGEP::VertexArray> m_SquareVertexArray;

    //Camera controller
    TGEP::OrthoCamera m_Camera;

    //Player pos
    glm::ivec2 m_QueenPosition = glm::ivec2(0);
    glm::ivec2 m_EnemyQueenPosition = glm::ivec2(5);

    //Cam pos
    glm::vec3 m_Position = glm::vec3(0.0f);
    
    //ImGui Windows
    bool m_Settings = false;

    //Data for drawing the board
    glm::vec3 m_SquarePosition = glm::vec3(0.0f);
    glm::vec3 m_SquareScale = glm::vec3(0.1f);
    glm::vec4 m_FirstColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 m_SecondColor = glm::vec4(1.0f);
    float OffsetMulitplier = 1.0f;
    int num_squares_x = 10;
    int num_squares_y = 10;

    //Textures
    TGEP::Ref<TGEP::Texture2D> m_QueenTexture, m_EnemyQueenTexture;

    //Data for the VA
    float m_SquareVertices[4 * 5] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    uint32_t m_SquareIndices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    TGEP::BufferLayout m_SquareLayout = {
        { TGEP::ShaderDataType::Float3 },
        { TGEP::ShaderDataType::Float2 }
    };


    /// <Networking>
    /// Not implemented yet.
    /// char m_ServerAddress[17] = "127.0.0.1";
    ///int m_ServerPort = 2556;
    ///bool m_IsConnected = false;
    /// </Networking>  
};