#include "ImGuiLayer.h"
#include "../pch.h"

#include "ImGuiOpenGlRenderer.h"
#include "imgui.h"
#include "../Application.h"

namespace TGEP
{
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
    {

    }

    ImGuiLayer::~ImGuiLayer()
    {

    }
    
    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO &io = ImGui::GetIO();
        io.BackendFlags = ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags = ImGuiBackendFlags_HasSetMousePos;

        ImGui_ImplOpenGL3_Init("#version 460");

    }

    void ImGuiLayer::OnDetach()
    {

    }

    void ImGuiLayer::OnUpdate()
    {
        LOG_CORE_INFO("STARTED UPDATE");
        ImGuiIO &io = ImGui::GetIO();
        Application &app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
        LOG_CORE_INFO("WINDOWSIZE");

        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;
        LOG_CORE_INFO("DELTATIME");

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        LOG_CORE_INFO("NEWFRAME");

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    }

    void ImGuiLayer::OnEvent(Event &e)
    {

    }
}