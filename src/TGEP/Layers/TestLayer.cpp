#include "ImGuiLayer.h"
#include "../pch.h"
#include "imgui.h"
#include "../../ImGui/imgui_impl_glfw.h"
#include "../../ImGui/imgui_impl_opengl3.h"

#include "../Application.h"
#include "../Events/KeyCodes.h"

namespace TGEP
{

    void TestLayer::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(TestLayer::OnKeyPressed));
    }

    bool TestLayer::OnKeyPressed(KeyPressedEvent &e)
    {
        if(e.GetKeyCode() == Key::W)
        {
            m_CamPos.y += 0.01f;
        }
        if(e.GetKeyCode() == Key::A)
        {
            m_CamPos.x -= 0.01f;
        }
        if(e.GetKeyCode() == Key::S)
        {
            m_CamPos.y -= 0.01f;
        }
        if(e.GetKeyCode() == Key::D)
        {
            m_CamPos.x += 0.01f;
        }

        if(e.GetKeyCode() == Key::Q)
        {
            m_CamRot += 0.01f;
        }
        if(e.GetKeyCode() == Key::E)
        {
            m_CamRot -= 0.01f;
        }

        return false; // not completely handled yet
    }

}