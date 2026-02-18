#include <iostream>
#include <vector>
#include <string>
#include <array>

#include "board.h"
#include "../square/square.h"
#include "./pieces/move-sets/move-set.h"
#include "../helper-functions.h"

using namespace std;

void Board::initialize_board()
{
    for(int i = 0, step = 0; i < 8; i++, step++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(step % 2 == 0)
            {
                board[i][j].set_color('W');
            } else
            {
                board[i][j].set_color('B');
            }

            step++;
        }
    }

    Piece b_pawn = Piece({
        "               ",
        "               ",
        "     .-'-.     ",
        "     `###'     ",
        "     .###.     ",
        "    .'###'.    ",
        "    `-----'    "
    }, {
        "###############",
        "###############",
        "#####.-'-.#####",
        "#####`###'#####",
        "#####.###.#####",
        "####.'###'.####",
        "####`-----'####"
                         }, 'B', 0, true);
    Piece w_pawn = Piece({
        "               ",
        "               ",
        "     .-'-.     ",
        "     `. .'     ",
        "     .' '.     ",
        "    .'___'.    ",
        "    `-----'    "
    }, {
        "###############",
        "###############",
        "#####.-'-.#####",
        "#####`. .'#####",
        "#####.' '.#####",
        "####.'___'.####",
        "####`-----'####"
                         }, 'W', 0, true);

    for(int i = 0; i < 8; i++)
    {
        board[1][i].is_empty = false;
        board[1][i].set_piece(b_pawn);

        board[6][i].is_empty = false;
        board[6][i].set_piece(w_pawn);
    }


    // Black Pieces
    Piece b_rook = Piece({
        "     _   _     ",
        "    |#|_|#|    ",
        "    |#####|    ",
        "    '#####'    ",
        "    |#####|    ",
        "   /_.---._\\   ",
        "   '._____.'   "
    }, {
        "#####_###_#####",
        "####|#|_|#|####",
        "####|#####|####",
        "####'#####'####",
        "####|#####|####",
        "###/_.---._\\###",
        "###'._____.'###"
                         }, 'B', 4);

    Piece b_knight = Piece({
        "               ",
        "     |\\.       ",
        "    /####.     ",
        "   /_#'###\\    ",
        "      /###|    ",
        "     /####|    ",
        "    `.____.'   "
    }, {
        "###############",
        "#####|\\.#######",
        "####/####.#####",
        "###/_#'###\\####",
        "##### /###|####",
        "#####/####|####",
        "####`.____.'###"
                         }, 'B', 2);

    Piece b_bishop = Piece({
        "      .-.      ",
        "     .'#'.     ",
        "     (###)     ",
        "     `.#.'     ",
        "      |#|      ",
        "    ._'#'_.    ",
        "    '--^--'    "
    }, {
        "######.-.######",
        "#####.'#'.#####",
        "#####(###)#####",
        "#####`.#.'#####",
        "######|#|######",
        "####._'#'_.####",
        "####'--^--'####"
                         }, 'B', 3);

    Piece b_queen = Piece({
        "               ",
        "     o   o     ",
        " o   /\\ /\\  o  ",
        " \\`.'##`##`'/  ",
        "  \\########/   ",
        "   \\_.--._/    ",
        "   '.____.'    "
    },{
        "###############",
        "#####o###o#####",
        "#o###/\\#/\\##o##",
        "#\\`.'##`##`'/##",
        "##\\########/###",
        "###\\_.--._/####",
        "###'.____.'####"
                         }, 'B', 5);

    Piece b_king = Piece({
        "       _       ",
        "      ( )      ",
        "   .-. ^ .-.   ",
        "  :###`.'###:  ",
        "  `.#######.'  ",
        "   )_.---._(   ",
        "   `._____.'   "
    }, {
        "###############",
        "######( )######",
        "###.-. ^ .-.###",
        "##:###`.'###:##",
        "##`.#######.'##",
        "###)_.---._(###",
        "###`._____.'###"
                         }, 'B', 1);


    // White Pieces
    Piece w_rook = Piece({
        "     _   _     ",
        "    | |_| |    ",
        "    |     |    ",
        "    '     '    ",
        "    |     |    ",
        "   /_.---._\\   ",
        "   '._____.'   "
    }, {
        "#####_###_#####",
        "####| |_| |####",
        "####|     |####",
        "####'     '####",
        "####|     |####",
        "###/_.---._\\###",
        "###'._____.'###"
                         }, 'W', 4);

    Piece w_knight = Piece({
        "               ",
        "     |\\.       ",
        "    /   '.     ",
        "   /_.'-  \\    ",
        "      /   |    ",
        "     /____|    ",
        "    `.____.'   "
    }, {
        "###############",
        "#####|\\.#######",
        "####/   '.#####",
        "###/_.'-  \\####",
        "##### /   |####",
        "#####/    |####",
        "####`.____.'###"
                         }, 'W', 2);

    Piece w_bishop = Piece({
        "      .-.      ",
        "     .' '.     ",
        "     (   )     ",
        "     `. .'     ",
        "      | |      ",
        "    ._' '_.    ",
        "    '--^--'    "
    }, {
        "######.-.######",
        "#####.' '.#####",
        "#####(   )#####",
        "#####`. .'#####",
        "######| |######",
        "####._' '_.####",
        "####'--^--'####"
                         }, 'W', 3);

    Piece w_queen = Piece({
        "               ",
        "     o   o     ",
        " o   /\\ /\\  o  ",
        " \\`.'  `  `'/  ",
        "  \\        /   ",
        "   \\_.--._/    ",
        "   '.____.'    "
    }, {
        "###############",
        "#####o###o#####",
        "#o###/\\#/\\##o##",
        "#\\`.'  `  `'/##",
        "##\\        /###",
        "###\\_.--._/####",
        "###'.____.'####"
                          }, 'W', 5);

    Piece w_king = Piece({
        "       _       ",
        "      ( )      ",
        "   .-. ^ .-.   ",
        "  :   `.'   :  ",
        "  `.       .'  ",
        "   )_.---._(   ",
        "   `._____.'   "
    }, {
        "###############",
        "######( )######",
        "###.-. ^ .-.###",
        "##:   `.'   :##",
        "##`.       .'##",
        "###)_.---._(###",
        "###`._____.'###"
                         }, 'W', 1);


    // Setting up all the pieces by directly indexing - Don't think this is a good practice but can't really come up with another solution for this

    // Black major pieces --
        // Black Rooks
        board[0][0].set_piece(b_rook);
        board[0][7].set_piece(b_rook);

        // Black Knights
        board[0][1].set_piece(b_knight);
        board[0][6].set_piece(b_knight);

        // Black Bishops
        board[0][2].set_piece(b_bishop);
        board[0][5].set_piece(b_bishop);

        // Black Queen
        board[0][3].set_piece(b_queen);

        // Black King
        board[0][4].set_piece(b_king);
    // --X

    // White major pieces --
        // White Rooks
        board[7][0].set_piece(w_rook);
        board[7][7].set_piece(w_rook);

        // White Knights
        board[7][1].set_piece(w_knight);
        board[7][6].set_piece(w_knight);

        // White Bishops
        board[7][2].set_piece(w_bishop);
        board[7][5].set_piece(w_bishop);

        // White Queen
        board[7][3].set_piece(w_queen);

        // White King
        board[7][4].set_piece(w_king);
    // --X

    // Set the squares that are now occupied by pieces to non-empty

    for(Square& s : board[0])
    {
        s.is_empty = false;
    }

    for(Square& s : board[7])
    {
        s.is_empty = false;
    }
}

