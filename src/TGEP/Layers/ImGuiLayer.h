#pragma once 

#include "../Layer.h"

#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"
#include "../Events/ApplicationEvent.h"

namespace TGEP 
{

    class DLLEXP ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& event);

        bool show_imgui_window = true;

    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &e);
        bool OnMouseMovedEvent(MouseMovedEvent &e);
        bool OnMouseScrolledEvent(MouseScrolledEvent &e);
        bool OnKeyPressedEvent(KeyPressedEvent &e);
        bool OnKeyReleasedEvent(KeyReleasedEvent &e);
        bool OnKeyTypedEvent(KeyTypedEvent &e);
        bool OnWindowResizedEvent(WindowResizedEvent &e);
    private:
        float m_Time = 0.0f;
    };
}