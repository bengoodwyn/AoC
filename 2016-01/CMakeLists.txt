cmake_minimum_required(VERSION 3.6)

add_executable(AoC-2016-01 main.cpp Traveler.h)

add_executable(AoC-2016-01-gtest tests.cpp Traveler.h)
target_link_libraries(AoC-2016-01-gtest gtest gtest_main)
