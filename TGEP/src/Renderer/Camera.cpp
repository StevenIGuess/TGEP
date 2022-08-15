#include "pch.h"
#include "Camera.h"

namespace TGEP
{
    OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float near, float far)
        : m_Projection(glm::ortho(left, right, bottom, top, near, far))
    {
        UpdatedMatrices();
    }

    void OrthoCamera::UpdatedMatrices()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1));
        m_View = glm::inverse(transform);
        m_PVM = m_Projection * m_View;
    }
}