#pragma once
#include "ElyraAPI.hpp"
#include <GLFW/glfw3.h>
namespace Elyra {

    class ELYRA_API TimeStep {
    public:
        TimeStep(float time = 0.0f)
            : m_Time(time) {}

        operator float() const { return m_Time; }

        float GetSeconds() const { return m_Time; }
        float GetMilliseconds() const { return m_Time * 1000.0f; }

        static float RawTime() { return (float)glfwGetTime(); }
        static TimeStep Now() { return TimeStep((float)glfwGetTime()); }

    private:
        float m_Time;
    };
    
    inline Elyra::TimeStep operator-(const Elyra::TimeStep& lhs, const Elyra::TimeStep& rhs) {
        return Elyra::TimeStep((float)lhs - (float)rhs);
    }

}