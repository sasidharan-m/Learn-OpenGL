cmake_minimum_required(VERSION 3.10)
project(MaterialsExcercise1)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(MaterialsExcercise1 stb_image.cpp main.cpp)

target_compile_features(MaterialsExcercise1 PRIVATE cxx_std_20)
target_compile_options(MaterialsExcercise1 PRIVATE -stdlib=libc++)
target_link_options(MaterialsExcercise1 PRIVATE -stdlib=libc++)

target_link_libraries(MaterialsExcercise1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad stb_image utils)