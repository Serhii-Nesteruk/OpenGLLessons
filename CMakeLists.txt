cmake_minimum_required(VERSION 3.0...3.5)

project(OpenGLLessons)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(dependencies/glfw-3.3.7)
include_directories(dependencies/GLEW/include)
include_directories(dependencies/GLAD)
include_directories(dependencies/KHR)
include_directories(dependencies/GLM)

add_executable(OpenGLLessons main.cpp dependencies/GLAD/glad.c OpenGLApp.h OpenGlApp.cpp Utils.cpp Utils.h)

target_link_libraries(OpenGLLessons PUBLIC glfw)