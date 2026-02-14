#include <catch2/catch_test_macros.hpp>
#include "../src/board/board.h"

using namespace std;

TEST_CASE("King", "[board]")
{
    Board board;

    SECTION("When: A piece gives a check to the opponent king - Then: Return true")
    {
        board.move_piece("e2e4");
        board.move_piece("f7f5");
        board.move_piece("d1h5");
        REQUIRE(board.is_checked('B') == true);
    }

    SECTION("When: A piece gives a check to the opponent king and the player does have squares to go to - Then: is_checkmate should return true")
    {
        board.move_piece("e2e4");
        board.move_piece("f7f5");
        board.move_piece("d1h5");
        REQUIRE(board.is_checkmate(board.get_turn()) == false);
    }

    SECTION("When: An opponent knight gives a check to the opponent king - Then: Return true")
    {
        board.move_piece("b1c3");
        board.move_piece("a7a6");
        board.move_piece("c3d5");
        board.move_piece("a6a5");
        REQUIRE(board.move_piece("d5c7") == true);
    }

    SECTION("When: Trying to move another piece while the king of the same side is under check - Then: Return false")
    {
        board.move_piece("e2e4");
        board.move_piece("f7f5");
        board.move_piece("d1h5");
        board.move_piece("a2a4");
        REQUIRE(board.move_piece("a1a2") == false);
    }

    SECTION("When: Trying to move the king in line-of-sight (range) of another piece - Then: Return false")
    {
        board.move_piece("c2c3");
        board.move_piece("f7f6");
        board.move_piece("d2b3");
        REQUIRE(board.move_piece("e8f7") == false);
    }

    SECTION("When: There are no more safe moves/squares left for one side that can protect their king AKA it's a checkmate - Then: Return true")
    {
        board.move_piece("e2e4");
        board.move_piece("g7g5");
        board.move_piece("b1c3");
        board.move_piece("f7f6");
        board.move_piece("d1h5");
        REQUIRE(board.is_checkmate(board.get_turn()) == true);
    }

}

TEST_CASE("Pawn", "[board]")
{
    Board board;

    SECTION("When: A pawn on it's starting square tries to move 2 squares - Then: Return true")
    {
        REQUIRE(board.move_piece("a2a4") == true);
    }

    SECTION("When: A pawn not on it's starting square tries to move 2 squares - Then: Return false")
    {
        board.move_piece("a2a4");
        REQUIRE(board.move_piece("a4a6") == false);
    }

    SECTION("When: A pawn tries to move diagonally with no piece on the target square - Then: Return false")
    {
        board.move_piece("d2d4");
        board.move_piece("d7d5");
        REQUIRE(board.move_piece("d4e5") == false);
    }

    SECTION("When: A pawn tries to move diagonally with a piece present on the target square - Then: Return false")
    {
        board.move_piece("d2d4");
        board.move_piece("e7e5");
        REQUIRE(board.move_piece("d4e5") == true);
    }

    SECTION("When: A pawn tries to capture a piece by moving forward - Then: Return false")
    {
        board.move_piece("e2e4");
        board.move_piece("e7e5");
        REQUIRE(board.move_piece("e4e5") == false);
    }
}


