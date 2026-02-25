#ifndef HELPER_FUNCITONS_H
#define HELPER_FUNCITONS_H

#include <string>
#include <vector>

using namespace std;

// A function to handle all the input and perform actions accordingly
bool handle_input(char res[], Board& board, bool game_over, bool& running, WINDOW* win, WINDOW* log_win);

// Guard - So we don't go out of bounds of our 8x8 board
bool out_of_bounds(int row, int col);

// Returns a list of valid moves for a given piece
void get_moves(Piece p, int file, int rank, vector<array<int, 2>>& moves_list, vector<vector<Square>> board);

// A function to handle the output of different functions and print errors or log statements (if any) to the user accordingly, So if the case is:
// 0 : Invalid input
// 1 : Invalid move
// 2 : The chosen square dosen't have a piece
// 3 : Illegal move
// -1 : default : Valid move - nothing to print out to the screen
bool handle_output(int out_value, WINDOW* warn_log_win);

// Functions to print ascii text and normal logs/message

    // To print ascii text
    void print_ascii(WINDOW* window, int y, int x, vector<string> ascii, int color_pair);

    // Overloaded function to print message
    void print_ascii(WINDOW* window, int y, int x, string message, int color_pair);

// -- X

// Data-structures to store ascii text
extern vector<string> input_warn_ascii;
extern vector<string> invalid_warn_ascii;
extern vector<string> empty_warn_ascii;
extern vector<string> illegal_warn_ascii;
extern vector<string> check_warn_ascii;
extern vector<string> mate_warn_ascii;

#endif
