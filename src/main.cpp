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

    int main_win_width = ((COLS/100) * 70) - 2;
    int log_win_width = ((COLS/100) * 50) - 3;

    WINDOW* main_window = create_win(LINES, main_win_width, 0, 1);
    WINDOW* log_window = create_win(LINES, log_win_width, 0, main_win_width + 4);


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
        board.print_score(main_window);

        wrefresh(main_window);
        wrefresh(input_window);
        wrefresh(log_window);


        char res[6];
        echo();
        mvwgetnstr(input_window, 2, 3, res, 6);
        noecho();
        if(!get_input(res, board, false, running, input_window, log_window)) continue;

        if(board.move_piece(res))
        {
            if(board.is_checked(board.get_turn()))
            {
                if(board.is_checkmate(board.get_turn()))
                {

                }
            }
        }

    }

    delete_win(main_window);
    delete_win(input_window);
    delete_win(log_window);

    refresh();
    endwin();

    return 0;
}
