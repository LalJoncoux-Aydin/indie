cmake_minimum_required(VERSION 3.10)
project(graphic)

set(
    GRAPH
    Help.cpp
    Intro.cpp
    Menu.cpp
    GameMusic.cpp
    Settings.cpp
    Game.cpp
    Win.cpp
    WinMulti.cpp
    Loose.cpp
)

add_library(lib_graph ${GRAPH} ${HEADERS})
