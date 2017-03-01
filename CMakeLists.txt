cmake_minimum_required(VERSION 3.6)
project(EECS_352_Project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/dywapitchtrack.c
        src/dywapitchtrack.h
        src/pitch_utils.cpp src/pitch_utils.h src/main.cpp src/main.h src/note.cpp src/note.h src/note_name.cpp src/note_name.h)

add_executable(EECS_352_Project ${SOURCE_FILES})