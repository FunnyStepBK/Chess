#ifndef boardH
#define boardH

#include <string>
#include <vector>
#include <array>

#include "../square/square.h"

class Board
{
private:
    vector<vector<Square>> board;
    array<int, 2> WKing_square;
    array<int, 2> BKing_square;
    char turn;

public:
    void initialize_board(); // Adds all the pieces to their appropriate starting squares can also be used to reset the position of
    // all pieces back to their starting square

    void print_board();

    bool valid_move(Piece p, int file, int rank, int target_file, int target_rank);
    bool move_piece(string move, Board& b);

    bool is_checked(char color);

    // accessors
    array<int, 2> get_wk_position() { return WKing_square; }
    array<int, 2> get_bk_position() { return BKing_square; }
    char get_turn() { return turn; }

    // mutators
    void update_wk_position(array<int, 2> _position) { WKing_square = _position; }
    void update_bk_position(array<int, 2> _position) { BKing_square = _position; }
    void update_turn(char _turn) { turn = _turn; }

    // Constructors
    Board() : board(8, vector<Square>(8, Square(true))), turn('W')
    {
        initialize_board();

        WKing_square[0] = 7;
        WKing_square[1] = 4;

        BKing_square[0] = 0;
        BKing_square[1] = 4;
    }

};

#endif
