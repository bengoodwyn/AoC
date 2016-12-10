cmake_minimum_required(VERSION 3.6)

add_executable(AoC-2016-05 main.cpp)

target_link_libraries(AoC-2016-05 crypto)

add_executable(AoC-2016-05-gtest tests.cpp)
target_link_libraries(AoC-2016-05-gtest gtest gtest_main crypto)
