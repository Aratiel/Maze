cmake_minimum_required(VERSION 3.2)

project(maze_generate)

add_compile_options(
   -Werror

   -Wall
   -Wextra
   -Wpedantic

   -Wcast-align
   -Wcast-qual
   -Wconversion
   -Wctor-dtor-privacy
   -Wenum-compare
   -Wfloat-equal
   -Wnon-virtual-dtor
   -Wold-style-cast
   -Woverloaded-virtual
   -Wredundant-decls
   -Wsign-conversion
   -Wsign-promo
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB PROJECT_SOURCES
    "*.h"  "*.cc"
)

add_library(maze_generate STATIC ${PROJECT_SOURCES})

target_include_directories(maze_generate PUBLIC ${CMAKE_SOURCE_DIR})


