#pragma once

#include "Elyrapch.hpp"
#include "Event.hpp"

namespace Elyra {

    class ELYRA_API MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(float x, float y)
            : m_MouseX(x), m_MouseY(y) {}

        float GetX() const { return m_MouseX; }
        float GetY() const { return m_MouseY; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

    private:
        float m_MouseX, m_MouseY;
    };

    class ELYRA_API MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(float xOffset, float yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset) {}

        float GetXOffset() const { return m_XOffset; }
        float GetYOffset() const { return m_YOffset; }

        std::string ToString() const override {
            std::ostringstream oss;
            oss << "MouseScrolledEvent: (" << m_XOffset << ", " << m_YOffset << ")";
            return oss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

    private:
        float m_XOffset, m_YOffset;
    };

    class ELYRA_API MouseButtonEvent : public Event {
    public:
        MouseButton GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)

    protected:
        MouseButtonEvent(MouseButton button)
            : m_Button(button) {}

        MouseButton m_Button;
    };

    class ELYRA_API MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(MouseButton button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override {
            return "MouseButtonPressedEvent: " + std::to_string((int)m_Button);
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class ELYRA_API MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(MouseButton button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override {
            return "MouseButtonReleasedEvent: " + std::to_string((int)m_Button);
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

}
