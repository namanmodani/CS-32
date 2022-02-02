cmake_minimum_required(VERSION 3.21)
project(Homework_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Homework_1A testMap.cpp Map.cpp Map.h)
add_executable(Homework_1B testCarMap.cpp CarMap.cpp CarMap.h Map.cpp Map.h)
add_executable(Homework_1C testnewMap.cpp newMap.cpp newMap.h)