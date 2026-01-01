cmake_minimum_required(VERSION 3.10)
project(CameraClass)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(CameraClass stb_image.cpp main.cpp)

target_compile_features(CameraClass PRIVATE cxx_std_20)
target_compile_options(CameraClass PRIVATE -stdlib=libc++)
target_link_options(CameraClass PRIVATE -stdlib=libc++)

target_link_libraries(CameraClass ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad stb_image utils)