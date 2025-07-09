cmake_minimum_required(VERSION 3.17)
project(Elyra)

set(CMAKE_CXX_STANDARD 20)

# Build Engine as shared library
add_subdirectory(Elyra)

# Build Sandbox
add_subdirectory(Sandbox)