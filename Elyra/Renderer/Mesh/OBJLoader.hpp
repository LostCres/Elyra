#pragma once
#include "ElyraAPI.hpp"
#include "Core/Core.hpp"
#include "Renderer/Mesh/Mesh.hpp"

namespace Elyra {

    class ELYRA_API OBJLoader {
    public:
        // Load an OBJ file and return a ready-to-render Mesh.
        // Returns nullptr on failure (file not found, malformed data, etc.)
        static Ref<Mesh> Load(const std::string& filepath);
    };

}
