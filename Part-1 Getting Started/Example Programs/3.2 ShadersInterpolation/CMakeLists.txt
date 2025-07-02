cmake_minimum_required(VERSION 3.10)
project(ShadersInterpolation)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(ShadersInterpolation main.cpp)
target_link_libraries(ShadersInterpolation ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad)