#ifndef squareH
#define squareH

#include <string>
#include <vector>
#include <optional>

#include "../board/pieces/pieces.h"

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

    // Mutators
    void set_piece(Piece new_piece) { piece = new_piece; }
    void set_piece(Piece new_piece, bool empty_flag) {
        piece = new_piece;
        is_empty = empty_flag;
    }
    void set_color(char value) { color = value; }

    bool has_piece()
    {
        if(is_empty) return false;

        return true;
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
