cmake_minimum_required (VERSION 3.9)
project (chess)

find_package(Catch2 3 REQUIRED)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(tests
tests/test.cpp
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
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain ${CURSES_LIBRARIES})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
target_link_libraries(out ${CURSES_LIBRARIES})
add_compile_options(-Wall -lncurses)
