#include <ncurses.h>
#include <panel.h>
#include <array>
#include <vector>
#include <cstring>

#include "../src/board/board.hpp"
#include "./windows/windows.hpp"
#include "helper-functions.hpp"
#include "../src/board/pieces/move-sets/move-set.hpp"

vector<string> input_warn_ascii = {
    "dP                         dP                     dP                  dP   ",
    "88                         88                     88                  88   ",
    "88d888b. 88d888b. dP    dP 88d888b.    dP  dP  dP 88d888b. .d8888b. d8888P ",
    "88'  `88 88'  `88 88    88 88'  `88    88  88  88 88'  `88 88'  `88   88   ",
    "88.  .88 88       88.  .88 88    88    88.88b.88' 88    88 88.  .88   88   ",
    "88Y8888' dP       `88888P' dP    dP    8888P Y8P  dP    dP `88888P8   dP   "
};
vector<string> invalid_warn_ascii = {
    "dP                            dP oo       dP  dP ",
    "88                            88          88  88 ",
    "88 88d888b. dP   .dP .d8888b. 88 dP .d888b88  88 ",
    "88 88'  `88 88   d8' 88'  `88 88 88 88'  `88  dP ",
    "88 88    88 88 .88'  88.  .88 88 88 88.  .88     ",
    "dP dP    dP 8888P'   `88888P8 dP dP `88888P8  oo "
};

vector<string> empty_warn_ascii = {
    "88888888b                       dP             dP ",
    "88                              88             88 ",
    "888888    88d8b.d8b. 88d888b. d8888P dP    dP  88 ",
    "88        88'`88'`88 88'  `88   88   88    88  dP ",
    "88        88  88  88 88.  .88   88   88.  .88     ",
    "88888888P dP  dP  dP 88Y888P'   dP   `8888P88  oo ",
    "                     88                   .88     ",
    "                     dP               d8888P      "
};

vector<string> illegal_warn_ascii = {
    "oo dP dP                            dP                                         dP",
    "   88 88                            88                                         88",
    "dP 88 88 .d8888b. .d8888b. .d8888b. 88   88d8b.d8b. .d8888b. dP   .dP .d8888b. 88",
    "88 88 88 88ooood8 88'  `88 88'  `88 88   88'`88'`88 88'  `88 88   d8' 88ooood8 dP",
    "88 88 88 88.  ... 88.  .88 88.  .88 88   88  88  88 88.  .88 88 .88'  88.  ...   ",
    "dP dP dP `88888P' `8888P88 `88888P8 dP   dP  dP  dP `88888P' 8888P'   `88888P' oo",
    "                       .88                                                       ",
    "                   d8888P                                                        "
};


vector<string> check_warn_ascii = {
    " a88888b. dP                         dP       dP",
    "d8'   `88 88                         88       88",
    "88        88d888b. .d8888b. .d8888b. 88  .dP  88",
    "88        88'  `88 88ooood8 88'  `'' 88888'   dP",
    "Y8.   .88 88    88 88.  ... 88.  ... 88  `8b.   ",
    " Y88888P' dP    dP `88888P' `88888P' dP   `YP oo"
};

vector<string> mate_warn_ascii = {
    " a88888b. dP                         dP                             dP           ",
    "d8'   `88 88                         88                             88           ",
    "88        88d888b. .d8888b. .d8888b. 88  .dP  88d8b.d8b. .d8888b. d8888P .d8888b.",
    "88        88'  `88 88ooood8 88'  `'' 88888'   88'`88'`88 88'  `88   88   88ooood8",
    "Y8.   .88 88    88 88.  ... 88.  ... 88  `8b. 88  88  88 88.  .88   88   88.  ...",
    " Y88888P' dP    dP `88888P' `88888P' dP   `YP dP  dP  dP `88888P8   dP   `88888P'"
};

// A function to handle all the input and perform actions accordingly
bool handle_input(char res[], Board& board, bool game_over, bool& running, WINDOW* win, WINDOW* warn_log_win)
{
    echo();
    mvwgetnstr(win, 2, 3, res, 6);
    noecho();

    clear_and_box_win(warn_log_win);

    wmove(win, 2, 3);
    wclrtobot(win);

    string temp;
    for(size_t i = 0; i < strlen(res); i++)
    {
        temp += tolower(res[i]);
    }

    if(temp == "quit")
    {
        running = false;
        return false;
    }

    if(temp == "reset")
    {
        board = Board();
        board.initialize_board();
        return false;
    }

    if(game_over)
    {
        return true;
    }

    if(temp == "undo")
    {
        board.undo_move(warn_log_win);
        return false;
    }

    if(temp.size() != 4 && !game_over)
    {
        mvwprintw(warn_log_win, 1, 1, "> Invalid notation! Please use standard notations to move the pieces.");
    }

    return true;
}

