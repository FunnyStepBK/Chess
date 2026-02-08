#include <vector>
#include <array>

#include "move-set.h"
#include "../../../helper-functions.h"

using namespace std;

void identify_opponent(vector<vector<Square>> v, int row, int col, char color, vector<array<int, 2>>& moves_list)
{
    // If it encounters a piece with a different color
    if(v[row][col].get_piece().color != color)
    {
        moves_list.push_back({row, col});
        return;
    }

    // Does nothing if the piece is of the same color
}

void MoveSet::travel_diagonally(vector<vector<Square>> v, int row, int col, int _row, int _col, int fuel, vector<array<int, 2>>& moves_list, char color, bool avoid_pieces)
{
    if(fuel == 0) return;

    if(out_of_bounds(row, col)) return;

    if(v[row][col].has_piece() && !avoid_pieces)
    {
        identify_opponent(v, row, col, color, moves_list);
        return;
    }

    moves_list.push_back({row, col});
    fuel--;

    travel_diagonally(v, row + _row, col + _col, _row, _col, fuel, moves_list, color, avoid_pieces);
}

void MoveSet::intercardinal_traversal(vector<vector<Square>> vec, int row, int col, int fuel, vector<array<int, 2>>& moves_list, char color, bool avoid_pieces)
{
    if(fuel == 0) return;

    travel_diagonally(vec, row - 1, col + 1, -1, +1, fuel, moves_list, color, avoid_pieces);
    travel_diagonally(vec, row + 1, col + 1, +1, +1, fuel, moves_list, color, avoid_pieces);
    travel_diagonally(vec, row + 1, col - 1, +1, -1, fuel, moves_list, color, avoid_pieces);
    travel_diagonally(vec, row - 1, col - 1, -1, -1, fuel, moves_list, color, avoid_pieces);
}

void MoveSet::travel_straight(vector<vector<Square>> v, int row, int col, int _row, int _col, int fuel, vector<array<int, 2>>& moves_list, char color, bool avoid_pieces)
{
    if(fuel == 0) return;

    if(out_of_bounds(row, col)) return;

    if(v[row][col].has_piece() && !avoid_pieces)
    {
        identify_opponent(v, row, col, color, moves_list);
        return;
    }

    if(!avoid_pieces) {
        moves_list.push_back({row, col});
    }
    fuel--;

    travel_straight(v, row + _row, col + _col, _row, _col, fuel, moves_list, color, avoid_pieces);
    if(fuel == 0 && avoid_pieces) moves_list.push_back({row, col});
}

void MoveSet::cardinal_traversal(vector<vector<Square>> vec, int row, int col, int fuel, vector<array<int, 2>>& moves_list, char color, bool avoid_pieces)
{
    if(fuel == 0) return;

    travel_straight(vec, row, col - 1, 0, -1, fuel, moves_list, color, avoid_pieces);
    travel_straight(vec, row, col + 1, 0, +1, fuel, moves_list, color, avoid_pieces);
    travel_straight(vec, row + 1, col, +1, 0, fuel, moves_list, color, avoid_pieces);
    travel_straight(vec, row - 1, col, -1, 0, fuel, moves_list, color, avoid_pieces);
}

void MoveSet::knight_move_set(vector<vector<Square>> v, int row, int col, vector<array<int, 2>>& moves_list, char color)
{
    bool avoid_pieces = false;
    cardinal_traversal(v, row, col, 2, moves_list, color, true);

    vector<array<int, 2>> temp = moves_list;
    moves_list = vector<array<int, 2>>();

    for(array<int, 2> a : temp)
    {
        if(a[1] > col || a[1] < col)
        {
            travel_straight(v, a[0] - 1, a[1], -1, 0, 1, moves_list, color, avoid_pieces);
            travel_straight(v, a[0] + 1, a[1], -1, 0, 1, moves_list, color, avoid_pieces);
        }

        if(a[0] > row || a[0] < row)
        {
            travel_straight(v, a[0], a[1] - 1, 0, -1, 1, moves_list, color, avoid_pieces);
            travel_straight(v, a[0], a[1] + 1, 0, -1, 1, moves_list, color, avoid_pieces);
        }
    }

}
