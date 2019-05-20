cmake_minimum_required(VERSION 3.13)
project(test)

set(CMAKE_CXX_STANDARD 17)

include_directories(.. .)
find_package (Threads)

add_executable(tests
        # test sources
        ../tests/math3d/vector_test.cpp
        ../tests/math3d/matrix_test.cpp
        # task sources
        ../math3d/vector4.h
        ../math3d/matrix4.h
        ../math3d/matrix3.h
        # gtest sources
        gtest/gtest-all.cc
        gtest/gtest_main.cc
)

target_link_libraries(tests Threads::Threads)