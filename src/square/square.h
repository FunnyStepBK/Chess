#ifndef squareH
#define squareH

#include <string>
#include <vector>

using namespace std;

class Piece
{
private:
    // Something to descirbe the different move-sets of each type of piece here

public:
    string piece;
    char color;

    // Constructors
    Piece()
    {
    }
    Piece(string new_piece, char new_color) : piece(new_piece), color(new_color)
    {
    }

    void very_path(); // A function to verify the path of a piece according to it's move set -- I am kinda leaning
    // towards recursion for this tho not sure about the params and how to give each piece it's unique move-set.

};

class Square
{
private:
    Piece piece;
    char color;

public:
    char rank;
    char file;
    bool is_empty;

    // Accessors
    Piece get_piece() { return piece; }
    char get_color() { return color; }

    // Mutators
    void set_piece(Piece new_piece) { piece = new_piece; }
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
