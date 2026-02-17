#include <iostream>
#include <ncurses.h>

#include "board/board.h"
#include "./helper-functions.h"

using namespace std;

int main()
{
    Board board;

    initscr();
    noecho();
    keypad(stdscr, TRUE);

    WINDOW* main_window = create_win(LINES, COLS/2 - 2, 0, 1);
    WINDOW* log_window = create_win(LINES, COLS/2 - 2, 0, COLS/2 + 1);


    int y_main, x_main;
    getmaxyx(main_window, y_main, x_main);

    WINDOW* input_window = newwin(3, x_main - 2, y_main - 4, 2);

    keypad(input_window, TRUE);
    wborder(input_window, ' ', ' ', ACS_HLINE, ' ',  ACS_HLINE, ACS_HLINE, ' ', ' ');

    wrefresh(input_window);

    mvwprintw(input_window, 1, 0, "> Type 'quit'/'Quit' to quit or 'reset'/'Reset' to reset the board\n>> ");

    bool running = true;
    while(running)
    {
        board.print_board(main_window);

        wrefresh(main_window);
        wrefresh(input_window);
        wrefresh(log_window);


        char res[6];
        echo();
        mvwgetnstr(input_window, 2, 3, res, 6);
        noecho();
        if(!get_input(res, board, false, running, input_window)) continue;


    }

    delete_win(main_window);
    delete_win(input_window);
    delete_win(log_window);

    refresh();
    endwin();

    return 0;
}