// Guard - So we don't go out of bounds of our 8x8 board
bool out_of_bounds(int row, int col)
{
    if((row < 0 || row > 7) || (col < 0 || col > 7))
    {
        return true;
    }

    return false;
}

// Returns a list of valid moves for any given piece
void get_moves(Piece p, int file, int rank, vector<array<int, 2>>& moves_list, vector<vector<Square>> board)
{
    switch(p.type)
    {
        // 0 - If the piece is a pawn
        case 0: {
            int n = +1;
            if(p.color == 'W') n = -1;

            if(p.on_start) {
                MoveSet::travel_straight(board, rank + n, file, n, 0, 2, moves_list, p.color, false);
            } else
            {
                MoveSet::travel_straight(board, rank + n, file, 0, 0, 1, moves_list, p.color, false);
            }

            MoveSet::travel_diagonally(board, rank + n, file - 1, 0, 0, 1, moves_list, p.color, false);
            MoveSet::travel_diagonally(board, rank + n, file + 1, 0, 0, 1, moves_list, p.color, false);

            break;
        }

        // 1 - If the piece is a king
        case 1: {
            MoveSet::intercardinal_traversal(board, rank, file, 1, moves_list, p.color, false);
            MoveSet::cardinal_traversal(board, rank, file, 1, moves_list, p.color, false);
            break;
        }

        // 2 - If the piece is a knight
        case 2: {
            MoveSet::knight_move_set(board, rank, file, moves_list, p.color);
            break;
        }

        // 3 - If the piece is a bishop
        case 3: {
            MoveSet::intercardinal_traversal(board, rank, file, 8, moves_list, p.color, false);
            break;
        }

        // 4 - If the piece is a rook
        case 4: {
            MoveSet::cardinal_traversal(board, rank, file, 8, moves_list, p.color, false);
            break;
        }

        // 5 - If the piece is a queen
        case 5: {
            MoveSet::intercardinal_traversal(board, rank, file, 8, moves_list, p.color, false);
            MoveSet::cardinal_traversal(board, rank, file, 8, moves_list, p.color, false);
            break;
        }

        default:
            break;
    }
}

// A function to handle the output of different functions and print errors (if any) to the user accordingly
bool handle_output(int out_value, WINDOW* warn_log_win)
{
    float x = getmaxx(warn_log_win);
    float x_by_100 = x/100;

    switch(out_value)
    {

        // 0 : Invalid input
        case INVALID_INPUT: {
            print_ascii(warn_log_win, 3, 5, input_warn_ascii, 3);
            break;
        }

        // 1 : Invalid Move
        case INVALID_MOVE: {
            print_ascii(warn_log_win, 3, x_by_100 * 23, invalid_warn_ascii, 1);
            break;
        }

        // 2 : The chosen square dosen't have a piece
        case EMPTY_SQUARE: {
            print_ascii(warn_log_win, 2, x_by_100 * 23, empty_warn_ascii, 3);
            break;
        }

        // 3 : Illegal Move
        case ILLEGAL_MOVE: {
            print_ascii(warn_log_win, 3, 2, illegal_warn_ascii, 1);
            break;
        }

        // -1 : default : Valid move - nothing to print out to the screen
        case VALID_MOVE:
            [[fallthrough]];
        default: {
            return true;
        }

    }

    wrefresh(warn_log_win);

    return false;
}

// To print ascii text
void print_ascii(WINDOW* window, int y, int x, vector<string> ascii, int color_pair)
{
    wattron(window, COLOR_PAIR(color_pair));
    for(int i = 0; i < ascii.size(); i++)
    {
        mvwprintw(window, y + i, x, "%s", ascii[i].c_str());
    }
    wattroff(window, COLOR_PAIR(color_pair));

}

// To print out normal text logs/messages to the user
void print_ascii(WINDOW* window, int y, int x, string message, int color_pair)
{
    wattron(window, COLOR_PAIR(color_pair));
    mvwprintw(window, y, x, "%s", message.c_str());
    wattroff(window, COLOR_PAIR(color_pair));
}
