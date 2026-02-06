#include <vector>
#include <array>

#include "move-set.h"

using namespace std;

void MoveSet::travel_diagonally(vector<vector<Square>> v, int row, int col, int _row, int _col, int fuel, vector<array<int, 2>>& moves_list, char color)
{
    // It's named fuel but I am using it kinda of as the range of the piece, like for example for the King it would be
    // 1 because it can only move 1 square at a time.
    if(fuel == 0) return;

    // Guard - So we don't go out of bounds
    if((row < 0 || row > 7) || (col < 0 || col > 7))
    {
        return;
    }

    // If it encounters a piece with the same color
    if(v[row][col].has_piece() && v[row][col].get_piece().color == color)
    {
        return;
    }

    // If it encounters a piece with a different color
    if(v[row][col].has_piece() && v[row][col].get_piece().color != color)
    {
        moves_list.push_back({row, col});
        return;
    }

    moves_list.push_back({row, col});
    fuel--;

    travel_diagonally(v, row + _row, col + _col, _row, _col, fuel, moves_list, color);
}

void MoveSet::intercardinal_traversal(vector<vector<Square>> vec, int row, int col, int fuel, vector<array<int, 2>>& moves_list, char color)
{
    if(fuel == 0) return;

    travel_diagonally(vec, row - 1, col + 1, -1, +1, fuel, moves_list, color);
    travel_diagonally(vec, row + 1, col + 1, +1, +1, fuel, moves_list, color);
    travel_diagonally(vec, row + 1, col - 1, +1, -1, fuel, moves_list, color);
    travel_diagonally(vec, row - 1, col - 1, -1, -1, fuel, moves_list, color);
}

void MoveSet::travel_straight(vector<vector<Square>> v, int row, int col, int _row, int _col, int fuel, vector<array<int, 2>>& moves_list, char color)
{
    if(fuel == 0) return;

    // Guard - So we don't go out of bounds
    if((row < 0 || row > 7) || (col < 0 || col > 7))
    {
        return;
    }

    // If it encounters a piece with the same color
    if(v[row][col].has_piece() && v[row][col].get_piece().color == color)
    {
        return;
    }

    // If it encounters a piece with a different color
    if(v[row][col].has_piece() && v[row][col].get_piece().color != color)
    {
        moves_list.push_back({row, col});
        return;
    }

    moves_list.push_back({row, col});
    fuel--;

    travel_straight(v, row + _row, col + _col, _row, _col, fuel, moves_list, color);
}

void MoveSet::cardinal_traversal(vector<vector<Square>> vec, int row, int col, int fuel, vector<array<int, 2>>& moves_list, char color)
{
    if(fuel == 0) return;

    travel_straight(vec, row, col - 1, 0, -1, fuel, moves_list, color);
    travel_straight(vec, row, col + 1, 0, +1, fuel, moves_list, color);
    travel_straight(vec, row + 1, col, +1, 0, fuel, moves_list, color);
    travel_straight(vec, row - 1, col, -1, 0, fuel, moves_list, color);
}
