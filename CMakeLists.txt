cmake_minimum_required(VERSION 3.0.0)
project(OpenGL VERSION 0.1.0 LANGUAGES C CXX)

add_executable(OpenGL main.cpp glad.h src/glad.c)

target_link_libraries(OpenGL glfw)

set(CMAKE_INCLUDE_CURRENT_DIR ON)