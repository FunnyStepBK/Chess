#ifndef HELPER_FUNCITONS_H
#define HELPER_FUNCITONS_H

#include "./board/board.h"
#include <ncurses.h>

using namespace std;

// A function to handle all the input and perform actions accordingly
bool handle_input(char res[], Board& board, bool game_over, bool& running, WINDOW* win, WINDOW* log_win);

// Guard - So we don't go out of bounds of our 8x8 board
bool out_of_bounds(int row, int col);

// Returns a list of valid moves for a given piece
void get_moves(Piece p, int file, int rank, vector<array<int, 2>>& moves_list, vector<vector<Square>> board);

#endif
