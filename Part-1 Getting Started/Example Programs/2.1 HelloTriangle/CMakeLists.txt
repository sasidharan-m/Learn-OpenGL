cmake_minimum_required(VERSION 3.10)
project(HelloTriangle)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(HelloTriangle main.cpp)
target_link_libraries(HelloTriangle ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad)
