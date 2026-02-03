#ifndef chessH
#define chessH

#include <string>
#include <vector>

using namespace std;

class Piece
{
private:
    string piece;
    char color;

public:

    // Accessors
    string get_piece();
    char get_color();

    // Mutators
    void edit_piece(string new_piece);
    void edit_color(char new_color);

    // Static functions - cuz I want to associate these functions with this class, mhm mhm

    // Constructors
    Piece()
    {
    }
};

#endif
