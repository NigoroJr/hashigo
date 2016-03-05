cmake_minimum_required(VERSION 2.8)
project(hashigo)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#enable_testing()

add_subdirectory(src)
#add_subdirectory(test)
