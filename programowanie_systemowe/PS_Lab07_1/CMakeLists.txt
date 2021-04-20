cmake_minimum_required(VERSION 3.5)

project(PS_Lab07_1 LANGUAGES C)

add_executable(PS_Lab07_1 main.c)
target_link_libraries(PS_Lab07_1 crypt)
