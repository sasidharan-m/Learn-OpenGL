cmake_minimum_required(VERSION 3.10)

project(HelloWorld)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(HelloWindow main.cpp)
target_link_libraries(HelloWindow ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad)
