cmake_minimum_required(VERSION 3.10)
project(LightMapsSpecularMap)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(LightMapsSpecularMap stb_image.cpp main.cpp)

target_compile_features(LightMapsSpecularMap PRIVATE cxx_std_20)
target_compile_options(LightMapsSpecularMap PRIVATE -stdlib=libc++)
target_link_options(LightMapsSpecularMap PRIVATE -stdlib=libc++)

target_link_libraries(LightMapsSpecularMap ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad stb_image utils)