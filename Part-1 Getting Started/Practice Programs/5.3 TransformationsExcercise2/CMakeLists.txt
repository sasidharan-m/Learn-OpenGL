cmake_minimum_required(VERSION 3.10)
project(TransformationsExcercise2)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(TransformationsExcercise2 stb_image.cpp main.cpp)

target_compile_features(TransformationsExcercise2 PRIVATE cxx_std_20)
target_compile_options(TransformationsExcercise2 PRIVATE -stdlib=libc++)
target_link_options(TransformationsExcercise2 PRIVATE -stdlib=libc++)

target_link_libraries(TransformationsExcercise2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad stb_image utils)