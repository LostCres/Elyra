#pragma once
#include "ElyraAPI.hpp"
#include "Core/TimeStep.hpp"
#include "Events/Event.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Renderer/Camera/PerspectiveCamera.hpp"

namespace Elyra {

    class ELYRA_API PerspectiveCameraController
    {
    public:
        PerspectiveCameraController(float fovY, float aspectRatio, float nearClip = 0.1f, float farClip = 100.0f);

        void OnUpdate(TimeStep ts);
        void OnEvent(Event& e);
        void OnResize(float width, float height);

        const PerspectiveCamera& GetCamera() const { return m_Camera; }
        PerspectiveCamera& GetCamera() { return m_Camera; }

        float GetSpeed() const { return m_CameraSpeed; }
        void SetSpeed(float speed) { m_CameraSpeed = speed; }

    private:
        bool OnMouseMoved(MouseMovedEvent& e);
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnKeyPressed(KeyPressedEvent& e);

        void UpdateView();

    private:
        PerspectiveCamera m_Camera;
        float m_CameraSpeed = 5.0f;
        float m_MouseSensitivity = 0.1f;

        glm::vec2 m_LastMousePosition = { 0.0f, 0.0f };
        bool m_FirstMouse = true;

        float m_Yaw = -90.0f;   // Facing -Z
        float m_Pitch = 0.0f;

    };

}
