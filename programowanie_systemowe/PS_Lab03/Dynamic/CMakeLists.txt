cmake_minimum_required(VERSION 3.5)
set(CMAKE_SHARED_LIBRARY_PREFIX )
project(PS_Lab03 LANGUAGES C)

add_executable(PS_Lab03 main.c)
target_link_libraries(PS_Lab03 dl Groups)
add_library(Groups SHARED lib.c)
