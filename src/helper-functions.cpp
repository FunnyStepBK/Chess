#include <array>
#include <vector>

#include "helper-functions.h"
#include "../src/board/pieces/move-sets/move-set.h"
#include "../src/board/board.h"

// A function to handle all the input and perform actions accordingly
bool get_input(string& move, Board& board, bool game_over, bool& running)
{
    if(!game_over)
    {
        cout << "(" << board.get_turn() << ")" << ">> ";
    } else
    {
        cout << ">> ";
    }

    cin >> move;

    if(move == "Quit" || move == "quit")
    {
        running = false;
        return false;
    }

    if(move == "Reset" || move == "reset")
    {
        board = Board();
        board.print_board();
        return false;
    }

    if(move == "undo" || move == "Undo")
    {
        board.undo_move();
        board.print_board();
        return false;
    }

    if(!(move.size() == 4) && !game_over)
    {
        cout << "Please use valid square notations!" << endl;
        return false;
    }

    if(game_over)
    {
        cout << "\033[033m> Please choose a valid option.\033[0m" << endl;
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

            int temp_rank;
            int temp_file;
            int counter = 0;

            for(array<int, 2> a : moves_list)
            {
                temp_rank = a[0];
                temp_file = a[1];


                if(temp_file != file && !board[temp_rank][temp_file].has_piece())
                {
                    moves_list.erase(moves_list.begin() + counter);
                }

                counter++;
            }

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
