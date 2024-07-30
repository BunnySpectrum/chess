cmake_minimum_required(VERSION 3.13)

set( CMAKE_VERBOSE_MAKEFILE on )
project(chess_sim C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)


include_directories(../../lib)
add_executable(${PROJECT_NAME}
    main.cpp
    ../../lib/app/piece.cpp
    ../../lib/app/board.cpp
)


