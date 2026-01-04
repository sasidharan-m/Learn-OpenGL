cmake_minimum_required(VERSION 3.10)
project(LightMapsExcercise4)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(LightMapsExcercise4 stb_image.cpp main.cpp)

target_compile_features(LightMapsExcercise4 PRIVATE cxx_std_20)
target_compile_options(LightMapsExcercise4 PRIVATE -stdlib=libc++)
target_link_options(LightMapsExcercise4 PRIVATE -stdlib=libc++)

target_link_libraries(LightMapsExcercise4 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad stb_image utils)