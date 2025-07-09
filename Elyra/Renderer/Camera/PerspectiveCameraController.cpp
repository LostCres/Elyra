#include "Elyrapch.hpp"
#include "PerspectiveCameraController.hpp"
#include "Events/EventDispatcher.hpp"

#include "Input/Input.hpp"
#include "Core/KeyCodes.hpp"

namespace Elyra {

    PerspectiveCameraController::PerspectiveCameraController(float fovY, float aspectRatio, float nearClip, float farClip)
        : m_Camera(fovY, aspectRatio, nearClip, farClip)
    {}

    void PerspectiveCameraController::OnUpdate(TimeStep ts)
    {
        float velocity = m_CameraSpeed * ts.GetSeconds();
        glm::vec3 position = m_Camera.GetPosition();

        if (Input::IsKeyPressed(Key_W))
            position += m_Camera.GetForwardDirection() * velocity;
        if (Input::IsKeyPressed(Key_S))
            position -= m_Camera.GetForwardDirection() * velocity;
        if (Input::IsKeyPressed(Key_A))
            position -= m_Camera.GetRightDirection() * velocity;
        if (Input::IsKeyPressed(Key_D))
            position += m_Camera.GetRightDirection() * velocity;
        if (Input::IsKeyPressed(Key_Left_Shift))
            position -= m_Camera.GetUpDirection() * velocity;
        if (Input::IsKeyPressed(Key_Space))
            position += m_Camera.GetUpDirection() * velocity;

        m_Camera.SetPosition(position);
        m_Camera.SetRotation({ m_Pitch, m_Yaw, 0.0f });
    }

    void PerspectiveCameraController::OnEvent(Event& e)
    {
        switch (e.GetEventType())
        {
            case EventType::MouseMoved:
                OnMouseMoved(static_cast<MouseMovedEvent&>(e));
                break;

            case EventType::KeyPressed:
                OnKeyPressed(static_cast<KeyPressedEvent&>(e));
                break;

            default:
                break;
        }
    }


    bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent& e)
    {
        if(!Input::IsMouseButtonPressed(Right)){
            m_FirstMouse = true; 
            return false;
        } 

        if (m_FirstMouse)
        {
            m_LastMousePosition = { e.GetX(), e.GetY() };
            m_FirstMouse = false;
            return false;
        }

        float xOffset = e.GetX() - m_LastMousePosition.x;
        float yOffset = m_LastMousePosition.y - e.GetY(); // reversed since y-coordinates go from bottom to top

        m_LastMousePosition = { e.GetX(), e.GetY() };

        xOffset *= m_MouseSensitivity;
        yOffset *= m_MouseSensitivity;

        m_Yaw += xOffset;
        m_Pitch += yOffset;

        m_Pitch = glm::clamp(m_Pitch, -89.0f, 89.0f);

        return false;
    }

    bool PerspectiveCameraController::OnKeyPressed(KeyPressedEvent& e)
    {
        return false;
    }

    void PerspectiveCameraController::OnResize(float width, float height)
    {
        m_Camera.SetViewportSize(width, height);
    }

}
