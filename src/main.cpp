#include <iostream>
#include <vector>

#include "board/board.h"

using namespace std;

void get_input(string& square, string& target_square)
{
}

int main()
{
    Board board;
    board.print_board();

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
        } else if(move == "Reset" || move == "reset")
        {
            board.initialize_board();
        }

        if(!(move.size() == 4))
        {
            cout << "Please use valid square notations" << endl;
        }

        if(board.move_piece(move, board))
        {
            board.print_board();
        }
    }

    return 0;
}
