#pragma once 
#include <TGEP.h>
#include <Profiling.h>

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
    glm::vec4 m_SquareColor = glm::vec4(0.8f, 0.4f, 0.2f, 1.0f);
    glm::vec4 m_Tint = glm::vec4(0.8f, 0.4f, 0.2f, 1.0f);
    TGEP::Ref<TGEP::Texture2D> m_Texture;
    
    QuadData m_QuadData[2];
    QuadDataR m_QuadDataR[2];
};