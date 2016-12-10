cmake_minimum_required(VERSION 3.6)

add_executable(AoC-2016-09 main.cpp)
add_executable(AoC-2016-09-gtest decompress.cpp)
target_link_libraries(AoC-2016-09-gtest gtest gtest_main)
