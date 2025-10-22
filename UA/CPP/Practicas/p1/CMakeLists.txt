cmake_minimum_required(VERSION 3.8)

project(p1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "-Wall -g")
set(CMAKE_CXX_STANDARD 11)

add_executable(prac1 prac1.cc)
