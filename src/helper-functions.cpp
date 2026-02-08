#include "helper-functions.h"

// Guard - So we don't go out of bounds of our 8x8 board
bool out_of_bounds(int row, int col)
{
    if((row < 0 || row > 7) || (col < 0 || col > 7))
    {
        return true;
    }

    return false;
}
