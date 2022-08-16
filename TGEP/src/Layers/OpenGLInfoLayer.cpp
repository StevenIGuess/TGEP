#include "pch.h"
#include "OpenGLInfoLayer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

namespace TGEP
{
    void OpenGLInfoLayer::OnImGuiRender()
    {
        if (show_info_layer)
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

    void OpenGLInfoLayer::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(OpenGLInfoLayer::OnKeyPressed));
    }

    bool OpenGLInfoLayer::OnKeyPressed(KeyPressedEvent& e)
    {
        if (e.GetKeyCode() == Key::ScrollLock)
        {
            if (show_info_layer)
            {
                show_info_layer = false;
                return false;
            }
            show_info_layer = true;
        }

        return false;
    }

}