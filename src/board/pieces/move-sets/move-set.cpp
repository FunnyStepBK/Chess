#include <vector>
#include <array>

#include "move-set.h"

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

void MoveSet::travel_diagonally(vector<vector<Square>> v, int row, int col, int _row, int _col, int fuel, vector<array<int, 2>>& moves_list, char color)
{
    if(fuel == 0) return;

    if(Board::out_of_bounds(row, col)) return;

    if(v[row][col].has_piece())
    {
        identify_opponent(v, row, col, color, moves_list);
        return;
    }

    moves_list.push_back({row, col});
    cout << "Added row - " << row << " and col - " << col << " - inside of diagonal ray traversal" << endl;
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

    if(Board::out_of_bounds(row, col)) return;

    if(v[row][col].has_piece())
    {
        identify_opponent(v, row, col, color, moves_list);
        return;
    }

    moves_list.push_back({row, col});
    cout << "Added row - " << row << " and col - " << col << " - inside of straight ray traversal" << endl;
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
