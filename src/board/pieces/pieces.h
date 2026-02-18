#ifndef pieceH
#define pieceH

#include <vector>
#include <string>
#include <optional>
#include <array>

using namespace std;

class Piece
{
private:
    // optional<bool> is_checked;

public:
    vector<string> ascii_white;
    vector<string> ascii_black;
    char color;
    int type;
    bool on_start;

// Constructors
    Piece()
    {
    }

    Piece(vector<string> new_white_ascii, vector<string> new_black_ascii, char new_color, int _type) : ascii_white(new_white_ascii),
        ascii_black(new_black_ascii), color(new_color), type(_type)
    {

    }
    Piece(vector<string> new_white_ascii, vector<string> new_black_ascii, char new_color, int _type, bool _on_start) : ascii_white(new_white_ascii),
        ascii_black(new_black_ascii), color(new_color), type(_type), on_start(_on_start)
    {
    }
};

#endif
