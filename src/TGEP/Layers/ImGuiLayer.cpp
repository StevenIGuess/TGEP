#include "ImGuiLayer.h"
#include "../pch.h"

#include "../ImGui/ImGuiOpenGlRenderer.h"
#include "../ImGui/imgui.h"
#include "../Application.h"
#include "../Events/KeyCodes.h"

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
        ImGuiIO &io = ImGui::GetIO();
        Application &app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        if(show_imgui_window)
            ImGui::ShowDemoWindow(&show_imgui_window);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    }

    void ImGuiLayer::OnEvent(Event &event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FUNC(ImGuiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FUNC(ImGuiLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FUNC(ImGuiLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FUNC(ImGuiLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(ImGuiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FUNC(ImGuiLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FUNC(ImGuiLayer::OnWindowResizedEvent));
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.AddMouseButtonEvent(e.GetMouseButton(), GLFW_PRESS);

        return false; //not sure if already handled
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.AddMouseButtonEvent(e.GetMouseButton(), GLFW_RELEASE);


        return false; //not sure if already handled
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent &e)
    {
        ImGuiIO  &io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(), e.GetY());

        return false; //not sure if already handled
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent &e)
    {
        ImGuiIO  &io = ImGui::GetIO();
        io.MouseWheelH += e.GetXOffset();
        io.MouseWheel += e.GetYOffset();

        return false; //not sure if already handled
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent &e)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGuiKey imgui_key = TGEPKeycodeToImGuiKeycode(e.GetKeyCode());
        io.AddKeyEvent(imgui_key, GLFW_PRESS);

        LOG_CORE_INFO("KEY PRESS {0}", TGEPKeycodeToImGuiKeycode(e.GetKeyCode()));

        return false; //not sure if already handled
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent &e)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGuiKey imgui_key = TGEPKeycodeToImGuiKeycode(e.GetKeyCode());
        io.AddKeyEvent(imgui_key, GLFW_RELEASE);

        LOG_CORE_INFO("KEY RELEASE {0}", TGEPKeycodeToImGuiKeycode(e.GetKeyCode()));

        return false; //not sure if already handled
    }

    bool ImGuiLayer::OnWindowResizedEvent(WindowResizedEvent &e)
    {
        ImGuiIO  &io = ImGui::GetIO();
        return false; //not sure if already handled
    }
}