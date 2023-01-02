cmake_minimum_required(VERSION 3.16)
project(blocky)


set(CMAKE_CXX_STANDARD 14)

LINK_LIBRARIES(GLEW glfw GL GLU)

include_directories("include")

add_executable(blocky 
    src/main.cpp

    src/game/blocky.cpp

    src/renderer/shader.cpp
)