#pragma once
#include <glm/glm.hpp>

namespace TGEP
{
    class OrthoCamera
    {
    public:
        OrthoCamera(float left, float right, float bottom, float top);
        void SetProjection(float left, float right, float bottom, float top);

        void SetPosition(const glm::vec3& pos) { m_Position = pos; UpdatedMatrices(); }
        glm::vec3 GetPosition() { return m_Position; }

        void SetRotation(const float& rot) { m_Rotation = rot; UpdatedMatrices(); }
        float GetRotation() { return m_Rotation; }


        glm::mat4 GetProjection() { return m_Projection; }
        glm::mat4 GetView() { return m_View; }
        const glm::mat4 GetVPM() const { return m_VPM; }


    private:
        void UpdatedMatrices();

        glm::vec3 m_Position = glm::vec3(0.0f);
        float m_Rotation = 0.0f;

        glm::mat4 m_Projection;
        glm::mat4 m_View;
        glm::mat4 m_VPM;//Buffer the view projection matrix to save performance.
    };

}