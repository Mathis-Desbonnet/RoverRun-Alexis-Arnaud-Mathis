cmake_minimum_required(VERSION 3.28)
project(RoverRun C)

set(CMAKE_C_STANDARD 11)

add_executable(RoverRun main.c
        loc.c
        map.c
        moves.c
        queue.c
        stack.c
        loc.h
        map.h
        moves.h
        queue.h
        stack.h)
