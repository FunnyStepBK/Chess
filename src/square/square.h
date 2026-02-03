#ifndef squareH
#define squareH

#include <string>
#include <vector>

using namespace std;

class Piece
{
public:
    string piece;
    char piece_color;
};

class Square
{
private:
    Piece piece;
    char color;
    bool is_empty;

public:

    // Accessors
    Piece get_piece() { return piece; }
    char get_color() { return color; }

    // Mutators
    void edit_piece(Piece new_piece) { piece = new_piece; }
    void change_empty_flag(bool value) { is_empty = value; }
    void set_color(char value) { color = value; }

    void move_piece();

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
