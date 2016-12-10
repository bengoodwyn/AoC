cmake_minimum_required(VERSION 3.6)
project(AoC)

set(CMAKE_CXX_STANDARD 11)

include_directories("/usr/local/opt/openssl/include")
link_directories("/usr/local/opt/openssl/lib")

add_subdirectory(2016-01)
add_subdirectory(2016-02)
add_subdirectory(2016-03)
add_subdirectory(2016-04)
add_subdirectory(2016-05)
add_subdirectory(2016-06)
add_subdirectory(2016-07)
