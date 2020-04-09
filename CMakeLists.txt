cmake_minimum_required(VERSION 3.15)
project(avm)

set(CMAKE_CXX_STANDARD 14)

add_executable(avm main.cpp avm32/avm32.cpp avm2/avm32.cpp avm2/avm32.hpp)