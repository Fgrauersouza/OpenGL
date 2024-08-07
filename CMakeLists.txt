cmake_minimum_required(VERSION 3.0.0)
project(OpenGL VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

add_executable(OpenGL main.cpp glad.h src/glad.c)

find_package(OpenGL REQUIRED)

target_link_libraries(OpenGL 
    glfw
    OpenGL::GL)

set(CMAKE_INCLUDE_CURRENT_DIR ON)