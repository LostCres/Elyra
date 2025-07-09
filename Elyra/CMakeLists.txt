add_library(Elyra SHARED
    Application.cpp
    Window.cpp
    Log.cpp
    ${CMAKE_SOURCE_DIR}/vendor/glad/src/glad.c    # manually add glad source
)

# Include paths
target_include_directories(Elyra PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_SOURCE_DIR}/vendor/spdlog/include
)


# Link GLFW statically
target_link_directories(Elyra PRIVATE
    ${CMAKE_SOURCE_DIR}/vendor/glfw/lib
)

target_link_libraries(Elyra
    ${CMAKE_SOURCE_DIR}/vendor/glfw/lib/libglfw3dll.a
    opengl32
)


target_compile_definitions(Elyra PRIVATE ELYRA_BUILD_DLL)

