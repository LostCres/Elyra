# ---- Sandbox Application ----
add_executable(Sandbox
    SandboxApp.cpp
    ${CMAKE_SOURCE_DIR}/Elyra/EntryPoint.cpp
)

# Link against the Elyra engine DLL
target_link_libraries(Sandbox PRIVATE Elyra)

# Include Elyra headers
target_include_directories(Sandbox PRIVATE
    ${CMAKE_SOURCE_DIR}/Elyra
)

# Platform
target_compile_definitions(Sandbox PRIVATE ELYRA_PLATFORM_WINDOWS)

# Copy required DLLs to the Sandbox output directory
add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Elyra>
        $<TARGET_FILE_DIR:Sandbox>

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/vendor/glfw/lib/glfw3.dll"
        $<TARGET_FILE_DIR:Sandbox>
)
