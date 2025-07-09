#pragma once
#include "ElyraAPI.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Elyra {

    class ELYRA_API PerspectiveCamera
    {
    public:
        PerspectiveCamera(float fovY, float aspectRatio, float nearClip, float farClip);

        void SetPosition(const glm::vec3& position);
        void SetRotation(const glm::vec3& rotation); // pitch, yaw, roll
        void SetFOV(float FOV);
        float GetFOV(){return m_FOV;}

        void SetViewportSize(float width,float height);

        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

        const glm::vec3& GetPosition() const { return m_Position; }
        const glm::vec3& GetRotation() const { return m_Rotation; }

        glm::vec3 GetForwardDirection() const;
        glm::vec3 GetRightDirection() const;
        glm::vec3 GetUpDirection() const;

        void RecalculateViewMatrix();

    private:
        float m_FOV, m_AspectRatio, m_NearClip, m_FarClip;
        float m_width , m_height;
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position = { 0.0f, 0.0f, 3.0f };
        glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f }; // pitch, yaw, roll
    };

} // namespace Elyra
