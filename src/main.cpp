#include <iostream>

#include "board/board.h"
#include "./helper-functions.h"

using namespace std;

int main()
{
    Board board;
    board.print_board();

    string move;
    bool running = true;

    cout << "Type 'quit' or 'Quit' to exit" << endl;
    while(running)
    {
        if(!get_input(move, board, false, running)) { continue; }

        if(board.move_piece(move)) {
            if(board.is_checked(board.get_turn()))
            {
                if(board.is_checkmate(board.get_turn()))
                {
                    cout << "\033[034m>> Checkmate! Game over.\033[0m" << endl;
                    board.print_board();

                    cout << "\033[033m> Type 'quit'/'Quit' to quit, or type 'reset'/'Reset' to reset the board to play another game!\033[0m" << endl;
                    while(get_input(move, board, true, running)) {}
                    continue;

                } else
                {
                    cout << "\033[037mCheck!\033[0m" << endl;
                }
            }

            board.print_board();
        }
    }

    return 0;
}
