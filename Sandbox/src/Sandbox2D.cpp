#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <TGEP.h>

Sandbox2D::Sandbox2D() 
	: TGEP::Layer("Sanbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
    PROFILE_FUNCTION();
    m_Texture = TGEP::Texture2D::Create("assets/textures/Texture.png");

    m_QuadData[0].Pos = { 1.0f, 1.0f, 0.0f };
    m_QuadData[0].Scale = { 1.0f, 1.0f};
    m_QuadData[0].Color = { 0.2f, 0.3f, 0.8f, 1.0f};
    m_QuadData[0].TextureScale = 1.0f;

    m_QuadData[1].Pos = { 2.0f, 1.0f, 0.0f };
    m_QuadData[1].Scale = { 1.0f, 1.0f };
    m_QuadData[1].Color = { 0.2f, 0.3f, 0.8f, 1.0f };
    m_QuadData[1].TextureScale = 1.0f;

    m_QuadDataR[0].Pos = { 3.5f, 1.0f, 0.0f};
    m_QuadDataR[0].Scale = { 1.0f, 1.0f };
    m_QuadDataR[0].Rot= 45.0f;
    m_QuadDataR[0].Color = { 0.2f, 0.3f, 0.8f, 1.0f };
    m_QuadDataR[0].TextureScale = 1.0f;

    m_QuadDataR[1].Pos = { 4.5f, 1.0f, 0.0f };
    m_QuadDataR[1].Scale = { 1.0f, 1.0f };
    m_QuadDataR[1].Rot = 45.0f;
    m_QuadDataR[1].Color = { 0.2f, 0.3f, 0.8f, 1.0f };
    m_QuadDataR[1].TextureScale = 1.0f;
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
    

    //Begin Scene
    TGEP::Renderer2D::BeginScene(m_CameraController.GetCamera());
    
    //Render
    for (int i = 0; i < m_NumberOfQuadsX; i++)
    {
        for (int j = 0; j < m_NumberOfQuadsY; j++)
        {
            float r = i / 0.5;
            float g = j / 0.5;
            float b = (i + 1) / (j + 1);
            TGEP::Renderer2D::DrawQuad({ m_QuadData[0].Pos.x * i, m_QuadData[0].Pos.y * j }, m_QuadData[0].Scale, { m_QuadData[0].Color.x * r,  m_QuadData[0].Color.y + g, m_QuadData[0].Color.z * b, m_QuadData[0].Color.w});
        }
    }

    
    //End Scene
    TGEP::Renderer2D::EndScene();



    //TGEP::Renderer2D::DrawQuad(m_QuadData[0].Pos, m_QuadData[0].Scale, m_QuadData[0].Color);
    //TGEP::Renderer2D::DrawQuad(m_QuadData[1].Pos, m_QuadData[1].Scale, m_QuadData[1].Color, m_Texture, m_QuadData[1].TextureScale);
    //TGEP::Renderer2D::DrawQuadR(m_QuadDataR[0].Pos, m_QuadDataR[0].Scale, m_QuadDataR[0].Rot, m_QuadDataR[0].Color);
    //TGEP::Renderer2D::DrawQuadR(m_QuadDataR[1].Pos, m_QuadDataR[1].Scale, m_QuadDataR[1].Rot, m_QuadDataR[1].Color, m_Texture, m_QuadDataR[1].TextureScale);
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

        ImGui::DragInt("Number of Quads on X axis", &m_NumberOfQuadsX);
        ImGui::DragInt("Number of Quads on Y axis", &m_NumberOfQuadsY);


        if (ImGui::TreeNode("Quad data"))
        {
            for (int i = 0; i < (sizeof(m_QuadData) / sizeof(QuadData)); i++)
            {
                ImGui::Separator;
                std::stringstream ss;
                ss << "Quad " << i;
                if (ImGui::TreeNode(ss.str().c_str()))
                {
                    ImGui::DragFloat3("Position", (float*)&m_QuadData[i].Pos);
                    ImGui::DragFloat2("Scale", (float*)&m_QuadData[i].Scale);
                    ImGui::ColorEdit4("Color", (float*)&m_QuadData[i].Color);
                    ImGui::DragFloat("Texture Scale", (float*)&m_QuadData[i].TextureScale);
                    ImGui::TreePop();
                }
            }

            for (int i = 0; i < (sizeof(m_QuadDataR) / sizeof(QuadDataR)); i++)
            {
                ImGui::Separator;
                std::stringstream ss;
                ss << "QuadR " << i;
                if (ImGui::TreeNode(ss.str().c_str()))
                {
                    ImGui::DragFloat3("Position", (float*)&m_QuadDataR[i].Pos);
                    ImGui::DragFloat2("Scale", (float*)&m_QuadDataR[i].Scale);
                    ImGui::DragFloat("Rotation", (float*)&m_QuadDataR[i].Rot);
                    ImGui::ColorEdit4("Color", (float*)&m_QuadDataR[i].Color);
                    ImGui::DragFloat("Texture Scale", (float*)&m_QuadDataR[i].TextureScale);
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
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