void Board::print_board(WINDOW* window)
{
    vector<string> temp(64, "");
    int step = 0;

    for(int i = 0; i < 8; i++)
    {
        for(Square s : board[i])
        {
            char color = 'B';
            if(s.get_color() != 'B')
            {
                color = 'W';
            }
            Piece piece = s.get_piece();

            if(!s.has_piece())
            {
                if(color == 'B')
                {
                    for(int j = 0; j < 7; j++)
                    {
                        temp[step + j] += black_sqaure_ascii[j];
                    }
                } else
                {
                    for(int j = 0; j < 7; j++)
                    {
                        temp[step + j] += white_sqaure_ascii[j];
                    }
                }
            } else
            {
                if(color == 'B')
                {
                    for(int j = 0; j < 7; j++)
                    {
                        temp[step + j] += piece.ascii_black[j];
                    }
                } else
                {
                    for(int j = 0; j < 7; j++)
                    {
                        temp[step + j] += piece.ascii_white[j];
                    }
                }
            }

        }

        step += 7;
    }

    int pos_y = 1;
    for(string& str : temp)
    {
        mvwprintw(window, pos_y, 9, "%s", str.c_str());
        pos_y++;
    }
}

void Board::print_score(WINDOW* window)
{
    int y, x;
    getmaxyx(window, y, x);

    wattron(window, A_STANDOUT | COLOR_BLACK | A_BOLD);
    mvwprintw(window, y - 5, 1, "B:%i", black_score);
    mvwprintw(window, y - 5, x - 5, "W:%i", white_score);
    wattroff(window, A_STANDOUT | COLOR_BLACK | A_BOLD);
}

