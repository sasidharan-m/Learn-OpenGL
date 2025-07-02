cmake_minimum_required(VERSION 3.10)
project(Textures)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(Textures stb_image.cpp main.cpp)
target_link_libraries(Textures ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad stb_image utils)