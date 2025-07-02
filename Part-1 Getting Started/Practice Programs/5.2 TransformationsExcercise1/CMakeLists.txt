cmake_minimum_required(VERSION 3.10)
project(TransformationsExcercise1)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(TransformationsExcercise1 stb_image.cpp main.cpp)
target_link_libraries(TransformationsExcercise1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad stb_image utils)