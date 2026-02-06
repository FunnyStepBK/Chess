#ifndef pieceH
#define pieceH

#include <string>
#include <optional>
#include <array>

using namespace std;

class Piece
{
private:
    // optional<bool> is_checked;

public:
    string name;
    char color;
    int type;

    // Optionals for pawns
    // optional<bool> on_start;
    // optional<array<int, 2>> start_square;

    // mutators

    // accessors

    // Constructors
    Piece()
    {
    }
    Piece(string new_piece, char new_color) : name(new_piece), color(new_color)
    {
    }
    Piece(string new_piece, char new_color, int _type) : name(new_piece), color(new_color), type(_type)
    {
    }
};

#endif
