cmake_minimum_required(VERSION 3.10)
project(Materials)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(Materials stb_image.cpp main.cpp)

target_compile_features(Materials PRIVATE cxx_std_20)
target_compile_options(Materials PRIVATE -stdlib=libc++)
target_link_options(Materials PRIVATE -stdlib=libc++)

target_link_libraries(Materials ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad stb_image utils)