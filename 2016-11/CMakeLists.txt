cmake_minimum_required(VERSION 3.6)

add_executable(AoC-2016-11 main.cpp Facility.h)
add_executable(AoC-2016-11-gtest tests.cpp Facility.h)
target_link_libraries(AoC-2016-11-gtest gtest gtest_main)
