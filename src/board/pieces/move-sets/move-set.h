#ifndef movesetH
#define movesetH

#include <array>
#include <vector>

#include "../../board.h"

class MoveSet
{
public:
    static void intercardinal_traversal(vector<vector<Square>> v, int row, int col, int fuel, vector<array<int, 2>>& moves_list, char color);
    static void travel_diagonally(vector<vector<Square>> v, int row, int col, int _row, int _col, int fuel, vector<array<int, 2>>& moves_list, char color);
    static void travel_straight(vector<vector<Square>> v, int row, int col, int _row, int _col, int fuel, vector<array<int, 2>>& moves_list, char color);
    static void cardinal_traversal(vector<vector<Square>> v, int row, int col, int fuel, vector<array<int, 2>>& moves_list, char color);
};

#endif
