cmake_minimum_required(VERSION 3.6)

add_executable(AoC-2016-14 main.cpp)

target_link_libraries(AoC-2016-14 crypto)

add_executable(AoC-2016-14-gtest tests.cpp)
target_link_libraries(AoC-2016-14-gtest gtest gtest_main crypto)
