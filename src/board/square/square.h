#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include <string>
#include <vector>
#include <optional>

#include "../pieces/pieces.h"

using namespace std;


class Square
{
private:
    Piece piece;
    char color;

public:
    bool is_empty;

    // Accessors
    Piece get_piece() { return piece; }
    char get_color() { return color; }
    void clear_square() // Removes the piece from the square, hermm i can overload this function to make a capture piece function
    // don't think that will be needed tho -- no idea tbh
    {
        is_empty = true;
        piece = Piece();
    }

    // Mutators
    void set_piece(Piece new_piece) { piece = new_piece; }
    void set_piece(Piece new_piece, bool empty_flag) {
        piece = new_piece;
        is_empty = empty_flag;
    }
    void set_color(char value) { color = value; }
    bool has_piece();
    void update_position(bool value) {
        piece.on_start = value;
    }

    // Static functions -- No idea right now if I am even gonna have any in this class

    // Constructors
    Square()
    {
    }
    Square(bool is_empty_) : is_empty(is_empty_)
    {
    }
};

#endif
