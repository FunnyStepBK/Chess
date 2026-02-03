cmake_minimum_required (VERSION 3.9)

project (chess)

add_executable(out src/main.cpp src/piece/piece.h src/piece/piece.cpp src/board/board.h src/board/board.cpp)
