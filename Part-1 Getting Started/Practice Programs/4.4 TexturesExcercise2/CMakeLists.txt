cmake_minimum_required(VERSION 3.10)
project(TexturesExcercise2)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(TexturesExcercise2 stb_image.cpp main.cpp)

target_compile_features(TexturesExcercise2 PRIVATE cxx_std_20)
target_compile_options(TexturesExcercise2 PRIVATE -stdlib=libc++)
target_link_options(TexturesExcercise2 PRIVATE -stdlib=libc++)

target_link_libraries(TexturesExcercise2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad stb_image utils)