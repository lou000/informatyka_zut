cmake_minimum_required(VERSION 3.5)

project(PS_Lab08 LANGUAGES C)

add_executable(manager manager.c shared.h)
add_executable(worker worker.c shared.h)
target_link_libraries(manager rt)
