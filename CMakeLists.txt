cmake_minimum_required(VERSION 3.7)

project(sierpinski-carpet)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(PkgConfig)
pkg_check_modules(SDL2_GFX SDL2_gfx)
include_directories(${SDL2_GFX_INCLUDE_DIRS})

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -O0 -Wall -Werror -fdump-rtl-expand")

SET(SRCS main.c)

add_executable(sierpinski-carpet ${SRCS})
target_link_libraries(sierpinski-carpet ${SDL2_LIBRARIES} ${SDL2_GFX_LIBRARIES} m)

