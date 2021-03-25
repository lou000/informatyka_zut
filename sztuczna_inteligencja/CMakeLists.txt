cmake_minimum_required(VERSION 3.5)

project(sztuczna_inteligencja LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE sudoku_SRC CONFIGURE_DEPENDS "*.h" "*.hpp" "*.cpp")
add_executable(sudoku ${sudoku_SRC})

