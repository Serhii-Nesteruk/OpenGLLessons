cmake_minimum_required(VERSION 3.0...3.5)

project(OpenGLLessons)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(dependencies/glfw-3.3.7)
include_directories(dependencies/GLEW/include)
include_directories(dependencies/GLAD)
include_directories(dependencies/KHR)
include_directories(dependencies/GLM)

add_executable(OpenGLLessons main.cpp dependencies/GLAD/glad.c Gl.h Gl.cpp Utils.cpp Utils.h Window.h Window.cpp "VAO.h" "VAO.cpp" "VBO.h" "VBO.cpp")

target_link_libraries(OpenGLLessons PUBLIC glfw)

add_custom_command(TARGET OpenGLLessons PRE_BUILD
   COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/assets
   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/assets
   COMMAND ${CMAKE_COMMAND} -E copy_directory
   ${CMAKE_CURRENT_SOURCE_DIR}/assets
   ${CMAKE_CURRENT_BINARY_DIR}/assets
)

add_custom_target(
  Copy-Assets
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/assets
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/assets
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/assets
  ${CMAKE_CURRENT_BINARY_DIR}/assets
)