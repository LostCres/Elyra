# --- ImGui (static, no PCH) ---
add_library(ImGui STATIC
    ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(ImGui PUBLIC
    ${CMAKE_SOURCE_DIR}/vendor/imgui
    ${CMAKE_SOURCE_DIR}/vendor/imgui/backends
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
)
# ---- glad (static, no PCH) ----build and added 
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glad/include)

# ---- Elyra engine (shared DLL) ----

# Gather engine sources
file(GLOB_RECURSE ELYRA_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Events/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/OpenGL/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Camera/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Layer/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Input/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UI/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ECS/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Script/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Mesh/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Core/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Shader/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Material/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Texture/*.cpp
    # Renderer/Shadow/*.cpp  <- uncomment when shadow system is implemented
)

add_library(Elyra SHARED ${ELYRA_SRC})

# Enable precompiled headers
target_precompile_headers(Elyra PRIVATE Elyrapch.hpp)

# Include directories for engine
target_include_directories(Elyra PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Elyra                         # To find Elyrapch.hpp, etc.
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/vendor/glm/include
    ${CMAKE_SOURCE_DIR}/vendor/stb_image
)

# Link directories for glfw
target_link_directories(Elyra PRIVATE
    ${CMAKE_SOURCE_DIR}/vendor/glfw/lib
)

# Link libraries
target_link_libraries(Elyra
    ImGui
    glad
    ${CMAKE_SOURCE_DIR}/vendor/glfw/lib/libglfw3dll.a
    opengl32
)

# Define only when building the DLL (PRIVATE)
target_compile_definitions(Elyra PRIVATE ELYRA_BUILD_DLL)

# Platform define — propagated to consumers (Sandbox) via PUBLIC
target_compile_definitions(Elyra PUBLIC ELYRA_PLATFORM_WINDOWS)
