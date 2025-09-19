#pragma once
#include "Elyrapch.hpp"
#include "ElyraAPI.hpp"
#include <glm/glm.hpp>


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

    static void BeginDockspace();
    static void EndDockspace();
    
    static bool TreeNode(const std::string& label);
    static void TreePop();
    
    static void Separator();
    static void SameLine();
    
    static bool DragFloat(const std::string& label, float* value, float speed = 1.0f, float min = 0.0f, float max = 0.0f);
    static bool DragFloat3(const std::string& label, glm::vec3& values, float speed = 1.0f, float min = 0.0f, float max = 0.0f);
    
    static bool ColorEdit3(const std::string& label, glm::vec3& color);
    static bool ColorEdit4(const std::string& label, glm::vec4& color);
};

} // namespace Elyra