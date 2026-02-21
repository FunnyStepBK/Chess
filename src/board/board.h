#ifndef BOARD_H
#define BOARD_H

#include <ncurses.h>
#include <string>
#include <vector>
#include <array>
#include <deque>

#include "./square/square.h"

class Board
{
private:
    vector<vector<Square>> board;
    array<int, 2> WKing_square;
    array<int, 2> BKing_square;
    char turn;

    // Format for the moves_buffer : {int file, int rank, int target_file, int target_rank, int move_type}
    // 0 - regular move
    // 1 - A piece captured another piece
    // 2 - en-passant move
    // 3 - Pawn promotion
    // 4 - Pawn promotion by capturing a piece
    // 5 - castling
    deque<array<int, 5>> moves_buffer;

    vector<Piece> captured_pieces;

public:
    // Ints to store the sum of all the pieces captured by a side (black/white)
    int white_score;
    int black_score;

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

    vector<string> check_warn_ascii = {
        " a88888b. dP                         dP       dP",
        "d8'   `88 88                         88       88",
        "88        88d888b. .d8888b. .d8888b. 88  .dP  88",
        "88        88'  `88 88ooood8 88'  `'' 88888'   dP",
        "Y8.   .88 88    88 88.  ... 88.  ... 88  `8b.   ",
        " Y88888P' dP    dP `88888P' `88888P' dP   `YP oo"
    };

    vector<string> mate_warn_ascii = {
        " a88888b. dP                         dP                             dP           ",
        "d8'   `88 88                         88                             88           ",
        "88        88d888b. .d8888b. .d8888b. 88  .dP  88d8b.d8b. .d8888b. d8888P .d8888b.",
        "88        88'  `88 88ooood8 88'  `'' 88888'   88'`88'`88 88'  `88   88   88ooood8",
        "Y8.   .88 88    88 88.  ... 88.  ... 88  `8b. 88  88  88 88.  .88   88   88.  ...",
        " Y88888P' dP    dP `88888P' `88888P' dP   `YP dP  dP  dP `88888P8   dP   `88888P'"
    };

    vector<string> illegal_warn_ascii = {
        "oo dP dP                            dP                                         dP",
        "   88 88                            88                                         88",
        "dP 88 88 .d8888b. .d8888b. .d8888b. 88   88d8b.d8b. .d8888b. dP   .dP .d8888b. 88",
        "88 88 88 88ooood8 88'  `88 88'  `88 88   88'`88'`88 88'  `88 88   d8' 88ooood8 dP",
        "88 88 88 88.  ... 88.  .88 88.  .88 88   88  88  88 88.  .88 88 .88'  88.  ...   ",
        "dP dP dP `88888P' `8888P88 `88888P8 dP   dP  dP  dP `88888P' 8888P'   `88888P' oo",
        "                       .88                                                       ",
        "                   d8888P                                                        "
    };

    vector<string> invalid_warn_ascii = {
        "dP                            dP oo       dP  dP ",
        "88                            88          88  88 ",
        "88 88d888b. dP   .dP .d8888b. 88 dP .d888b88  88 ",
        "88 88'  `88 88   d8' 88'  `88 88 88 88'  `88  dP ",
        "88 88    88 88 .88'  88.  .88 88 88 88.  .88     ",
        "dP dP    dP 8888P'   `88888P8 dP dP `88888P8  oo "
    };

    void initialize_board(); // Adds all the pieces to their appropriate starting squares can also be used to reset the position of
    // all pieces back to their starting square

    void print_board(WINDOW* window);
    void print_score(WINDOW* window);

    // Funcitons related to the whole piece movement functionality
    bool valid_move(Piece p, int file, int rank, int target_file, int target_rank);
    bool move_piece(char move[], WINDOW* input_window, WINDOW* warn_log_win);

    // Funcitons related to undo-redo stuff
    int undo_move(WINDOW* warn_log_win);
    void undo_capture(Square& current_square, Square& initial_square, Piece capturing_piece);

    // A function that will prompt a player and get thier res when a pawn reaches it's promotion rank
    int prompt_promotion(WINDOW* input_window, WINDOW* warn_log_win);

    // Fucntion related to mechaincs/game-rules surrounding the King
    bool is_king_safe(Piece piece, int file, int rank, int target_file, int target_rank);
    bool is_checked(char color);
    bool is_checkmate(char color);

    // Increments the score of the provided piece's side
    void increment_score(Piece piece);

    // Decrements the score of the provided piece's side
    void decrement_score(Piece piece);


    // Static functions

        // A function to save extra lines of code
        static void convert_to_pawn(Piece& piece);

        // Clear the curr_square and set the provided piece on the target_square
        static void move_to_square(Square& curr_square, Square& target_square, Piece piece);

    // -- X


    // accessors
    array<int, 2> get_wk_position() { return WKing_square; }
    array<int, 2> get_bk_position() { return BKing_square; }
    char get_turn() { return turn; }

    // mutators
    void update_wk_position(array<int, 2> _position) { WKing_square = _position; }
    void update_bk_position(array<int, 2> _position) { BKing_square = _position; }
    void update_turn(char _turn) { turn = _turn; }

    // Constructors
    Board() : board(8, vector<Square>(8, Square(true))), turn('W'), white_score(0), black_score(0)
    {
        initialize_board();

        WKing_square[0] = 7;
        WKing_square[1] = 4;

        BKing_square[0] = 0;
        BKing_square[1] = 4;
    }

};

#endif
