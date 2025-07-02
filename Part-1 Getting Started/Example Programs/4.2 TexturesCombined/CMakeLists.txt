cmake_minimum_required(VERSION 3.10)
project(TexturesCombined)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(TexturesCombined stb_image.cpp main.cpp)
target_link_libraries(TexturesCombined ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad stb_image utils)