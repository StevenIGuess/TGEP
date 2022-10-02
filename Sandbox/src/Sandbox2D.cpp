#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <TGEP.h>

Sandbox2D::Sandbox2D() 
	: TGEP::Layer("Sanbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
    
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(TGEP::DeltaTime deltaTime)
{
    //Update
    t0 = m_Profiler->get_cpu_cycles();
    m_DeltaTime = deltaTime;
    m_CameraController.OnUpdate(deltaTime);

    //Render
    TGEP::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
    TGEP::RenderCommand::Clear();

    //Begin Scene
    TGEP::Renderer2D::BeginScene(m_CameraController.GetCamera());

    TGEP::Renderer2D::DrawQuad({ 1.0f, 1.0f }, { 1.0f, 1.0f }, m_SquareColor );
    TGEP::Renderer2D::DrawQuad({ -1.0f, -1.0f }, { 1.5f, 1.5f }, m_SquareColor);
    
    TGEP::Renderer2D::EndScene();


    /*
    auto Square2DShader = m_ShaderLibary.Get("Square2D");
    
    TGEP::Renderer::Push(m_SquareVertexArray, Square2DShader, transform);
    */

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
        ImGui::TextColored(ImVec4(0, 1, 1, 1), "General Settings");

        ImGui::ColorEdit4("Color", (float*)&m_SquareColor);

        ImGui::Separator();
        ImGui::TextColored(ImVec4(0, 1, 1, 1), "Advanced Settings");

        if (ImGui::TreeNode("Advanced performance info"))
        {
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