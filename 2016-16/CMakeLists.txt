cmake_minimum_required(VERSION 3.6)

add_executable(AoC-2016-16 main.cpp)

add_executable(AoC-2016-16-gtest tests.cpp)
target_link_libraries(AoC-2016-16-gtest gtest gtest_main)
