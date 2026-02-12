#ifndef helper_functionsH
#define helper_functionsH

#include <iostream>
#include "./board/board.h"

using namespace std;

// Guard - So we don't go out of bounds of our 8x8 board
bool out_of_bounds(int row, int col);

// Returns a list of valid moves for a given piece
void get_moves(Piece p, int file, int rank, vector<array<int, 2>>& moves_list, vector<vector<Square>> board);

#endif
