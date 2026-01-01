cmake_minimum_required(VERSION 3.10)
project(CameraCircle)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(CameraCircle stb_image.cpp main.cpp)

target_compile_features(CameraCircle PRIVATE cxx_std_20)
target_compile_options(CameraCircle PRIVATE -stdlib=libc++)
target_link_options(CameraCircle PRIVATE -stdlib=libc++)

target_link_libraries(CameraCircle ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw glad stb_image utils)