cmake_minimum_required(VERSION 3.6)

add_executable(AoC-2016-01 main.cpp year2016day01.h)

add_executable(AoC-2016-01-gtest tests.cpp year2016day01.h)
target_link_libraries(AoC-2016-01-gtest gtest gtest_main)
