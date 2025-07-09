#include "Elyrapch.hpp"
#include "PerspectiveCamera.hpp"

namespace Elyra {

    PerspectiveCamera::PerspectiveCamera(float fovY, float aspectRatio, float nearClip, float farClip)
        : m_FOV(fovY), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip)
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
        RecalculateViewMatrix();
    }

    void PerspectiveCamera::SetPosition(const glm::vec3& position)
    {
        m_Position = position;
        RecalculateViewMatrix();
    }

    void PerspectiveCamera::SetRotation(const glm::vec3& rotation)
    {
        m_Rotation = rotation;
        RecalculateViewMatrix();
    }

    glm::vec3 PerspectiveCamera::GetForwardDirection() const
    {
        float yaw = glm::radians(m_Rotation.y);
        float pitch = glm::radians(m_Rotation.x);

        glm::vec3 direction;
        direction.x = cos(pitch) * cos(yaw);
        direction.y = sin(pitch);
        direction.z = cos(pitch) * sin(yaw);

        return glm::normalize(direction);
    }

    glm::vec3 PerspectiveCamera::GetRightDirection() const
    {
        return glm::normalize(glm::cross(GetForwardDirection(), glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    glm::vec3 PerspectiveCamera::GetUpDirection() const
    {
        return glm::normalize(glm::cross(GetRightDirection(), GetForwardDirection()));
    }

    void PerspectiveCamera::SetViewportSize(float width, float height)
    {
        m_AspectRatio = width / height;
        m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
        RecalculateViewMatrix();
    }

    void PerspectiveCamera::RecalculateViewMatrix()
    {
        glm::vec3 direction = GetForwardDirection();
        m_ViewMatrix = glm::lookAt(m_Position, m_Position + direction, glm::vec3(0.0f, 1.0f, 0.0f));
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }


}
