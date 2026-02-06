#include <iostream>
#include <vector>
#include <string>
#include <array>

#include "board.h"
#include "../square/square.h"
#include "./pieces/move-sets/move-set.h"

using namespace std;

void Board::initialize_board()
{
    for(int i = 0, step = 0; i < 8; i++, step++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(step % 2 == 0)
            {
                board[i][j].set_color('W');
            } else
            {
                board[i][j].set_color('B');
            }

            step++;
        }
    }

    Piece b_pawn = Piece("BP", 'B');
    // b_pawn.on_start = true;

    Piece w_pawn = Piece("WP", 'W');
    // w_pawn.on_start = true;

    // for(int i = 0; i < 8; i++)
    // {
    //     // b_pawn.start_square = {0, i};
    //     board[1][i].is_empty = false;
    //     board[1][i].set_piece(b_pawn);
    //
    //     // w_pawn.start_square = {6, i};
    //     board[6][i].is_empty = false;
    //     board[6][i].set_piece(w_pawn);
    // }

    Piece b_rook = Piece("BR", 'B');
    Piece b_knight = Piece("BK", 'B');
    Piece b_bishop = Piece("BB", 'B');
    Piece b_queen = Piece("BQ", 'B');
    Piece b_king = Piece("BKG", 'B', 1);

    Piece w_rook = Piece("WR", 'W');
    Piece w_knight = Piece("WK", 'W');
    Piece w_bishop = Piece("WB", 'W');
    Piece w_queen = Piece("WQ", 'W');
    Piece w_king = Piece("WKG", 'W', 1);


    // Setting up all the pieces by directly indexing - Don't think this is a good practice but can't really come up with another solution for this

    // Black major pieces --
        // Black Rooks
        board[0][0].set_piece(b_rook);
        board[0][7].set_piece(b_rook);

        // Black Knights
        board[0][1].set_piece(b_knight);
        board[0][6].set_piece(b_knight);

        // Black Bishops
        board[0][2].set_piece(b_bishop);
        board[0][5].set_piece(b_bishop);

        // Black Queen
        board[0][3].set_piece(b_queen);

        // Black King
        board[0][4].set_piece(b_king);
    // --X

    // White major pieces --
        // White Rooks
        board[7][0].set_piece(w_rook);
        board[7][7].set_piece(w_rook);

        // White Knights
        board[7][1].set_piece(w_knight);
        board[7][6].set_piece(w_knight);

        // White Bishops
        board[7][2].set_piece(w_bishop);
        board[7][5].set_piece(w_bishop);

        // White Queen
        board[7][3].set_piece(w_queen);

        // White King
        board[7][4].set_piece(w_king);
    // --X

    // Set the squares that are now occupied by pieces to non-empty

    for(Square& s : board[0])
    {
        s.is_empty = false;
    }

    for(Square& s : board[7])
    {
        s.is_empty = false;
    }
}

void Board::print_board()
{
    for(int i = 0; i < 8; i++)
    {
        for(Square& s : board[i])
        {
            if(s.is_empty)
            {
                if(s.get_color() == 'B')
                {
                    cout << "## ";
                } else {
                    cout << "OO ";
                }
            } else {
                cout << s.get_piece().name << " ";
            }
        }
        cout << endl;
    }

}

bool Board::valid_move(Piece p, int file, int rank, int target_file, int target_rank)
{
    vector<array<int, 2>> moves_list;

    switch(p.type)
    {
        case 1: // 1 - If the piece is a king
            MoveSet::intercardinal_traversal(board, rank, file, 1, moves_list, p.color);
            MoveSet::cardinal_traversal(board, rank, file, 1, moves_list, p.color);
            break;
        default:
            return false;
    }

    for(array<int, 2> c : moves_list)
    {
        if(c[0] == target_rank && c[1] == target_file) return true;
    }

    return false;
}

bool Board::move_piece(string move, Board& b)
{
    int file = static_cast<int>(move[0]) - 97;
    int rank = 56 - static_cast<int>(move[1]);

    int target_file = static_cast<int>(move[2]) - 97;
    int target_rank = 56 - static_cast<int>(move[3]);

    if ((file < 0 || file > 7) || (rank < 0 || rank > 7) || (target_file < 0 || target_file > 7) || (target_rank < 0 || target_rank > 7))
    {
        cout << "Invalid move! Please use standard notations to move the pieces" << endl;
        return false;
    }

    Square curr_square = board[rank][file];
    Square target_square = board[target_rank][target_file];

    Piece temp;

    if(!curr_square.has_piece())
    {
        cout << "\033[33m=> \033[0m" << move.substr(0, 2) << "\033[33m is an empty square!\033[0m\n" << endl;
        print_board();
        return false;
    }

    temp = (board[rank][file].get_piece());

    if(!valid_move(temp, file, rank, target_file, target_rank))
    {
        cout << "\033[31mInvalid Move!\033[0m" << endl;
        return false;
    }

    if(curr_square.has_piece() && !(target_square.has_piece()))
    {
        board[rank][file].set_piece(board[target_rank][target_file].get_piece(), true);
        board[target_rank][target_file].set_piece(temp, false);

        return true;
    }

    board[rank][file].set_piece(board[target_rank][target_file].get_piece(), false);
    board[target_rank][target_file].set_piece(temp, false);

    cout << temp.name << " - " << temp.color << endl;

    return true;
}
