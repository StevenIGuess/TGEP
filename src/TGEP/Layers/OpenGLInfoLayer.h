#pragma once

#include "../Layer.h"
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
            ImGui::Begin("OpenGL Info");
            std::stringstream glGpuInfo;
            glGpuInfo << "OpenGL GPU: " << glGetString(GL_RENDERER) << "\n";
            std::stringstream glVersionInfo;
            glVersionInfo << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";
            ImGui::Text(glGpuInfo.str().c_str());
            ImGui::Text(glVersionInfo.str().c_str());
            ImGui::End();
        }
    };

}