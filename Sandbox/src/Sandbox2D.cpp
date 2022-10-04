#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <TGEP.h>


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


Sandbox2D::Sandbox2D() 
	: TGEP::Layer("Sanbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
    PROFILE_FUNCTION();

    m_MapWidth = 32;
    m_MapHeight = 17;

    m_SpriteSheet = TGEP::Texture2D::Create("assets/textures/tilemap_packed_default.png");
    m_PlayerSpriteSheet = TGEP::Texture2D::Create("assets/textures/loose sprites.png");
    s_TextureMap['0'] = TGEP::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 0,7 }, { 16,16 });
    s_TextureMap['1'] = TGEP::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1,7 }, { 16,16 });
    s_TextureMap['2'] = TGEP::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2,7 }, { 16,16 });
    s_TextureMap['3'] = TGEP::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3,7 }, { 16,16 });
    s_TextureMap['4'] = TGEP::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1,6 }, { 16,16 });
    s_TextureMap['5'] = TGEP::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2,6 }, { 16,16 });
    s_TextureMap['6'] = TGEP::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3,6 }, { 16,16 });
    s_TextureMap['7'] = TGEP::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1,5 }, { 16,16 });
    s_TextureMap['8'] = TGEP::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2,5 }, { 16,16 });
    s_TextureMap['9'] = TGEP::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3,5 }, { 16,16 });
    s_TextureMap['C'] = TGEP::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1,4 }, { 16,16 });
    s_TextureMap['L'] = TGEP::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3,4 }, { 16,16 });
    s_TextureMap['A'] = TGEP::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 8,6 }, { 16,16 });

    s_PlayerSprites['D'][0] = TGEP::SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 0,7 }, { 16,16 });
    s_PlayerSprites['D'][1] = TGEP::SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 1,7 }, { 16,16 });
    s_PlayerSprites['D'][2] = TGEP::SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 2,7 }, { 16,16 });
    s_PlayerSprites['D'][3] = TGEP::SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 3,7 }, { 16,16 });
    s_PlayerSprites['U'][0] = TGEP::SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 0,3 }, { 16,16 });
    s_PlayerSprites['U'][1] = TGEP::SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 1,3 }, { 16,16 });
    s_PlayerSprites['U'][2] = TGEP::SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 2,3 }, { 16,16 });
    s_PlayerSprites['U'][3] = TGEP::SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 3,3 }, { 16,16 });
    s_PlayerSprites['L'][0] = TGEP::SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 0,5 }, { 16,16 });
    s_PlayerSprites['L'][1] = TGEP::SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 1,5 }, { 16,16 });
    s_PlayerSprites['L'][2] = TGEP::SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 2,5 }, { 16,16 });
    s_PlayerSprites['L'][3] = TGEP::SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 3,5 }, { 16,16 });
    s_PlayerSprites['R'][0] = TGEP::SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 0,1 }, { 16,16 });
    s_PlayerSprites['R'][1] = TGEP::SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 1,1 }, { 16,16 });
    s_PlayerSprites['R'][2] = TGEP::SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 2,1 }, { 16,16 });
    s_PlayerSprites['R'][3] = TGEP::SubTexture2D::CreateFromCoords(m_PlayerSpriteSheet, { 3,1 }, { 16,16 });

    m_CameraController.SetZoom(10.0f);
    m_PlayerPos = { 0.0f, 0.0f };
    m_PlayerDirection = 'U';
    m_PlayerIsMoving = false;
    m_PlayerMoveSpeed = 10.0f;
    m_CurrentPlayerSprite = 0;
    m_CurrentFrame = 0;
}

