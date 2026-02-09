#include <catch2/catch_test_macros.hpp>
#include "../src/board/board.h"

using namespace std;

TEST_CASE("Try to move the king to the square d2 - this test should fail because that square is range of an enemy piece AKA un-safe for the king", "[board]")
{
    Board board;
    REQUIRE(board.move_piece("e1d2", board) == false);

    SECTION("Give a check to the black king", "[board]")
    {
        board.move_piece("d1e2", board);
        REQUIRE(board.is_king_attacked(board.get_bk_position()) == true);
    }

    SECTION("Trying to move another piece while the king of the same side should result in a fail", "[board]")
    {
        board.move_piece("d1e2", board);
        REQUIRE(board.move_piece("a1a2", board) == false);
    }
}
