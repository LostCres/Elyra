add_executable(Sandbox
    sandbox.cpp
)

target_link_libraries(Sandbox PRIVATE Elyra)

target_include_directories(Sandbox PRIVATE
    ${CMAKE_SOURCE_DIR}/Elyra
)

target_compile_definitions(Elyra PRIVATE ELYRA_BUILD_DLL)


# Automatically copy Elyra.dll next to sandbox executable
add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Elyra>               # Source DLL
        $<TARGET_FILE_DIR:Sandbox>         # Destination folder
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/vendor/glfw/lib/glfw3.dll"
        $<TARGET_FILE_DIR:Sandbox>
)
