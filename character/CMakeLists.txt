cmake_minimum_required(VERSION 3.10)
project(character)

set(
    CHARAC
    Bomb.cpp
    Player.cpp
    IA.cpp
)

add_library(lib_charac ${CHARAC} ${HEADERS})