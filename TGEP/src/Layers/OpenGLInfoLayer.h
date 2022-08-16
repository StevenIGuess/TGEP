#pragma once
#include "Layer.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"

namespace TGEP
{

    class OpenGLInfoLayer : public Layer
    {
    public:
        OpenGLInfoLayer() : Layer("Example") {}

        virtual void OnImGuiRender() override;
        virtual void OnEvent(Event& e) override;


    private:
        bool OnKeyPressed(KeyPressedEvent& e);

        bool show_info_layer = false;
    };

}