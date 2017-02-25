cmake_minimum_required(VERSION 3.6)
project(EECS_352_Project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/dywapitchtrack.c
        src/dywapitchtrack.h
        src/main.c src/main.h)

add_executable(EECS_352_Project ${SOURCE_FILES})