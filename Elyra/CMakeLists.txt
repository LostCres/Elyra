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
    ${CMAKE_CURRENT_SOURCE_DIR}/Layer/*.cpp
)

add_library(Elyra SHARED ${ELYRA_SRC})

# Enable precompiled headers
target_precompile_headers(Elyra PRIVATE Elyrapch.hpp)

# Include directories for engine
target_include_directories(Elyra PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}                         # To find Elyrapch.hpp, etc.
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/vendor/spdlog/include
)

# Link directories for glfw
target_link_directories(Elyra PRIVATE
    ${CMAKE_SOURCE_DIR}/vendor/glfw/lib
)

# Link libraries
target_link_libraries(Elyra
    glad
    ${CMAKE_SOURCE_DIR}/vendor/glfw/lib/libglfw3dll.a
    opengl32
)

# Define only when building the DLL
target_compile_definitions(Elyra PRIVATE ELYRA_BUILD_DLL)
