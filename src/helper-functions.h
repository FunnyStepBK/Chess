#ifndef helper_functionsH
#define helper_functionsH

#include <iostream>
#include "./board/board.h"

using namespace std;

// Guard - So we don't go out of bounds of our 8x8 board
bool out_of_bounds(int row, int col);

#endif
