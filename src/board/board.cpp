#include <iostream>
#include <vector>

#include "board.h"
#include "../square/square.h"

using namespace std;

vector<vector<Square>> Board::initialize_board()
{
    vector<vector<Square>> board(8, vector<Square>(8, Square(true)));

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

    return board;
}

void Board::print_board(vector<vector<Square>>& board)
{
    for(int i = 0; i < 8; i++)
    {
        for(Square& s : board[i])
        {
            cout << s.get_color() << " "; // Just for testing right now - Will remove later after making sure all the functions are working fine
        }
        cout << endl;
    }

}
