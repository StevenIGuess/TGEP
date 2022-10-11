#pragma once 
#include <TGEP.h>
#include <Profiling.h>
#include <chrono>

struct QuadData
{
    glm::vec3 Pos;
    glm::vec2 Scale;
    glm::vec4 Color;
    float TextureScale;
};

struct QuadDataR
{
    glm::vec3 Pos;
    glm::vec2 Scale;
    float Rot;
    glm::vec4 Color;
    float TextureScale;
};

class Sandbox2D : public TGEP::Layer
{
public:
    Sandbox2D();
    ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(TGEP::DeltaTime deltaTime) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(TGEP::Event& e) override;

private:

    bool OnKeyPressed(TGEP::KeyPressedEvent& e);

    //profiling and deltatime
    TGEP::Ref<TGEP::Profiling> m_Profiler = std::make_shared<TGEP::Profiling>();
    uint64_t t0 = 0;
    uint64_t dt = 0;
    int m_NumCpus = m_Profiler->get_num_processors();
    bool advancedProfiling = false;
    float m_DeltaTime = 0.0f;

    //Shader
    TGEP::ShaderLibary m_ShaderLibary;

    //VA
    TGEP::Ref<TGEP::VertexArray> m_SquareVertexArray;

    //Camera
    TGEP::OrthoCameraController m_CameraController;

    
    //ImGUI Settings tab
    bool m_Settings = false;

    //Gamedata
    uint32_t m_MapHeight, m_MapWidth;
    TGEP::Ref<TGEP::Texture2D> m_SpriteSheet;
    TGEP::Ref<TGEP::Texture2D> m_PlayerSpriteSheet;
    std::unordered_map<char, TGEP::Ref<TGEP::SubTexture2D>> s_TextureMap;
    std::unordered_map<char, TGEP::Ref<TGEP::SubTexture2D>[4]> s_PlayerSprites;
    char m_PlayerDirection;
    bool m_PlayerIsMoving;
    uint32_t m_CurrentPlayerSprite;
    long long m_CurrentFrame;
    glm::vec2 m_PlayerPos;
    glm::ivec2 m_PlayerTilePos;
    float m_PlayerMoveSpeed;
};