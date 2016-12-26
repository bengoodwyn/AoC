cmake_minimum_required(VERSION 3.6)

add_executable(AoC-2016-12 main.cpp Vm.h)

add_executable(AoC-2016-12-gtest tests.cpp Vm.h)
target_link_libraries(AoC-2016-12-gtest gtest gtest_main)
