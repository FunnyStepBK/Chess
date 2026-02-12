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
        cout << "(" << board.get_turn() << ")" << ">> ";
        cin >> move;
        if(move == "Quit" || move == "quit")
        {
            break;
        } else if(move == "Reset" || move == "reset")
        {
            board = Board();
            board.print_board();
            continue;
        }

        if(!(move.size() == 4))
        {
            cout << "Please use valid square notations" << endl;
            continue;
        }


        if(board.move_piece(move, board))
        {
            if(board.is_checked(board.get_turn()))
            {
                if(board.is_checkmate(board.get_turn()))
                {
                    cout << "Checkmate!" << endl;
                    board.print_board();

                    cout << "Game over." << endl << "Type 'quit'/'Quit' to quit, or type 'reset'/'Reset' to reset the board to play another game!" << endl;

                    while(true)
                    {
                        cout << ">> ";
                        cin >> move;
                        if(move == "Quit" || move == "quit")
                        {
                            return 0;
                        } else if(move == "Reset" || move == "reset")
                        {
                            board = Board();
                            break;
                        } else
                        {
                            cout << "\033[033mPlease choose a valid option.\033[0m" << endl;
                            continue;
                        }
                    }
                } else
                {
                    cout << "Check!" << endl;
                }
            }

            board.print_board();
        }
    }

    return 0;
}