bool Board::valid_move(Piece p, int file, int rank, int target_file, int target_rank)
{
    vector<array<int, 2>> moves_list;

    get_moves(p, file, rank, moves_list, board);

    if(p.type == 0)
    {
        int n = +1;
        if(p.color == 'W')
        {
            n = -1;
        }

        if((board[rank + n][file].has_piece() || board[rank +(n * 2)][file].has_piece()) && target_file == file) return false;
    }

    for(array<int, 2> c : moves_list)
    {
        if(c[0] == target_rank && c[1] == target_file)
        {
            return true;
        }
    }

    return false;
}

bool Board::move_piece(char move[])
{
    int file = static_cast<int>(move[0]) - 97;
    int rank = 56 - static_cast<int>(move[1]);

    int target_file = static_cast<int>(move[2]) - 97;
    int target_rank = 56 - static_cast<int>(move[3]);

    if (out_of_bounds(rank, file) || out_of_bounds(target_rank, target_file))
    {
        cout << "Invalid notation! Please use standard notations to move the pieces" << endl;
        return false;
    }

    Square& curr_square = board[rank][file];
    Square& target_square = board[target_rank][target_file];

    Piece piece;

    if(!curr_square.has_piece())
    {
        cout << "\033[33m=> \033[0m" << move[0] << move[1] << "\033[33m is an empty square!\033[0m\n";
        // print_board();
        return false;
    }

    piece = curr_square.get_piece();

    if(get_turn() != piece.color)
    {
        cout << "Not your turn! It's your opponent's turn to move their piece." << endl;
        return false;
    }

    if(get_turn() == piece.color && is_checked(get_turn()))
    {
        if(!is_king_safe(piece, file, rank, target_file, target_rank))
        {
            if(piece.type == 1)
            {
                cout << "\033[31m> Illegal Move!\033[0m" << endl;
                return false;
            }
            cout << "\033[31m> Illegal Move!\033[0m" << endl;
            cout << "Your king is in danger! Move it to a safe position first." << endl;
            return false;
        }
    }

    if(!valid_move(piece, file, rank, target_file, target_rank))
    {
        cout << "\033[31m> Invalid Move!\033[0m" << endl;
        return false;
    }

    if(piece.type == 1)
    {
        if(piece.color == 'W')
        {
            update_wk_position({target_rank, target_file});
        } else
        {
            update_bk_position({target_rank, target_file});
        }
    }

    if(target_square.has_piece())
    {
        Piece temp_target = target_square.get_piece();

        // Update the captured_pieces list whenever a piece is captured
        captured_pieces.push_back(temp_target);

        // Update the score when a piece is captured
        if(piece.color == 'W')
        {
            if(temp_target.type == 0 || temp_target.type == 2)
            {
                white_score += ++temp_target.type;
            } else
            {
                white_score += temp_target.type;
            }
        } else {
            if(temp_target.type == 0 || temp_target.type == 2)
            {
                black_score += ++temp_target.type;
            } else
            {
                black_score += temp_target.type;
            }
        }
    }

    if(moves_buffer.size() < 3)
    {
        target_square.has_piece() ? moves_buffer.push_back({file, rank, target_file, target_rank, 1}) :
        moves_buffer.push_back({file, rank, target_file, target_rank, 0});
    } else
    {
        moves_buffer.pop_front();
        target_square.has_piece() ? moves_buffer.push_back({file, rank, target_file, target_rank, 1}) :
        moves_buffer.push_back({file, rank, target_file, target_rank, 0});
    }

    curr_square.clear_square();
    target_square.set_piece(piece, false);
    if(target_square.get_piece().type == 0 && target_square.get_piece().on_start == true)
    {
        target_square.update_position(false);
    }

    if(piece.color == 'W')
    {
        update_turn('B');
    } else
    {
        update_turn('W');
    }

    return true;
}

