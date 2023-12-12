cmake_minimum_required(VERSION 3.22)

project(oxygen)

set(CMAKE_CXX_STANDARD 20)

add_executable(oxy src/main.cpp
        src/generation.h
        src/parser.h
        src/tokenization.h)