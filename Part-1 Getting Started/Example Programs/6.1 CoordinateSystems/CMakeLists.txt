cmake_minimum_required(VERSION 3.10)
project(CoordinateSystems)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(CoordinateSystems stb_image.cpp main.cpp)
target_link_libraries(CoordinateSystems ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad stb_image utils)