#include <ncurses.h>
#include <panel.h>

#include "board/board.hpp"
#include "./helper-functions.hpp"
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
    init_pair(4, COLOR_BLACK, -1);

    // A collection to store all the windows in one place - useful for refreshing and deleting them all collectively
    vector<WINDOW*> windows_collection = initialize_windows();

    // Two collection of panels - One for the left side aka the main_win and the other one of the right side, i.e. the log_win panels
    PANEL* main_panels[2];
    PANEL* log_panels[4];

    WINDOW* main_window = windows_collection[0];
    WINDOW* log_window = windows_collection[1];

    WINDOW* input_window = windows_collection[2];

    WINDOW* moves_log_win = windows_collection[3];
    WINDOW* eval_log_win = windows_collection[4];
    WINDOW* warn_log_win = windows_collection[5];

    // A var to store the window in which the cursor is currently present
    WINDOW* active_window = main_window;

    main_panels[0] = new_panel(main_window);
    main_panels[1] = new_panel(input_window);

    log_panels[0] = new_panel(log_window);
    log_panels[1] = new_panel(moves_log_win);
    log_panels[2] = new_panel(eval_log_win);
    log_panels[3] = new_panel(warn_log_win);

    top_panel(main_panels[1]);

    setlocale(LC_ALL, "");

    mvwprintw(input_window, 1, 0, "> Type 'quit'/'Quit' to quit or 'reset'/'Reset' to reset the board\n>> ");

    bool running = true;
    while(running)
    {
        board.print_board(main_window);
        board.print_score(main_window);

        box(active_window, 0, 0);

        update_panels();
        doupdate();

        char res[6];
        if(!handle_input(res, board, false, running, input_window, warn_log_win)) continue;

        float x = getmaxx(warn_log_win);

        if(handle_output(board.move_piece(res, input_window, warn_log_win), warn_log_win))
        {
            // If the move was valid then check - If the opponent player got a check? If yes, then check if it's a checkmate
            if(board.is_checked(board.get_turn()))
            {
                if(board.is_checkmate(board.get_turn()))
                {
                    print_ascii(warn_log_win, 3, 2, mate_warn_ascii, 2);

                    mvwprintw(input_window, 1, 0, "Type 'quit'/'Quit' to quit, or type 'reset'/'Reset' to reset the board and play another game!");

                    board.print_board(main_window);
                    board.print_score(main_window);

                    update_panels();
                    doupdate();

                    while(handle_input(res, board, true, running, input_window, warn_log_win)) { }

                } else
                {
                    print_ascii(warn_log_win, 3, (x/100) * 21, check_warn_ascii, 3);
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
