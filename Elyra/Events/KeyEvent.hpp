#pragma once

#include "Event.hpp"

namespace Elyra {

    class KeyEvent : public Event {
    public:
        inline int GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
        KeyEvent(int keycode) : m_KeyCode(keycode) {}
        int m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(int keycode, int repeatCount)
            : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

        inline int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override {
            return std::string(GetName()) + ": " + std::to_string(m_KeyCode) +
                " (" + std::to_string(m_RepeatCount) + " repeats)";
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        int m_RepeatCount;
    };

    class KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(int keycode)
            : KeyEvent(keycode) {}

        EVENT_CLASS_TYPE(KeyReleased)

        std::string ToString() const override {
            return std::string(GetName()) + ": " + std::to_string(m_KeyCode);
        }
    };

}
