#ifndef boardH
#define boardH

#include <vector>
#include "../square/square.h"


class Board
{
private:
    vector<vector<Square>> board;

public:
    void initialize_board(); // Adds all the pieces to their appropriate starting squares can also be used to reset the position of
    // all pieces back to their starting square
    void clear_board();

    void check_squares(int file, int rank, int target_file, int target_rank);
    bool move_piece(string move);

    void print_board();

    // Constructors
    Board() : board(8, vector<Square>(8, Square(true)))
    {
        Board::initialize_board();
    }

};

#endif
