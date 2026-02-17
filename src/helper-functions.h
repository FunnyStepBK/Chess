#ifndef helper_functionsH
#define helper_functionsH

#include <iostream>
#include "./board/board.h"
#include <ncurses.h>

using namespace std;

// A function to create a window
WINDOW* create_win(int height, int width, int starty, int startx);

// A function to delete a window
void delete_win(WINDOW* window);

// A function to handle all the input and perform actions accordingly
bool get_input(char res[], Board& board, bool game_over, bool& running, WINDOW* win);

// Guard - So we don't go out of bounds of our 8x8 board
bool out_of_bounds(int row, int col);

// Returns a list of valid moves for a given piece
void get_moves(Piece p, int file, int rank, vector<array<int, 2>>& moves_list, vector<vector<Square>> board);

// Embedd the ascii of a piece into a square's ascii
void embed_piece(string& piece_ascii, string& square_ascii);

#endif
