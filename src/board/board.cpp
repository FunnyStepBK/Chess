#include <vector>
#include <string>
#include <array>

#include <ncurses.h>
#include "board.hpp"
#include "../windows/windows.hpp"
#include "../helper-functions.hpp"
#include "./pieces/move-sets/move-set.hpp"
#include "./pieces/piece-templates/piece-template.hpp"

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

    for(int i = 0; i < 8; i++)
    {
        board[1][i].is_empty = false;
        board[1][i].set_piece(B_PAWN);

        board[6][i].is_empty = false;
        board[6][i].set_piece(W_PAWN);
    }


    // Black Pieces
    Piece b_rook = B_ROOK_TEMPLATE;
    Piece b_knight = B_KNIGHT_TEMPLATE;
    Piece b_bishop = B_BISHOP_TEMPLATE;
    Piece b_queen = B_QUEEN_TEMPLATE;
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
                         }, 'B', 1, true);


    // White Pieces
    Piece w_rook = W_ROOK_TEMPLATE;
    Piece w_knight = W_KNIGHT_TEMPLATE;
    Piece w_bishop = W_BISHOP_TEMPLATE;
    Piece w_queen =  W_QUEEN_TEMPLATE;
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
                         }, 'W', 1, true);


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

int Board::valid_move(Piece p, int file, int rank, int target_file, int target_rank)
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

        int size = moves_buffer.size();

        int last_move_target_rank;
        int last_move_target_file;
        int last_move_rank;

        if(size != 0)
        {
            last_move_target_rank = moves_buffer[moves_buffer.size() - 1][3];
            last_move_target_file = moves_buffer[moves_buffer.size() - 1][2];
            last_move_rank = moves_buffer[moves_buffer.size() - 1][1];
        }

        int valid_rank;
        int valid_file;
        int counter = 0;

        Square valid_square;

        for(array<int, 2> a : moves_list)
        {
            valid_rank = a[0];
            valid_file = a[1];

            valid_square = board[valid_rank][valid_file];

            // A check so pawns can't move to diagonal squares when there is no piece to capture on that square
            if(valid_file != file && !valid_square.has_piece())
            {

                // A check for en-passant
                valid_square = board[rank][valid_file];
                if(valid_square.has_piece() && valid_square.get_piece().type == 0 && size != 0)
                {
                    // Here we are doing last_move_rank - 2 * n, because we want to check if last_move_rank is 2 squares away from last_move_target_rank
                    // and the reason it's - 2 rather then + 2 is cuz if the value of n is 1 it will become -1 as that's what the value of n
                    // would have been on the last iteration of valid_move
                    if((last_move_target_rank == rank && last_move_target_file == valid_file) && last_move_rank - 2 * n == last_move_target_rank)
                    {
                        counter++;
                        continue;
                    }
                }

                moves_list.erase(moves_list.begin() + counter);
            }

            counter++;
        }

        // A check so a pawn can't capture pieces by moving forward
        if(target_file == file && board[target_rank][target_file].has_piece()) return false;
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

int Board::valid_move(Piece p, int file, int rank, int target_file, int target_rank, bool& is_castle)
{
    Square target_square = board[target_rank][target_file];

    if(p.type == 1 && (target_square.has_piece() && target_square.get_piece().type == 4) && p.color == target_square.get_piece().color)
    {
        if(p.on_start && target_square.get_piece().on_start)
        {
            is_castle = true;
            return true;
        }
    }

    return valid_move(p, file, rank, target_file, target_rank);
}

