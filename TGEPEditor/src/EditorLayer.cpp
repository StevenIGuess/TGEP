#include "EditorLayer.h"
#include "imgui/imgui.h"
#include <TGEP.h>


namespace TGEP
{

    static const char* s_MapTiles =
        "00045555555555555555555555555600"
        "00045555555555555555555555555600"
        "00045555555555555555555555555600"
        "00045555555555555555555555555600"
        "00045555555555555555555555555600"
        "00012222222222222222222222222300"
        "00000000000000000000000000000000"
        "00000000000000000000000000000000"
        "00000000000000000000000000000000"
        "00000000000000000000000000000000"
        "00078888C888888888888888L8888900"
        "00045555555555555555555555555600"
        "00045555555555555555555555555600"
        "00045555555555555555555555555600"
        "00045555555555555555555555555600"
        "00045555555555555555555555555600"
        "00045555555555555555555555555600"
        "00012222222222222222222222222300"
        ;


    EditorLayer::EditorLayer()
        : Layer("Sanbox2D"), m_CameraController(1280.0f / 720.0f)
    {
    }

    void EditorLayer::OnAttach()
    {
        PROFILE_FUNCTION();

        m_MapWidth = 32;
        m_MapHeight = 17;

        m_SpriteSheet = Texture2D::Create("assets/textures/tilemap_packed_default.png");
        m_PlayerSpriteSheet = Texture2D::Create("assets/textures/loose sprites.png");
        s_TextureMap['0'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 0,7 }, { 16,16 });
        s_TextureMap['1'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1,7 }, { 16,16 });
        s_TextureMap['2'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2,7 }, { 16,16 });
        s_TextureMap['3'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3,7 }, { 16,16 });
        s_TextureMap['4'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1,6 }, { 16,16 });
        s_TextureMap['5'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2,6 }, { 16,16 });
        s_TextureMap['6'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3,6 }, { 16,16 });
        s_TextureMap['7'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1,5 }, { 16,16 });
        s_TextureMap['8'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2,5 }, { 16,16 });
        s_TextureMap['9'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3,5 }, { 16,16 });
        s_TextureMap['C'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1,4 }, { 16,16 });
        s_TextureMap['L'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3,4 }, { 16,16 });
        s_TextureMap['A'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 8,6 }, { 16,16 });

        s_PlayerSprites['D'][0] = SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 0,7 }, { 16,16 });
        s_PlayerSprites['D'][1] = SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 1,7 }, { 16,16 });
        s_PlayerSprites['D'][2] = SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 2,7 }, { 16,16 });
        s_PlayerSprites['D'][3] = SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 3,7 }, { 16,16 });
        s_PlayerSprites['U'][0] = SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 0,3 }, { 16,16 });
        s_PlayerSprites['U'][1] = SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 1,3 }, { 16,16 });
        s_PlayerSprites['U'][2] = SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 2,3 }, { 16,16 });
        s_PlayerSprites['U'][3] = SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 3,3 }, { 16,16 });
        s_PlayerSprites['L'][0] = SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 0,5 }, { 16,16 });
        s_PlayerSprites['L'][1] = SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 1,5 }, { 16,16 });
        s_PlayerSprites['L'][2] = SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 2,5 }, { 16,16 });
        s_PlayerSprites['L'][3] = SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 3,5 }, { 16,16 });
        s_PlayerSprites['R'][0] = SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 0,1 }, { 16,16 });
        s_PlayerSprites['R'][1] = SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 1,1 }, { 16,16 });
        s_PlayerSprites['R'][2] = SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 2,1 }, { 16,16 });
        s_PlayerSprites['R'][3] = SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 3,1 }, { 16,16 });

        m_CameraController.SetZoom(10.0f);
        FramebufferSettings fbSettings;
        fbSettings.Width = 1280;
        fbSettings.Height = 720;
        m_Framebuffer = Framebuffer::Create(fbSettings);

        m_PlayerPos = { 0.0f, 0.0f };
        m_PlayerDirection = 'U';
        m_PlayerIsMoving = false;
        m_PlayerMoveSpeed = 10.0f;
        m_CurrentPlayerSprite = 0;
        m_CurrentFrame = 0;

    }

    void EditorLayer::OnDetach()
    {
        PROFILE_FUNCTION();
    }

    void EditorLayer::OnUpdate(DeltaTime deltaTime)
    {
        //Update & Profileing
        PROFILE_FUNCTION();
        m_Framebuffer->Bind();
        t0 = m_Profiler->get_cpu_cycles();
        m_DeltaTime = deltaTime;
        m_CameraController.OnUpdate(deltaTime);


        //PreRender
        Renderer2D::ResetStats();
        RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        RenderCommand::Clear();

        m_PlayerTilePos = { (int)m_PlayerPos.x, (int)m_PlayerPos.y };
        if (m_PlayerTilePos.x > m_MapWidth)
            m_PlayerTilePos.x = m_MapWidth;
        if (m_PlayerTilePos.y > m_MapHeight)
            m_PlayerTilePos.y = m_MapHeight;

        if (m_PlayerTilePos.x < 0)
            m_PlayerTilePos.x = 0;
        if (m_PlayerTilePos.y < 0)
            m_PlayerTilePos.y = 0;



        if (Input::IsKeyPressed(TGEP_KEY_A))
        {

            m_PlayerDirection = 'L';
            m_PlayerIsMoving = true;
            m_PlayerPos.x -= m_PlayerMoveSpeed * deltaTime;

        }
        else if (Input::IsKeyPressed(TGEP_KEY_D))
        {

            m_PlayerDirection = 'R';
            m_PlayerIsMoving = true;
            m_PlayerPos.x += m_PlayerMoveSpeed * deltaTime;

        }


        if (Input::IsKeyPressed(TGEP_KEY_W))
        {
            m_PlayerDirection = 'U';
            m_PlayerIsMoving = true;
            m_PlayerPos.y += m_PlayerMoveSpeed * deltaTime;

        }
        else if (Input::IsKeyPressed(TGEP_KEY_S))
        {
            m_PlayerDirection = 'D';
            m_PlayerIsMoving = true;
            m_PlayerPos.y -= m_PlayerMoveSpeed * deltaTime;
        }

        if (!(Input::IsKeyPressed(TGEP_KEY_W)) && !(Input::IsKeyPressed(TGEP_KEY_A)) && !(Input::IsKeyPressed(TGEP_KEY_S)) && !(Input::IsKeyPressed(TGEP_KEY_D)))
        {
            m_PlayerIsMoving = false;
        }


        //Begin Scene
        Renderer2D::BeginScene(m_CameraController.GetCamera());

        //Render
        for (uint32_t y = 0; y < m_MapHeight; y++)
        {
            for (uint32_t x = 0; x < m_MapWidth; x++)
            {
                char tile = s_MapTiles[x + y * m_MapWidth];
                if (s_TextureMap.find(tile) != s_TextureMap.end())
                {
                    Renderer2D::DrawQuad({ x, y, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, s_TextureMap[tile]);
                }
            }
        }


        if (m_PlayerIsMoving)
        {
            if (m_CurrentFrame % 4 == 0)
            {
                if (m_CurrentPlayerSprite != 3)
                {
                    m_CurrentPlayerSprite++;
                }
                else
                {
                    m_CurrentPlayerSprite = 0;
                }
            }
            Renderer2D::DrawQuad({ m_PlayerPos.x, m_PlayerPos.y, 0.5f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, s_PlayerSprites[m_PlayerDirection][m_CurrentPlayerSprite]);
        }
        else
        {
            Renderer2D::DrawQuad({ m_PlayerPos.x, m_PlayerPos.y, 0.5f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, s_PlayerSprites[m_PlayerDirection][0]);
        }

        m_CameraController.SetPosition({ m_PlayerPos.x, m_PlayerPos.y, 0.0f });

        //End Scene
        Renderer2D::EndScene();
        m_Framebuffer->UnBind();
        m_CurrentFrame++;
    }

    void EditorLayer::OnImGuiRender()
    {

        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static bool imGuiDockSpace = true;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->GetWorkPos());
            ImGui::SetNextWindowSize(viewport->GetWorkSize());
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &imGuiDockSpace, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit")) Application::Get().Close();
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        bool showViewport = true;


        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Viewport", &showViewport);

        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        if (m_ViewportSize != *((glm::vec2*)&viewportSize))
        {
            m_Framebuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
            m_ViewportSize = { viewportSize.x, viewportSize.y };

            m_CameraController.ResizeBounds(viewportSize.x, viewportSize.y);
        }
        uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
        ImGui::Image((void*)textureID, viewportSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::Begin("Settings", &m_Settings);
        std::stringstream DT;
        DT << "Delta Time(ms): " << m_DeltaTime << "\n";
        std::stringstream FPS;
        FPS << "FPS: " << 1 / m_DeltaTime << "\n";
        ImGui::TextColored(ImVec4(0, 1, 1, 1), "Performance");
        ImGui::Text(DT.str().c_str());
        ImGui::Text(FPS.str().c_str());

        ImGui::Separator();
        ImGui::Text("Rederer2D Stats");

        auto stats = Renderer2D::GetStats();
        ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        ImGui::Text("Quads: %d", stats.QuadCount);
        ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
        ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

        ImGui::Separator();
        ImGui::TextColored(ImVec4(0, 1, 1, 1), "Game Data");

        ImGui::DragFloat("Player movement speed", &m_PlayerMoveSpeed);

        if (m_PlayerIsMoving)
        {
            ImGui::Text("PlayerIsMoving: true");
        }
        else
        {
            ImGui::Text("PlayerIsMoving: false");
        }

        ImGui::Separator();
        ImGui::TextColored(ImVec4(0, 1, 1, 1), "Advanced Settings");

        if (ImGui::TreeNode("Advanced performance info"))
        {
            ImGui::Separator();

            if (advancedProfiling)
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
            }
            else
            {
                if (ImGui::Button("Turn on advanced performance info"))
                {
                    advancedProfiling = true;
                }
                ImGui::TextColored(ImVec4(1, 0, 0, 1), "WARNING: This might impact performance");
            }
            ImGui::TreePop();
        }

        ImGui::End();

        ImGui::End();
    }

    void EditorLayer::OnEvent(Event& e)
    {
        m_CameraController.OnEvent(e);
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(EditorLayer::OnKeyPressed));
    }

    bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
    {
        if (e.GetKeyCode() == Key::Escape)
        {
            if (m_Settings)
            {
                m_Settings = false;
                return true;
            }
            else
            {
                m_Settings = true;
                return true;
            }
        }

    }

}


