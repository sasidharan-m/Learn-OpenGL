cmake_minimum_required(VERSION 3.10)
project(BasicLightingExcercise3)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(BasicLightingExcercise3 stb_image.cpp main.cpp)

target_compile_features(BasicLightingExcercise3 PRIVATE cxx_std_20)
target_compile_options(BasicLightingExcercise3 PRIVATE -stdlib=libc++)
target_link_options(BasicLightingExcercise3 PRIVATE -stdlib=libc++)

target_link_libraries(BasicLightingExcercise3 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad stb_image utils)