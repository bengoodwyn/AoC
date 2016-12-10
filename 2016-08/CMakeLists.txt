cmake_minimum_required(VERSION 3.6)

add_executable(AoC-2016-08 main.cpp)
add_executable(AoC-2016-08-gtest pixel.cpp)
target_link_libraries(AoC-2016-08-gtest gtest gtest_main)
