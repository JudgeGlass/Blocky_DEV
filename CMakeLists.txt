cmake_minimum_required(VERSION 3.16)
project(blocky)


set(CMAKE_CXX_STANDARD 14)

#find_package(GLEW REQUIRED)
#find_library(GLFW_LIB glfw)
#if(NOT GLFW_LIB)
#    message(FATAL_ERROR "glfw library not found")
#endif()


#LINK_LIBRARIES(GLEW glfw GL GLU)
LINK_LIBRARIES(glew32 glfw3 opengl32 glu32)
include_directories("include")

add_executable(blocky 
    src/main.cpp
        src/imgui.cpp
        src/imgui_impl_glfw.cpp
        src/imgui_impl_opengl3.cpp
        src/imgui_draw.cpp
        src/imgui_tables.cpp
        src/imgui_widgets.cpp
        src/imgui_demo.cpp

    src/game/blocky.cpp

    src/renderer/shader.cpp
    src/renderer/renderer.cpp
    src/renderer/chunk_mesh.cpp
    src/renderer/hud.cpp
    src/renderer/lighting.cpp

    src/world/chunk.cpp
    src/world/world.cpp
    src/world/player.cpp
    src/world/SimplexNoise.cpp
        src/renderer/lighting.cpp include/renderer/font.hpp)