cmake_minimum_required(VERSION 3.30)
project(traceroute C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(traceroute
    include/options.h
    include/traceroute.h
    src/main.c
    src/options.c
    src/traceroute.c
    src/socket.c
    include/socket.h
    src/udp.c
    include/udp.h
    src/print.c
    include/print.h
    src/common.c
    include/common.h)