int Board::undo_move()
{
    int s = moves_buffer.size();

    if(s == 0)
    {
        cout << "> No moves in the moves buffer, it only stores the last 3 moves." << endl;
        return 0;
    }

    int target_file = moves_buffer[s-1][0];
    int target_rank = moves_buffer[s-1][1];
    int file = moves_buffer[s-1][2];
    int rank = moves_buffer[s-1][3];

    int captured = moves_buffer[s-1][4];

    Piece temp = board[rank][file].get_piece();

    if(captured)
    {
        Piece captured_piece = captured_pieces[captured_pieces.size() - 1];

        board[rank][file].set_piece(captured_piece, false);
        board[target_rank][target_file].set_piece(temp, false);

        captured_pieces.pop_back();
    } else
    {
        board[rank][file].clear_square();
        board[target_rank][target_file].set_piece(temp, false);
    }

    int row = 6;
    if(temp.color == 'B')
    {
        row = 1;
    }
    if(temp.type == 0 && target_rank == row)
    {
        board[target_rank][target_file].update_position(true);
    }


    moves_buffer.pop_back();
    update_turn(temp.color);

    if(temp.color == 'W')
    {
        temp.type == 1 || temp.type == 2 ? (black_score -= ++temp.type) :
        (black_score -= temp.type);
    } else
    {
        temp.type == 1 || temp.type == 2 ? (white_score -= ++temp.type) :
        (white_score -= temp.type);
    }

    return 1;
}

bool Board::is_king_safe(Piece piece, int file, int rank, int target_file, int target_rank)
{
    Board temp_board;
    temp_board.board = board;
    Square& temp_square = temp_board.board[rank][file];
    Square& temp_target = temp_board.board[target_rank][target_file];

    if(!temp_board.valid_move(piece, file, rank, target_file, target_rank))
    {
        return false;
    }

    temp_square.clear_square();
    temp_target.set_piece(piece, false);

    if(piece.type == 1)
    {
        if(piece.color == 'B')
        {
            temp_board.update_bk_position({target_rank, target_file});
        } else
        {
            temp_board.update_wk_position({target_rank, target_file});
        }
    }

    if(temp_board.is_checked(piece.color))
    {
        return false;
    }

    return true;
}

bool Board::is_checked(char color)
{
    int rank = get_bk_position()[0];
    int file = get_bk_position()[1];

    if(color == 'W')
    {
        rank = get_wk_position()[0];
        file = get_wk_position()[1];
    }

    vector<array<int, 2>> in_sight;
    vector<array<int, 2>> in_L_sight;

    MoveSet::intercardinal_traversal(board, rank, file, 8, in_sight, color, false);
    MoveSet::cardinal_traversal(board, rank, file, 8, in_sight, color, false);
    MoveSet::knight_move_set(board, rank, file, in_L_sight, color);

    int target_rank;
    int target_file;
    Square square;

    for(array<int, 2> a : in_sight)
    {
        target_rank = a[0];
        target_file = a[1];
        square = board[target_rank][target_file];

        if(!square.has_piece())
        {
            continue;
        }
        if(valid_move(square.get_piece(), target_file, target_rank, file, rank))
        {
            return true;
        }
    }

    for(array<int, 2> a : in_L_sight)
    {
        target_rank = a[0];
        target_file = a[1];
        square = board[target_rank][target_file];

        if(!square.has_piece())
        {
            continue;
        }
        if(valid_move(square.get_piece(), target_file, target_rank, file, rank))
        {
            return true;
        }
    }

    return false;
}

bool Board::is_checkmate(char color)
{
    vector<array<int, 2>> squares;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(board[i][j].get_piece().color == color)
            {
                squares.push_back({i, j});
            }

            if(squares.size() == 16)
            {
                break;
            }
        }
    }

    int rank;
    int file;

    vector<array<int, 2>> moves_list;

    for(array<int, 2> square : squares)
    {
        int target_rank;
        int target_file;

        moves_list = vector<array<int, 2>>();

        rank = square[0];
        file = square[1];

        Piece p = board[rank][file].get_piece();

        get_moves(p, file, rank, moves_list, board);

        for(array<int, 2> move : moves_list)
        {
            target_rank = move[0];
            target_file = move[1];

            if(is_king_safe(p, file, rank, target_file, target_rank))
            {
                return false;
            }
        }
    }

    return true;
}
