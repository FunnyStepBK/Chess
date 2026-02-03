#include <iostream>
#include <vector>

#include "board/board.h"
#include "square/square.h"

using namespace std;

int main()
{
    vector<vector<Square>> board = Board::initialize_board();
    Board::print_board(board);

    return 0;
}
