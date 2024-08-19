cmake_minimum_required(VERSION 3.13)

set( CMAKE_VERBOSE_MAKEFILE on )
project(chess C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

include_directories(lib)
add_executable(${PROJECT_NAME}-sim
    main/sim/main.cpp
    lib/app/piece.cpp
    lib/app/board.cpp
    lib/app/actor.cpp
)

add_library(Unity STATIC
  external/Unity/src/unity.c
)

target_include_directories(Unity PUBLIC
  external/Unity/src
)

# include_directories(external/Unity/src)
add_executable(${PROJECT_NAME}-test
    unittest/chess_test.cpp
    unittest/test_location.cpp
    unittest/test_piece.cpp
    unittest/test_actor.cpp
    lib/app/piece.cpp
    lib/app/board.cpp
    lib/app/actor.cpp

)
target_include_directories(${PROJECT_NAME}-test PUBLIC
  external/Unity/src,
)

target_link_libraries(${PROJECT_NAME}-test 
  Unity
)

include(CTest)
add_test(NAME test1 COMMAND chess-test)
