cmake_minimum_required(VERSION 3.10)
project(ShadersUniform)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(ShadersUniform main.cpp)
target_link_libraries(ShadersUniform ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad)