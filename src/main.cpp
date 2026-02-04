#include <iostream>
#include <vector>

#include "board/board.h"
#include "square/square.h"

using namespace std;

void get_input(string& square, string& target_square)
{
}

int main()
{
    vector<vector<Square>> board = Board::initialize_board();
    Board::reset_board(board);
    Board::print_board(board);

    bool running = true;

    string move;

    cout << "Type 'quit' or 'Quit' to exit" << endl;
    while(running)
    {
        cout << ">> ";
        cin >> move;
        if(move == "Quit" || move == "quit")
        {
            break;
        }

        if(!(move.size() == 4))
        {
            cout << "Please use valid square notations" << endl;
        }

        if(Board::move_piece(move))
        {
            Board::print_board(board);
        }
    }

    return 0;
}
