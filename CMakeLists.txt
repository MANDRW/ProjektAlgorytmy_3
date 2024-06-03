cmake_minimum_required(VERSION 3.28)
project(ProjektAlgorytmy_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(ProjektAlgorytmy_3 main.cpp
        game.h
        game.cpp
        element.h
        ui.h
        ui.cpp
        minmax.cpp)
