#pragma once

#include "../Layer.h"
#include "../Events/Event.h"
#include "../../ImGui/imgui.h"
#include <glad/glad.h>

namespace TGEP 
{

    class OpenGLInfoLayer : public Layer
    {   
    public:
        OpenGLInfoLayer() : Layer("Example")
        {

        }

        virtual void OnImGuiRender() override
        {
            if(show_info_layer)
            {
                ImGui::Begin("OpenGL Info");
                std::stringstream glGpuInfo;
                glGpuInfo << "OpenGL GPU: " << glGetString(GL_RENDERER) << "\n";
                std::stringstream glVersionInfo;
                glVersionInfo << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";
                ImGui::Text(glGpuInfo.str().c_str());
                ImGui::Text(glVersionInfo.str().c_str());
                ImGui::End();
            }
        }
        void OnEvent(Event &e) override
        {
            EventDispatcher dispatcher(e);

            dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(OpenGLInfoLayer::OnKeyPressed));
        }


    private:
        bool OnKeyPressed(KeyPressedEvent &e)
        {
            if(e.GetKeyCode() == Key::ScrollLock)
            {
                if(show_info_layer)
                {
                    show_info_layer = false;
                    return false; 
                }
                show_info_layer = true;
            }

            return false;
        }

        bool show_info_layer = false;
    };

}