int Board::move_piece(char move[], WINDOW* input_window, WINDOW* warn_log_win)
{
    // We are gonna use this variable as a flag to check if the move type is castiling by passing it as a param in valid_move and after calling valid_move
    // we will check if this flag is triggered if it is then we will castle and return
    bool is_castle = false;

    int file = static_cast<int>(move[0]) - 97;
    int rank = 56 - static_cast<int>(move[1]);

    int target_file = static_cast<int>(move[2]) - 97;
    int target_rank = 56 - static_cast<int>(move[3]);

    // Check if the input is valid
    if (out_of_bounds(rank, file) || out_of_bounds(target_rank, target_file))
    {
        return INVALID_INPUT;
    }

    Square& curr_square = board[rank][file];
    Square& target_square = board[target_rank][target_file];

    Piece piece;

    // Check if the chosen square is empty - If yes, then return
    if(!curr_square.has_piece())
    {
        return EMPTY_SQUARE;
    }

    piece = curr_square.get_piece();

    // Check if a valid move
    if(get_turn() != piece.color || !valid_move(piece, file, rank, target_file, target_rank, is_castle))
    {
        return INVALID_MOVE;
    }

    // check if not an illegal move
    if(!is_king_safe(piece, file, rank, target_file, target_rank))
    {
        return ILLEGAL_MOVE;
    }

    // Check if the move type is castling
    if(is_castle)
    {
        return validate_and_castle(file, rank, target_file, target_rank, warn_log_win) ? VALID_MOVE : INVALID_MOVE;
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

    // if there is not piece on the target square, the piece type is 0 (a pawn) and target_file equals file - it means the move type is 2
    // AKA en-passant
    if(piece.type == 0 && target_file != file && !target_square.has_piece())
    {
        int n = piece.color == 'B' ? -1 : +1;

        int captured_rank = target_rank + n;
        Square& taken_piece = board[captured_rank][target_file];

        // Update the moves_buffer with move type 1 if a piece was captured
        update_moves_buffer(file, rank, target_file, captured_rank, 2);

        // Update the captured_pieces list whenever a piece is captured
        captured_pieces.push_back(taken_piece.get_piece());

        // Update the score when a piece is captured
        increment_score(taken_piece.get_piece());

        taken_piece.clear_square();

    // If there is a piece on the target_square
    } else if(target_square.has_piece())
    {
        Piece temp_target = target_square.get_piece();

        // Update the moves_buffer with move type 1 if a piece was captured
        update_moves_buffer(file, rank, target_file, target_rank, 1);

        // Update the captured_pieces list whenever a piece is captured
        captured_pieces.push_back(temp_target);

        // Update the score when a piece is captured
        increment_score(temp_target);

    // Default to move type 0 if the cases written above don't pass
    } else
    {
        update_moves_buffer(file, rank, target_file, target_rank, 0);
    }


    // Move the selected piece to the now empty square and that only if there was a piece on that square
    move_to_square(curr_square, target_square, piece);

    // Update the turn
    update_turn();

    Piece moved_piece = target_square.get_piece();

    if(moved_piece.type == 0 || moved_piece.type == 1 || moved_piece.type == 4)
    {
        if(moved_piece.on_start)
        {
            target_square.update_position(false);
        }

        int promotion_rank = piece.color == 'B' ? 7 : 0;
        if(target_rank == promotion_rank && moved_piece.type == 0)
        {
            int piece_type = prompt_promotion(input_window, warn_log_win);

            switch(piece_type)
            {
                case 2:
                    target_square.set_piece(piece.color == 'B' ? B_KNIGHT_TEMPLATE : W_KNIGHT_TEMPLATE);
                    break;
                case 3:
                    target_square.set_piece(piece.color == 'B' ? B_BISHOP_TEMPLATE : W_BISHOP_TEMPLATE);
                    break;
                case 4:
                    target_square.set_piece(piece.color == 'B' ? B_ROOK_TEMPLATE : W_ROOK_TEMPLATE);
                    break;
                case 5:
                    target_square.set_piece(piece.color == 'B' ? B_QUEEN_TEMPLATE : B_QUEEN_TEMPLATE);
                    break;
            }

            int& last_move_type = moves_buffer[moves_buffer.size() - 1][4];
            last_move_type = last_move_type == 1 ? 4 : 3;
        }

    }

    clear_and_box_win(warn_log_win);

    return VALID_MOVE;
}

int Board::undo_move(WINDOW* warn_log_win)
{
    int s = moves_buffer.size();

    if(s == 0)
    {
        mvwprintw(warn_log_win, 1, 1, "> No moves in the moves buffer, it only stores the last 3 moves.");
        return 0;
    }

    int file = moves_buffer[s-1][0];
    int rank = moves_buffer[s-1][1];
    int current_file = moves_buffer[s-1][2];
    int current_rank = moves_buffer[s-1][3];

    int move_type = moves_buffer[s-1][4];

    int n = get_turn() == 'B' ? -1 : +1;

    Square& initial_square = board[rank][file];

    Square& current_square = board[current_rank][current_file];

    Piece moved_piece = move_type == 2 && !current_square.has_piece() ? board[current_rank + n][current_file].get_piece() : current_square.get_piece();

    switch(move_type)
    {

        // if move_type is 3, we can simply set replace the temp piece with a pawn of respective color
        case 3:
            Board::convert_to_pawn(moved_piece);
            [[fallthrough]];

        // If move_type is 0, we clear the current square and set piece on initial square
        case 0: {
            move_to_square(current_square, initial_square, moved_piece);
            break;
        }

        // If move_type is 2, we can just clear the {current_rank + n, curren_file} square and how we have handled temp's declaration let's us
        // get away with only this much extra code for en-passant.
        case 2:
            board[current_rank + n][current_file].clear_square();
            [[fallthrough]];

        // If move_type is 1, we can re-store the piece that was last captured in the captured_pieces vector then set it to target_square
        // and set the capturing piece to it's initial square.
        case 1: {
            undo_capture(current_square, initial_square, moved_piece);
            break;
        }

        // If move_type is 4, Convert the moved piece to a pawn respecitve to it's color and then just undo capture
        case 4: {
            Board::convert_to_pawn(moved_piece);
            undo_capture(current_square, initial_square, moved_piece);
            break;
        }

        // If move_type is 5, Assign squares respecitve to the current_file to temp_king and temp_rook, then move back the moved
        // pieces to their initial squares and then clear temp_king & temp_rook squares
        case 5: {
            Square& temp_king = current_file == 0 ? board[current_rank][current_file + 2] : board[current_rank][current_file - 1];
            Square& temp_rook = current_file == 0 ? board[current_rank][file - 1] : board[current_rank][file + 1];

            initial_square.set_piece(temp_king.get_piece(), false);
            current_square.set_piece(temp_rook.get_piece(), false);

            temp_king.clear_square();
            temp_rook.clear_square();

            break;
        }

    }

    int row = moved_piece.color == 'B' ? 1 : 6;
    if(moved_piece.type != 0) row = moved_piece.color == 'B' ? 0 : 7;

    if(((moved_piece.type == 0) ||
        (moved_piece.type == 1 && file == 4) ||
        (moved_piece.type == 4 && (file == 0 || file == 7))) &&
        rank == row)
    {
        board[rank][file].update_position(true);
    }

    moves_buffer.pop_back();

    // Update the turn
    update_turn();

    if(move_type == 1)
    {
        decrement_score(moved_piece);
    }

    return 1;
}

void Board::undo_capture(Square& current_square, Square& initial_square, Piece capturing_piece)
{
    Piece captured_piece = captured_pieces[captured_pieces.size() - 1];

    current_square.set_piece(captured_piece, false);
    initial_square.set_piece(capturing_piece, false);

    captured_pieces.pop_back();
}

int Board::prompt_promotion(WINDOW* input_window, WINDOW* warn_log_win)
{
    mvwprintw(warn_log_win, 1, 1, "> Your pawn reached the promotion rank! What do you want to promote it to?");

    array<string, 4> options = {">> Knight", ">> Bishop", ">> Rook", ">> Queen"};
    int choice;
    int highlight = 0;

    int size = options.size();

    wmove(input_window, 2, 3);

    while(true)
    {
        for(int i = 0; i < size; i++)
        {
            if(i == highlight)
            {
                wattron(warn_log_win, A_REVERSE);
            }
            mvwprintw(warn_log_win, 3+i, 1, "%s", options[i].c_str());
            wattroff(warn_log_win, A_REVERSE);
        }
        wrefresh(warn_log_win);

        // Move the cursor the input window and clear the user-input then get the key inputs from that window so we won't need to unnecessarily
        // set keypad true for the warn_log_win and it also makes much more sense getting the input from input window ._.
        wmove(input_window, 2, 3);

        choice = wgetch(input_window);

        switch(choice)
        {
            case KEY_UP:
            case 107:
                highlight--;
                if(highlight == -1) highlight = 0;
                break;
            case KEY_DOWN:
            case 106:
                highlight++;
                if(highlight == size) highlight = size - 1;
                break;
            default:
                break;
        }

        if(choice == 10)
        {
            break;
        }

    }

    return highlight + 2;
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

    move_to_square(temp_square, temp_target, temp_square.get_piece());

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

bool Board::validate_and_castle(int file, int rank, int target_file, int target_rank, WINDOW* warn_log_win)
{
    Square& king_square = board[rank][file];
    Square& rook_square = board[target_rank][target_file];

    // Return if the king is under check
    if(is_checked(king_square.get_piece().color))
    {
        mvwprintw(warn_log_win, 1, 1, "> Your king is under check! Can't castle in current position.");
        return false;
    }

    int check_rank = 0;
    int check_file = 0;


    // If target_file is 0 then we make n equal to -1 because we need to travel back from the current index (that is of the king - 4) and make it +1
    // if target_file dosen't equal to 0 - here we don't need to check if the target_file is not 0 then it should be 7 becaues we already do that
    // in valid_move
    int n = target_file == 0 ? -1 : 1;

    vector<array<int, 2>> squares_list;
    MoveSet::travel_straight(board, rank, file + n, 0, n, n == 1 ? 2 : 3, squares_list, king_square.get_color(), false);

    int size = squares_list.size();

    // If the size of squares_list is not equal to the number respective to the value of n, then we return as that's the number of pieces/squares
    // present between the king and that rook (respective to the value of n ofc) so it would mean that there is/are some pieces present between
    // the king and the rook
    if(n == 1 ? size != 2 : size != 3)
    {
        mvwprintw(warn_log_win, 1, 1, "> Unable to castle! There is/are some pieces present between the king and the rook.");
        return false;
    }

    check_rank = squares_list[size - 1][0];
    check_file = squares_list[size - 1][1];

    // Now we just move the king and the rook to the squares in accordance with the value of n
    if(n == 1)
    {
        if(!castle_if_safe(check_file, squares_list[0][1], check_rank, king_square, rook_square))
        {
            mvwprintw(warn_log_win, 1, 1, "> Unable to castle! The king will be under attack.");
            return false;
        }

    } else
    {
        if(!castle_if_safe(squares_list[1][1], squares_list[0][1], check_rank, king_square, rook_square))
        {
            mvwprintw(warn_log_win, 1, 1, "> Unable to castle! The king will be under attack.");
            return false;
        }

    }

    update_moves_buffer(file, rank, target_file, target_rank, 5);
    return true;
}

bool Board::castle_if_safe(int king_file, int rook_file, int back_rank, Square& king_square, Square& rook_square)
{
    board[back_rank][king_file].set_piece(king_square.get_piece(), false);
    board[back_rank][rook_file].set_piece(rook_square.get_piece(), false);

    // Checks if the king is under check and if yes then return false
    if(is_checked(king_square.get_color()))
    {
        board[back_rank][king_file].clear_square();
        board[back_rank][rook_file].clear_square();

        return false;
    }

    king_square.clear_square();
    rook_square.clear_square();

    return true;
}

void Board::increment_score(Piece piece)
{
    if(piece.color == 'B')
    {
        if(piece.type == 0 || piece.type == 2)
        {
            white_score += 1 + piece.type;
        } else
        {
            white_score += piece.type;
        }
    } else {
        if(piece.type == 0 || piece.type == 2)
        {
            black_score += 1 + piece.type;
        } else
        {
            black_score += piece.type;
        }
    }
}

void Board::decrement_score(Piece piece)
{
    if(piece.color == 'B')
    {
        piece.type == 0 ||piece.type == 2 ? (black_score -= 1 + piece.type) :
        (black_score -= piece.type);
    } else
    {
        piece.type == 0 ||piece.type == 2 ? (white_score -= 1 + piece.type) :
        (white_score -= piece.type);
    }
}

void Board::update_moves_buffer(int file, int rank, int target_file, int target_rank, int move_type)
{
    if(moves_buffer.size() == 3)
    {
        moves_buffer.pop_front();
    }

    moves_buffer.push_back({file, rank, target_file, target_rank, move_type});
}

void Board::convert_to_pawn(Piece& piece)
{
    piece = W_PAWN;
    if (piece.color == 'B')
    {
        piece = B_PAWN;
    }
}

void Board::move_to_square(Square& curr_square, Square& target_square, Piece piece)
{
    curr_square.clear_square();
    target_square.set_piece(piece, false);
}
