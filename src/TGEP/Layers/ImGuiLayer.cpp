#include "ImGuiLayer.h"
#include "../pch.h"

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

        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;



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
        dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FUNC(ImGuiLayer::OnKeyTypedEvent));
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
        io.KeysDown[e.GetKeyCode()] = true;

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];

        LOG_CORE_INFO("KEY PRESS {0}", e.GetKeyCode());
        return false; //not sure if already handled
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent &e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = false;

        LOG_CORE_INFO("KEY RELEASE {0}", e.GetKeyCode());

        return false; //not sure if already handled
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent &e)
    {
        ImGuiIO& io = ImGui::GetIO();
        int c = e.GetKeyCode();
        if(c > 0 && c < 0x10000)
        {
            io.AddInputCharacter((unsigned short)c);
        }

        return false; //not sure if already handled
    } 

    bool ImGuiLayer::OnWindowResizedEvent(WindowResizedEvent &e)
    {
        ImGuiIO  &io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, e.GetWidth(), e.GetHeight());

        return false; //not sure if already handled
    }
}