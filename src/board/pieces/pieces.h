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
    bool on_start;


    // mutators

    // accessors

    // Constructors
    Piece()
    {
    }
    Piece(string new_piece, char new_color)
    {
        Piece(new_piece, new_color, -1);
    }
    Piece(string new_piece, char new_color, int _type) : name(new_piece), color(new_color), type(_type)
    {
    }
    Piece(string new_piece, char new_color, int _type, bool _on_start) : name(new_piece), color(new_color), type(_type), on_start(_on_start)
    {
    }
};

#endif
