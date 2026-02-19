#include "windows.hpp"

using namespace std;

// A function to create windows with attributes
WINDOW* create_win(float height, float width, float starty, float startx)
{
    WINDOW* temp_win;

    temp_win = newwin(height, width, starty, startx);

    box(temp_win, 0, 0);
    wrefresh(temp_win);

    return temp_win;
}

// A function to delete a window
void delete_win(WINDOW* window)
{
    // Replaces the characters used for creating the border of a window with 'Space' so we won't get any ugly remnants
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

    wrefresh(window);
    delwin(window);
}

// A function to properly setup all the windows required by the programm
vector<WINDOW*> initialize_windows()
{
    int main_win_width = ((COLS/100) * 70) - 2;
    int log_win_width = ((COLS/100) * 50) - 3;

    // Main_window
    WINDOW* main_window = create_win(LINES, main_win_width, 0, 1);

    // Log_window
    WINDOW* log_window = create_win(LINES, log_win_width, 0, main_win_width + 4);

    int y_main, x_main;
    getmaxyx(main_window, y_main, x_main);

    // Main_window component windows
    WINDOW* input_window = newwin(3, x_main - 2, y_main - 4, 2);

    keypad(input_window, TRUE);
    wborder(input_window, ' ', ' ', ACS_HLINE, ' ',  ACS_HLINE, ACS_HLINE, ' ', ' ');

    float y_log, x_log;
    getmaxyx(log_window, y_log, x_log);

    // Log_window component windows
    WINDOW* moves_log_win = create_win((y_log/100) * 80, (x_log/100) * 88, 1, main_win_width + 6);
    WINDOW* eval_log_win = create_win(y_log - 2, (x_log/100) * 8, 1, main_win_width + ((x_log/100) * 88) + 7);
    WINDOW* warns_log_win = create_win((y_log/100) * 18, (x_log/100) * 88, ((y_log/100) * 80) + 1, main_win_width + 6);

    return {main_window, log_window, input_window, moves_log_win, eval_log_win, warns_log_win};
}

// A function to refresh all the windows in a collection (vector)
void refresh_win(vector<WINDOW*> collection)
{
    for(WINDOW* w : collection)
    {
        wrefresh(w);
    }
}
