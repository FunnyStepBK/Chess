#ifndef BOARD_H
#define BOARD_H

#define VALID_MOVE -1
#define INVALID_INPUT 0
#define INVALID_MOVE 1
#define EMPTY_SQUARE 2
#define ILLEGAL_MOVE 3

#include <string>
#include <vector>
#include <array>
#include <deque>
#include <ncurses.h>

#include "./square/square.hpp"

struct Position {
    int row;
    int col;
};

class Board
{
private:
    Position WKing_square;
    Position BKing_square;
    char turn;

    // Format for the moves_buffer : {int file, int rank, int target_file, int target_rank, int move_type}
    // ALl the currently defined move types
    // 0 - regular move
    // 1 - A piece captured another piece
    // 2 - en-passant move
    // 3 - Pawn promotion
    // 4 - Pawn promotion by capturing a piece
    // 5 - castling
    deque<array<int, 5>> moves_buffer;

    // A vector to store all the pieces that get captured
    vector<Piece> captured_pieces;

public:
    vector<vector<Square>> board;
    // Ints to store the sum of all the pieces captured by a side (black/white)
    int white_score;
    int black_score;

    // A vector to store all the moves and display them in the moves_log_win
    vector<string> moves;

    vector<string> black_sqaure_ascii = {
        "###############",
        "###############",
        "###############",
        "###############",
        "###############",
        "###############",
        "###############"
    };

    vector<string> white_sqaure_ascii = {
        "               ",
        "               ",
        "               ",
        "               ",
        "               ",
        "               ",
        "               "
    };

    void initialize_board(); // Adds all the pieces to their appropriate starting squares can also be used to reset the position of
    // all pieces back to their starting square

    void print_board(WINDOW* window);
    void print_score(WINDOW* window);
    void print_moves_to_screen(WINDOW* window);

    // Funcitons related to the whole piece movement functionality
    int valid_move(Piece p, int file, int rank, int target_file, int target_rank);
    int valid_move(Piece p, int file, int rank, int target_file, int target_rank, bool& is_castle);
    int move_piece(char move[], WINDOW* input_window, WINDOW* warn_log_win);

    // Funcitons related to undo-redo stuff
    void undo_move(WINDOW* warn_log_win);
    void undo_capture(Square& current_square, Square& initial_square, Piece capturing_piece);

    // A function that will prompt a player and get thier response when a pawn reaches it's promotion rank
    int prompt_promotion(WINDOW* input_window, WINDOW* warn_log_win);

    // Fucntion related to mechaincs/game-rules surrounding the King
    bool is_king_safe(Piece piece, int file, int rank, int target_file, int target_rank);
    bool is_checked(char color);
    bool is_checkmate(char color);

    // Functions related to castling
    bool validate_and_castle(int file, int rank, int target_file, int target_rank, WINDOW* warn_log_win);
    bool castle_if_safe(int king_file, int rook_file, int back_rank, Square& king_square, Square& rook_square);

    // Increments the score of the provided piece's side
    void increment_score(Piece piece);

    // Decrements the score of the provided piece's side
    void decrement_score(Piece piece);

    // Adds the latest move to the moves buffer and removes the oldest
    void update_moves_buffer(int file, int rank, int target_file, int target_rank, int move_type);


    // Static functions

        // A function to save extra lines of code
        static void convert_to_pawn(Piece& piece);

        // Clear the curr_square and set the provided piece on the target_square
        static void move_to_square(Square& curr_square, Square& target_square, Piece piece);

    // -- X


    // accessors
    Position get_wk_position() { return WKing_square; }
    Position get_bk_position() { return BKing_square; }
    char get_turn() { return turn; }

    // mutators
    void update_wk_position(Position new_position) { WKing_square = new_position; }
    void update_bk_position(Position new_position) { BKing_square = new_position; }
    void update_turn()
    {
        turn = turn == 'W' ? 'B' : 'W';
    }


    // Constructors
    Board() : turn('W'), board(8, vector<Square>(8, Square(true))), white_score(0), black_score(0)
    {
        initialize_board();

        WKing_square.row = 7;
        WKing_square.col = 4;

        BKing_square.row = 0;
        BKing_square.col = 4;
    }

};

#endif
