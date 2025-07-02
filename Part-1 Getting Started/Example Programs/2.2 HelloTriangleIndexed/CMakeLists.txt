cmake_minimum_required(VERSION 3.10)
project(HelloTriangleIndexed)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(HelloTriangleIndexed main.cpp)
target_link_libraries(HelloTriangleIndexed ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad)