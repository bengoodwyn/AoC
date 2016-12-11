cmake_minimum_required(VERSION 3.6)
project(AoC)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")

include_directories(/usr/local/opt/openssl/include
        /usr/local/include)
link_directories(/usr/local/opt/openssl/lib
        /usr/local/lib)

add_subdirectory(2016-01)
add_subdirectory(2016-02)
add_subdirectory(2016-03)
add_subdirectory(2016-04)
add_subdirectory(2016-05)
add_subdirectory(2016-06)
add_subdirectory(2016-07)
add_subdirectory(2016-08)
add_subdirectory(2016-09)
add_subdirectory(2016-10)
