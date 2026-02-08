cmake_minimum_required (VERSION 3.9)

project (chess)

add_executable(out
src/main.cpp
src/helper-functions.h
src/helper-functions.cpp
src/square/square.h
src/square/square.cpp
src/board/board.h
src/board/board.cpp
src/board/pieces/pieces.h
src/board/pieces/pieces.cpp
src/board/pieces/move-sets/move-set.h
src/board/pieces/move-sets/move-set.cpp
)
