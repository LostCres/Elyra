#pragma once

#include "Elyrapch.hpp"
#include "ElyraAPI.hpp"
#include "Events/Event.hpp"
#include "Core/TimeStep.hpp"
#include "ImGui/ImGuiManager.hpp"

namespace Elyra {

    class ELYRA_API Layer {
    public:
        Layer(const std::string& name = "Layer") : m_DebugName(name) {}
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(TimeStep ts) {}
        virtual void OnImGuiRender(ImGuiContext* context) {} 
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return m_DebugName; }

    protected:
        std::string m_DebugName;
    };

}
