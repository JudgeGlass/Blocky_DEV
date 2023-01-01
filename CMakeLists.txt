cmake_minimum_required(VERSION 3.16)
project(blocky)

include_directories("include")

set(CMAKE_CXX_STANDARD 14)
file(GLOB SRC_SOURCES src/*.cpp)
LINK_LIBRARIES(GLEW glfw GL GLU)
#add_compile_options(-municode) #Needed for windows using gcc
add_executable(blocky ${SRC_SOURCES})