#ifndef boardH
#define boardH

#include <vector>
#include "../square/square.h"


class Board
{
public:
    // Static because these functions should be available through-out the whole scope of the programme AKA until the programme is stopped.
    static vector<vector<Square>> initialize_board();
    static void print_board(vector<vector<Square>>& board);
    static void reset_board(vector<vector<Square>>& board); // Reset the position of all pieces back to their starting square
    static bool move_piece(string move);
};

#endif
