cmake_minimum_required(VERSION 3.5)

project(sztuczna_inteligencja LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(si_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/external/SIplusplus_wchar
    ${CMAKE_SOURCE_DIR}/external/assert)
include_directories(${si_INCLUDE_DIRS})
file(GLOB_RECURSE sicpp_SRC CONFIGURE_DEPENDS "external/SIplusplus_wchar/*.h" "external/SIplusplus_wchar/*.hpp" "external/SIplusplus_wchar/*.cpp")
file(GLOB_RECURSE assert_SRC CONFIGURE_DEPENDS "external/assert/*.h" "external/assert/*.cpp")

file(GLOB_RECURSE sudoku_SRC CONFIGURE_DEPENDS "Sudoku/*.h" "Sudoku/*.cpp")
file(GLOB_RECURSE slide_SRC CONFIGURE_DEPENDS "SlidePuzzle/*.h" "SlidePuzzle/*.cpp")
file(GLOB_RECURSE connect4_SRC CONFIGURE_DEPENDS "Connect4/*.h" "Connect4/*.cpp")

set(si_INCLUDE_SRCS
    ${sicpp_SRC}
    ${assert_SRC}
    )

add_executable(sudoku ${sudoku_SRC} ${si_INCLUDE_SRCS})
add_executable(slide_puzzle ${slide_SRC} ${si_INCLUDE_SRCS})
add_executable(connect4 ${connect4_SRC} ${si_INCLUDE_SRCS})
