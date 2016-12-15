cmake_minimum_required(VERSION 3.6)

set(SOURCE_FILES Bot.cpp)
set(TEST_FILES OutputBinTests.cpp BotTests.cpp ValueTests.cpp MicrochipFactoryTests.cpp)

add_executable(AoC-2016-10 main.cpp ${SOURCE_FILES})
add_executable(AoC-2016-10-gtest ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(AoC-2016-10-gtest gtest gtest_main)
