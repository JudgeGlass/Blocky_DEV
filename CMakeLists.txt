cmake_minimum_required(VERSION 3.16)
project(blocky)


set(CMAKE_CXX_STANDARD 14)

find_package(GLEW REQUIRED)
find_library(GLFW_LIB glfw)
if(NOT GLFW_LIB)
    message(FATAL_ERROR "glfw library not found")
endif()


LINK_LIBRARIES(GLEW glfw GL GLU)

include_directories("include")

add_executable(blocky 
    src/main.cpp

    src/game/blocky.cpp

    src/renderer/shader.cpp
    src/renderer/renderer.cpp
    src/renderer/chunk_mesh.cpp

    src/world/chunk.cpp
    src/world/world.cpp
    src/world/player.cpp
)