cmake_minimum_required(VERSION 3.10)

add_library(glad STATIC glad.c)

target_include_directories(glad PUBLIC ${PROJECT_SOURCE_DIR}/GLAD)
target_link_libraries(glad PUBLIC khr)
