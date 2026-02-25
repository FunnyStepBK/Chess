#ifndef WINDOWS_H
#define WINDOWS_H

#include <ncurses.h>
#include <vector>

// A function to create a window
WINDOW* create_win(float height, float width, float starty, float startx);

// A function to delete a window
void delete_win(WINDOW* window);

// A function to properly setup all the windows required by the programm
std::vector<WINDOW*> initialize_windows();

// A function to clear a windows contents and re-initialized it's borders with the COLOR_PAIR(4) attribute
void clear_and_box_win(WINDOW* window);

#endif
