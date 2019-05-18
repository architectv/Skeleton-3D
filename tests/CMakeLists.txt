cmake_minimum_required(VERSION 3.12)
project(test)

set(CMAKE_CXX_STANDARD 17)

include_directories(. ..)
find_package (Threads)

add_executable(tests
        # test sources
        math3d/vector_test.cpp
        # task sources
        ../math3d/vector.h
        )


target_link_libraries(tests Threads::Threads)