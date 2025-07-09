#include "UI/UI.hpp"
#include "Elyrapch.hpp"
#include <imgui.h>
#include <cstring> 

namespace Elyra {

    void UI::BeginPanel(const std::string& title, bool* open, int flags)
    {
        ImGui::Begin(title.c_str(), open, flags);
    }

    void UI::EndPanel()
    {
        ImGui::End();
    }

    void UI::Text(const std::string& content)
    {
        ImGui::TextUnformatted(content.c_str());
    }

    bool UI::Button(const std::string& label)
    {
        return ImGui::Button(label.c_str());
    }

    bool UI::Checkbox(const std::string& label, bool* v)
    {
        return ImGui::Checkbox(label.c_str(), v);
    }

    bool UI::SliderFloat(const std::string& label, float* value, float min, float max)
	{
		return ImGui::SliderFloat(label.c_str(), value, min, max);
	}

	bool UI::InputText(const std::string& label, std::string& buffer)
	{
		char temp[256];
		std::strncpy(temp, buffer.c_str(), sizeof(temp));
		temp[sizeof(temp) - 1] = '\0';

		bool changed = ImGui::InputText(label.c_str(), temp, sizeof(temp));
		if (changed)
			buffer = std::string(temp);

		return changed;
	}

} // namespace Elyra
