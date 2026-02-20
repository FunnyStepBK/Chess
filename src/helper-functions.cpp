#include <ncurses.h>
#include <array>
#include <cstring>
#include <vector>

#include "helper-functions.h"
#include "../src/board/pieces/move-sets/move-set.h"
#include "../src/board/board.h"

// A function to handle all the input and perform actions accordingly
bool handle_input(char res[], Board& board, bool game_over, bool& running, WINDOW* win, WINDOW* log_win)
{
    echo();
    mvwgetnstr(win, 2, 3, res, 6);
    noecho();

    wclear(log_win);
    box(log_win, 0, 0);

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
        board.undo_move(log_win);
        return false;
    }

    if(temp.size() != 4 && !game_over)
    {
        mvwprintw(log_win, 1, 1, "> Invalid notation! Please use standard notations to move the pieces.");
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
