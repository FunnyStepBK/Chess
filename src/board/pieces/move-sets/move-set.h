#ifndef MOVESET_H
#define MOVESET_H

#include <array>
#include <vector>

#include "../../board.h"

class MoveSet
{
public:
    static void intercardinal_traversal(vector<vector<Square>> v, int row, int col, int fuel, vector<array<int, 2>>& moves_list, char color, bool avoid_pieces);
    static void travel_diagonally(vector<vector<Square>> v, int row, int col, int _row, int _col, int fuel, vector<array<int, 2>>& moves_list, char color, bool avoid_pieces);
    static void travel_straight(vector<vector<Square>> v, int row, int col, int _row, int _col, int fuel, vector<array<int, 2>>& moves_list, char color, bool avoid_pieces);
    static void cardinal_traversal(vector<vector<Square>> v, int row, int col, int fuel, vector<array<int, 2>>& moves_list, char color, bool avoid_pieces);

    static void knight_move_set(vector<vector<Square>> v, int row, int col, vector<array<int, 2>>& moves_list, char color);
};

#endif
