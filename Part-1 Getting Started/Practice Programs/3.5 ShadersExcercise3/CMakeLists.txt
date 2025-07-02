cmake_minimum_required(VERSION 3.10)
project(ShadersExcercise3)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(ShadersExcercise3 main.cpp)
target_link_libraries(ShadersExcercise3 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad)