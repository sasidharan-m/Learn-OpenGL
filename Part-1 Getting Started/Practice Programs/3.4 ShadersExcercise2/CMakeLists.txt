cmake_minimum_required(VERSION 3.10)
project(ShadersExcercise2)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(ShadersExcercise2 main.cpp)
target_link_libraries(ShadersExcercise2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad)