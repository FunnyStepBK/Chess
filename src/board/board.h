#ifndef boardH
#define boardH

#include <vector>
#include <array>

#include "../square/square.h"

class Board
{
private:
    vector<vector<Square>> board;

public:
    void initialize_board(); // Adds all the pieces to their appropriate starting squares can also be used to reset the position of
    // all pieces back to their starting square

    bool move_piece(string move, Board& b);

    void print_board();

    // Static functions
    bool valid_move(Piece p, int file, int rank, int target_file, int target_rank);

    // Constructors
    Board() : board(8, vector<Square>(8, Square(true)))
    {
        Board::initialize_board();
    }

};

#endif
