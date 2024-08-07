cmake_minimum_required(VERSION 3.0.0)
project(OpenGL VERSION 0.1.0 LANGUAGES CXX)

add_executable(OpenGL main.cpp)

target_link_libraries(OpenGL glfw)