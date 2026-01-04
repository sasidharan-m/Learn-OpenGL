cmake_minimum_required(VERSION 3.10)
project(LightMapsExcercise2)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(LightMapsExcercise2 stb_image.cpp main.cpp)

target_compile_features(LightMapsExcercise2 PRIVATE cxx_std_20)
target_compile_options(LightMapsExcercise2 PRIVATE -stdlib=libc++)
target_link_options(LightMapsExcercise2 PRIVATE -stdlib=libc++)

target_link_libraries(LightMapsExcercise2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad stb_image utils)