cmake_minimum_required(VERSION 3.10)
project(BasicLightingDiffuse)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(BasicLightingDiffuse stb_image.cpp main.cpp)

target_compile_features(BasicLightingDiffuse PRIVATE cxx_std_20)
target_compile_options(BasicLightingDiffuse PRIVATE -stdlib=libc++)
target_link_options(BasicLightingDiffuse PRIVATE -stdlib=libc++)

target_link_libraries(BasicLightingDiffuse ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad stb_image utils)