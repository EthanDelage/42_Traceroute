cmake_minimum_required(VERSION 3.30)
project(traceroute C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(traceroute
    include/traceroute.h
    src/main.c)
