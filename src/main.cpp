#include <ncurses.h>

#include "board/board.h"
#include "./helper-functions.h"
#include "./windows/windows.hpp"

using namespace std;

int main()
{
    Board board;

    initscr();
    noecho();
    keypad(stdscr, TRUE);

    start_color();
    use_default_colors();
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_BLUE, -1);
    init_pair(3, COLOR_YELLOW, -1);

    vector<WINDOW*> windows_collection = initialize_windows();

    WINDOW* main_window = windows_collection[0];
    WINDOW* log_window = windows_collection[1];

    WINDOW* input_window = windows_collection[2];

    WINDOW* moves_log_win = windows_collection[3];
    WINDOW* eval_log_win = windows_collection[4];
    WINDOW* warns_log_win = windows_collection[5];

    setlocale(LC_ALL, "");

    mvwprintw(input_window, 1, 0, "> Type 'quit'/'Quit' to quit or 'reset'/'Reset' to reset the board\n>> ");

    bool running = true;
    while(running)
    {
        board.print_board(main_window);
        board.print_score(main_window);

        // Refresh all the windows in the collection
        refresh_win(windows_collection);

        char res[6];
        if(!handle_input(res, board, false, running, input_window, warns_log_win)) continue;

        wclear(warns_log_win);
        box(warns_log_win, 0, 0);

        float x = getmaxx(warns_log_win);

        if(board.move_piece(res, input_window, warns_log_win))
        {
            // If the move was valid then check - If the opponent player got a check? If yes, then check if it's a checkmate
            if(board.is_checked(board.get_turn()))
            {
                if(board.is_checkmate(board.get_turn()))
                {
                    wattron(warns_log_win, COLOR_PAIR(2));
                    for(int i = 0; i < board.mate_warn_ascii.size(); i++)
                    {
                        mvwprintw(warns_log_win, 3 + i, 2, "%s", board.mate_warn_ascii[i].c_str());
                    }
                    wattroff(warns_log_win, COLOR_PAIR(2));

                    mvwprintw(input_window, 1, 0, "Type 'quit'/'Quit' to quit, or type 'reset'/'Reset' to reset the board and play another game!");

                    wrefresh(warns_log_win);
                    wrefresh(input_window);

                    while(handle_input(res, board, true, running, input_window, warns_log_win)) {
                        mvwprintw(warns_log_win, 1, 1, "> Please choose a valid option.");
                    }

                } else
                {
                    wattron(warns_log_win, COLOR_PAIR(3));
                    for(int i = 0; i < board.check_warn_ascii.size(); i++)
                    {
                        mvwprintw(warns_log_win, 3 + i, (x/100) * 21, "%s", board.check_warn_ascii[i].c_str());
                    }
                    wattroff(warns_log_win, COLOR_PAIR(3));

                }

            }

        }

    }

    for(WINDOW* w : windows_collection)
    {
        delete_win(w);
    }

    refresh();
    endwin();

    return 0;
}
