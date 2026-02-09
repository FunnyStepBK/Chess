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
    array<int, 2> whiteK_position;
    array<int, 2> blackK_position;
    char turn;

public:
    void initialize_board(); // Adds all the pieces to their appropriate starting squares can also be used to reset the position of
    // all pieces back to their starting square

    void print_board();

    bool valid_move(Piece p, int file, int rank, int target_file, int target_rank);
    bool move_piece(string move, Board& b);
    bool is_king_attacked(array<int, 2> arr);

    // accessors
    array<int, 2> get_wk_position() { return whiteK_position; }
    array<int, 2> get_bk_position() { return blackK_position; }
    char get_turn() { return turn; }

    // mutators
    void update_wk_position(array<int, 2> _position) { whiteK_position = _position; }
    void update_bk_position(array<int, 2> _position) { blackK_position = _position; }
    void update_turn(char _turn) { turn = _turn; }

    // Constructors
    Board() : board(8, vector<Square>(8, Square(true))), turn('W')
    {
        initialize_board();

        whiteK_position[0] = 7;
        whiteK_position[1] = 4;

        blackK_position[0] = 0;
        blackK_position[1] = 4;
    }

};

#endif
