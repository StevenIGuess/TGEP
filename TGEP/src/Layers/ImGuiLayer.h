#pragma once 

#include "Layer.h"

#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

namespace TGEP
{

    class DLLEXP ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnEvent(Event& e) override;
        void OnImGuiRender() override;

        void Begin();
        void End();

    private:
        float m_Time = 0.0f;
    private:
        bool show_ImGui = false;
        bool OnKeyPressed(KeyPressedEvent& e);
    };
}