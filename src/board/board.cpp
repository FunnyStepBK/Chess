#include <iostream>
#include <vector>

#include "board.h"
#include "../square/square.h"

using namespace std;

void Board::initialize_board()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(j % 2 == 0 && i % 2 == 0)
            {
                board[i][j].set_color('W');
            } else if(j % 2 != 0 && i % 2 == 0)
            {
                board[i][j].set_color('B');
            } else if (j % 2 == 0 && i % 2 != 0)
            {
                board[i][j].set_color('B');
            } else
            {
                board[i][j].set_color('W');
            }
        }
    }

    Piece b_pawn = Piece("BP", 'B');
    for (Square& s : board[1])
    {
        s.is_empty = false;
        s.set_piece(b_pawn);
    }

    Piece w_pawn = Piece("WP", 'W');
    for (Square& s : board[6])
    {
        s.is_empty = false;
        s.set_piece(w_pawn);
    }

    Piece b_rook = Piece("BR", 'B');
    Piece b_knight = Piece("BK", 'B');
    Piece b_bishop = Piece("BB", 'B');
    Piece b_queen = Piece("BQ", 'B');
    Piece b_king = Piece("BKG", 'B');

    Piece w_rook = Piece("WR", 'B');
    Piece w_knight = Piece("WK", 'B');
    Piece w_bishop = Piece("WB", 'B');
    Piece w_queen = Piece("WQ", 'B');
    Piece w_king = Piece("WKG", 'B');


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

void Board::check_squares(int file, int rank, int target_file, int target_rank)
{

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
                cout << s.get_piece().piece << " ";
            }
        }
        cout << endl;
    }

}

bool Board::move_piece(string move)
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

    Board::check_squares(file, rank, target_file, target_rank);

    Piece temp = (board[rank][file].get_piece());
    board[rank][file].set_piece(board[target_rank][target_file].get_piece(), true);
    board[target_rank][target_file].set_piece(temp, false);

    cout << temp.piece << " - " << temp.color << endl;

    return true;
}
