#include <iostream>

#include "board/board.h"

using namespace std;

void get_input(string& square, string& target_square)
{
}

int main()
{
    Board board;
    board.print_board();

    string move;

    cout << "Type 'quit' or 'Quit' to exit" << endl;
    while(true)
    {
        cout << ">> ";
        cin >> move;
        if(move == "Quit" || move == "quit")
        {
            break;
        } else if(move == "Reset" || move == "reset")
        {
            board.initialize_board();
        }

        if(!(move.size() == 4))
        {
            cout << "Please use valid square notations" << endl;
            continue;
        }

        if(board.move_piece(move, board))
        {
            board.print_board();
        }
    }

    return 0;
}
