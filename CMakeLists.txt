cmake_minimum_required (VERSION 3.9)
project (chess)

find_package(Catch2 3 REQUIRED)

set(CURSES_NEED_WIDE TRUE)
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
find_library(PANEL_LIBRARY panelw)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(tests
tests/test.cpp
src/helper-functions.hpp
src/helper-functions.cpp
src/windows/windows.hpp
src/windows/windows.cpp
src/board/square/square.hpp
src/board/square/square.cpp
src/board/board.hpp
src/board/board.cpp
src/board/pieces/pieces.hpp
src/board/pieces/pieces.cpp
src/board/pieces/move-sets/move-set.hpp
src/board/pieces/move-sets/move-set.cpp
src/board/pieces/piece-templates/piece-template.hpp
src/board/pieces/piece-templates/piece-template.cpp
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain ${CURSES_LIBRARIES})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(out
src/main.cpp
src/helper-functions.hpp
src/helper-functions.cpp
src/windows/windows.hpp
src/windows/windows.cpp
src/board/square/square.hpp
src/board/square/square.cpp
src/board/board.hpp
src/board/board.cpp
src/board/pieces/pieces.hpp
src/board/pieces/pieces.cpp
src/board/pieces/move-sets/move-set.hpp
src/board/pieces/move-sets/move-set.cpp
src/board/pieces/piece-templates/piece-template.hpp
src/board/pieces/piece-templates/piece-template.cpp
)
target_link_libraries(out
    ${CURSES_LIBRARIES}
    ${PANEL_LIBRARY}
)
