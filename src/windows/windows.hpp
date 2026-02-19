#ifndef  windowsH
#define windowsH

#include <ncurses.h>
#include <vector>

using namespace std;

// A function to create a window
WINDOW* create_win(float height, float width, float starty, float startx);

// A function to delete a window
void delete_win(WINDOW* window);

// A function to properly setup all the windows required by the programm
vector<WINDOW*> initialize_windows();

// A function to refresh all the windows in a collection (vector)
void refresh_win(vector<WINDOW*> colleciton);

#endif
