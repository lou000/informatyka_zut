cmake_minimum_required(VERSION 3.5)

project(PS_Lab06 LANGUAGES C)
link_libraries(pthread)
add_executable(PS_Lab06 main.c timer.h timer.c)
