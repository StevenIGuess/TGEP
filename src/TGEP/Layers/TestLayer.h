#pragma once

#include "../Layer.h"
#include "../../ImGui/imgui.h"
#include <glm/glm.hpp>

namespace TGEP 
{

    class TestLayer : public Layer
    {   
    public:
        TestLayer() : Layer("TestLayer")
        {
        }
        void OnEvent(Event &e) override;

        glm::vec3 GetCamPosition() { return m_CamPos; }
        float GetCamRotation() { return m_CamRot; }
    private:
        glm::vec3 m_CamPos = glm::vec3(0.0f);
        float m_CamRot = 0.0f;
        bool OnKeyPressed(KeyPressedEvent &e);
    };

}