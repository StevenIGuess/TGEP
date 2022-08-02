#include "pch.h"
#include "Camera.h"

namespace TGEP
{
    OrthoCamera::OrthoCamera(float left, float right, float top, float bottom, float near, float far) 
    : m_Projection(glm::ortho(left, right, top, bottom, near, far))
    {
        UpdatedMatrices();
    }

    void OrthoCamera::UpdatedMatrices()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        m_View = glm::inverse(transform);
        m_PVM = m_Projection * m_View;
    }
}