cmake_minimum_required(VERSION 3.12)
project(test)

set(CMAKE_CXX_STANDARD 17)

include_directories(. ..)
find_package (Threads)

add_executable(test_vector
        # test sources
        math3d/vector_test.cpp
        # gtest files
        gtest/gtest-all.cc
        gtest/gtest_main.cc
        # task sources
        ../math3d/vector.h
        )

add_executable(test_matrix
        # test sources
        math3d/matrix_test.cpp
        # gtest files
        gtest/gtest-all.cc
        gtest/gtest_main.cc
        # task sources
        ../math3d/vector.h
        )


target_link_libraries(test_vector Threads::Threads)
target_link_libraries(test_matrix Threads::Threads)