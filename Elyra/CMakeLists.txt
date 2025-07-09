# ---- glad (static, no PCH) ----
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glad/include)

# ---- Elyra engine (shared DLL) ----
file(GLOB_RECURSE ELYRA_SRC_CPP
     Core/*.cpp
     Events/*.cpp
     Platform/*.cpp)

add_library(Elyra SHARED ${ELYRA_SRC_CPP})
target_precompile_headers(Elyra PRIVATE Elyrapch.hpp)

target_include_directories(Elyra PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}                # finds Elyrapch.hpp & public headers
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/vendor/spdlog/include)

target_link_directories(Elyra PRIVATE
    ${CMAKE_SOURCE_DIR}/vendor/glfw/lib)

target_link_libraries(Elyra
    glad
    ${CMAKE_SOURCE_DIR}/vendor/glfw/lib/libglfw3dll.a
    opengl32
)

# define **only** while BUILDING the DLL
target_compile_definitions(Elyra PRIVATE ELYRA_BUILD_DLL)
