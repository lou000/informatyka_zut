cmake_minimum_required(VERSION 3.5)

project(PS_Lab07_2 LANGUAGES C)

add_executable(PS_Lab07_2 main.c)
target_link_libraries(PS_Lab07_2 crypt pthread)
