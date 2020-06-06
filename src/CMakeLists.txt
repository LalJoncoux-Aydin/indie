cmake_minimum_required(VERSION 3.10)
project(sources)

set(
    SRCS
    Bomberman.cpp
    indie.cpp
    Map.cpp
)

add_library(lib ${SRCS} ${HEADERS})
