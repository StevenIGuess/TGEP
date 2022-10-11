#pragma once 
#include <TGEP.h>
#include <Profiling.h>
#include <chrono>

namespace TGEP
{

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

    class EditorLayer : public Layer
    {
    public:
        EditorLayer();
        ~EditorLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate(DeltaTime deltaTime) override;
        virtual void OnImGuiRender() override;
        virtual void OnEvent(Event& e) override;

    private:

        bool OnKeyPressed(KeyPressedEvent& e);

        //profiling and deltatime
        Ref<Profiling> m_Profiler = std::make_shared<Profiling>();
        uint64_t t0 = 0;
        uint64_t dt = 0;
        int m_NumCpus = m_Profiler->get_num_processors();
        bool advancedProfiling = false;
        float m_DeltaTime = 0.0f;

        //Shader
        ShaderLibary m_ShaderLibary;

        //VA
        Ref<VertexArray> m_SquareVertexArray;

        //Camera
        OrthoCameraController m_CameraController;

        //Framebuffer
        Ref<Framebuffer> m_Framebuffer;

        //ImGUI Settings tab
        bool m_Settings = false;

        //ImGUI viewport
        glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

        //Gamedata
        uint32_t m_MapHeight, m_MapWidth;
        Ref<Texture2D> m_SpriteSheet;
        Ref<Texture2D> m_PlayerSpriteSheet;
        std::unordered_map<char, Ref<SubTexture2D>> s_TextureMap;
        std::unordered_map<char, Ref<SubTexture2D>[4]> s_PlayerSprites;
        char m_PlayerDirection;
        bool m_PlayerIsMoving;
        uint32_t m_CurrentPlayerSprite;
        long long m_CurrentFrame;
        glm::vec2 m_PlayerPos;
        glm::ivec2 m_PlayerTilePos;
        float m_PlayerMoveSpeed;
    };
}