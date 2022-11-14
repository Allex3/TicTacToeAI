cmake_minimum_required(VERSION 3.21)
project(Tic_Tac_Toe)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(Tic_Tac_Toe main.cpp TicTacToe.h TicTacToe.cpp)
