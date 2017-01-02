cmake_minimum_required(VERSION 3.6)

add_executable(AoC-2016-17 main.cpp)

target_link_libraries(AoC-2016-17 crypto)

add_executable(AoC-2016-17-gtest tests.cpp)
target_link_libraries(AoC-2016-17-gtest gtest gtest_main crypto)
