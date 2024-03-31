cmake_minimum_required(VERSION 3.27)
project(untitled)
add_definitions(-D_MBCS)
set(CMAKE_CXX_STANDARD 23)
include_directories(./easyx/include)
link_directories(./easyx/lib64)
link_libraries(libeasyx.a)


add_executable(untitled main.cpp
        Player.h
        AI.cpp
        AI.h
        Chess.cpp
        Chess.h
        Game.h
        Game.cpp
        Player.cpp
)
