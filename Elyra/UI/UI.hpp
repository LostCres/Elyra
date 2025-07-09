#pragma once
#include "Elyrapch.hpp"
#include "ElyraAPI.hpp"

namespace Elyra {

/**
 * Thin wrapper around ImGui, exposing a clean Elyra‑style API.
 * Add more widgets as your engine grows—keep all ImGui calls hidden here.
 */
class ELYRA_API UI
{
public:
    static void BeginPanel(const std::string& title, bool* open = nullptr, int flags = 0);
    static void EndPanel();

    static void Text(const std::string& content);
    static bool Button(const std::string& label);
    static bool Checkbox(const std::string& label, bool* v);
    static bool SliderFloat(const std::string& label, float* value, float min, float max);
	static bool InputText(const std::string& label, std::string& buffer);
};

} // namespace Elyra