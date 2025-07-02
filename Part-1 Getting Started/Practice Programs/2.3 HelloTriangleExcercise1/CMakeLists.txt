cmake_minimum_required(VERSION 3.10)
project(HelloTriangleExcercise1)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(HelloTriangleExcercise1 main.cpp)
target_link_libraries(HelloTriangleExcercise1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad)