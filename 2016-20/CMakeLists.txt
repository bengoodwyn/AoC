cmake_minimum_required(VERSION 3.6)

add_executable(AoC-2016-20 main.cpp)

add_executable(AoC-2016-20-gtest tests.cpp)
target_link_libraries(AoC-2016-20-gtest gtest gtest_main)