void Sandbox2D::OnDetach()
{
    PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(TGEP::DeltaTime deltaTime)
{
    //Update & Profileing
    PROFILE_FUNCTION()
        t0 = m_Profiler->get_cpu_cycles();
    m_DeltaTime = deltaTime;
    m_CameraController.OnUpdate(deltaTime);


    //PreRender
    TGEP::Renderer2D::ResetStats();
    TGEP::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
    TGEP::RenderCommand::Clear();

    m_PlayerTilePos = { (int)m_PlayerPos.x, (int)m_PlayerPos.y };
    if (m_PlayerTilePos.x > m_MapWidth)
        m_PlayerTilePos.x = m_MapWidth;
    if (m_PlayerTilePos.y > m_MapHeight)
        m_PlayerTilePos.y = m_MapHeight;

    if (m_PlayerTilePos.x < 0)
        m_PlayerTilePos.x = 0;
    if (m_PlayerTilePos.y < 0)
        m_PlayerTilePos.y = 0;



    if (TGEP::Input::IsKeyPressed(TGEP_KEY_A) && s_MapTiles[(m_PlayerTilePos.x - 1) + m_PlayerTilePos.y * m_MapWidth] == '0')
    {
        m_PlayerDirection = 'L';
        m_PlayerIsMoving = true;
        m_PlayerPos.x -= m_PlayerMoveSpeed * deltaTime;
    }
    else if (TGEP::Input::IsKeyPressed(TGEP_KEY_D) && s_MapTiles[(m_PlayerTilePos.x + 1)+ m_PlayerTilePos.y * m_MapWidth] == '0')
    {
        m_PlayerDirection = 'R';
        m_PlayerIsMoving = true;
        m_PlayerPos.x += m_PlayerMoveSpeed * deltaTime;
    }


    if (TGEP::Input::IsKeyPressed(TGEP_KEY_W) && s_MapTiles[m_PlayerTilePos.x + (m_PlayerTilePos.y + 1 ) * m_MapWidth] == '0')
    {
        m_PlayerDirection = 'U';
        m_PlayerIsMoving = true;
        m_PlayerPos.y += m_PlayerMoveSpeed * deltaTime;
    }
    else if (TGEP::Input::IsKeyPressed(TGEP_KEY_S) && s_MapTiles[m_PlayerTilePos.x + (m_PlayerTilePos.y - 1) * m_MapWidth] == '0')
    {
        m_PlayerDirection = 'D';
        m_PlayerIsMoving = true;
        m_PlayerPos.y -= m_PlayerMoveSpeed * deltaTime;
    }

    if (!(TGEP::Input::IsKeyPressed(TGEP_KEY_W)) && !(TGEP::Input::IsKeyPressed(TGEP_KEY_A)) && !(TGEP::Input::IsKeyPressed(TGEP_KEY_S)) && !(TGEP::Input::IsKeyPressed(TGEP_KEY_D)))
    {
        m_PlayerIsMoving = false;
    }


    //Begin Scene
    TGEP::Renderer2D::BeginScene(m_CameraController.GetCamera());

    //Render
    for (uint32_t y = 0; y < m_MapHeight; y++)
    {
        for (uint32_t x = 0; x < m_MapWidth; x++)
        {
            char tile = s_MapTiles[x + y * m_MapWidth];
            if (s_TextureMap.find(tile) != s_TextureMap.end())
            {
                TGEP::Renderer2D::DrawQuad({ x, y, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, s_TextureMap[tile]);
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
        TGEP::Renderer2D::DrawQuad({ m_PlayerPos.x, m_PlayerPos.y, 0.5f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, s_PlayerSprites[m_PlayerDirection][m_CurrentPlayerSprite]);
    }
    else
    {
        TGEP::Renderer2D::DrawQuad({ m_PlayerPos.x, m_PlayerPos.y, 0.5f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, s_PlayerSprites[m_PlayerDirection][0]);
    }

    

    m_CameraController.SetPosition({ m_PlayerPos.x, m_PlayerPos.y, 0.0f });

    //End Scene
    TGEP::Renderer2D::EndScene();
    m_CurrentFrame++;
}

void Sandbox2D::OnImGuiRender()
{
    if (m_Settings)
    {
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
        
        auto stats = TGEP::Renderer2D::GetStats();
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
    }

}

void Sandbox2D::OnEvent(TGEP::Event& e)
{
    m_CameraController.OnEvent(e);
    TGEP::EventDispatcher dispatcher(e);
    dispatcher.Dispatch<TGEP::KeyPressedEvent>(BIND_EVENT_FUNC(Sandbox2D::OnKeyPressed));
}

bool Sandbox2D::OnKeyPressed(TGEP::KeyPressedEvent& e)
{
    if (e.GetKeyCode() == TGEP::Key::Escape)
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


