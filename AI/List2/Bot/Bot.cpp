/**
 * Jakub Drzewiecki
 * 268418
 * Bot class.
 */

#include "Bot.hpp"
#include <limits>
#include <random>

namespace bot {

/**
 * Constructor. Initializes class fields.
 *
 * @param depth Depth of the algorithm.
 * @param player Player number.
 */
Bot::Bot(int depth, int player) {
  depth_ = depth;
  player_ = player;
}

/**
 * This method updates the state of the current board using given move and player number.
 *
 * @param move Number of field on board.
 * @param playerNumber Number of player that makes a move.
 */
void Bot::makeMove(int move, int playerNumber) {
  int row = move / 10;
  int column = move % 10;
  uint64_t sign;
  if(playerNumber == 1)
    sign = 1U;
  else
    sign = 2U;
  for(int i = 1; i < row; i++) {
    sign <<= 10;
  }
  for(int j = 1; j < column; j++) {
    sign <<= 2;
  }
  game_board_ ^= sign;
}

/**
 * This method generates a new game board based on the given one.
 *
 * @param move Number of field on game board.
 * @param playerNumber Number of player that makes a move.
 * @param current_game_board Previous game board.
 * @return New game board after given move.
 */
uint64_t Bot::generateGameBoard(int move, int playerNumber, uint64_t current_game_board) {
  int row = move / 10;
  int column = move % 10;
  uint64_t sign;
  if(playerNumber == 1)
    sign = 1U;
  else
    sign = 2U;
  for(int i = 1; i < row; i++) {
    sign <<= 10;
  }
  for(int j = 1; j < column; j++) {
    sign <<= 2;
  }
  current_game_board ^= sign;
  return current_game_board;
}

/**
 * This method launches alfa-beta algorithm and returns best move.
 *
 * @param playerNumber Number of the player that is currently playing.
 * @return Best available move.
 */
int Bot::findBestMove(int playerNumber) {
  std::pair<int, int> cost = alfaBeta(playerNumber,
                  depth_,
                  std::numeric_limits<int>::min(),
                  std::numeric_limits<int>::max(),
                  game_board_,
                  0);
  return cost.second;
}

/**
 * Alfa-beta algorithm. It checks all game board states up to given depth and finds best available move
 * using heuristic function.
 *
 * @param playerNumber Number of the player that is currently moving.
 * @param depth Current available depth.
 * @param alfa Alfa max heuristic value.
 * @param beta Beta min heuristic value.
 * @param current_game_board Current state of the game board.
 * @param num_of_moves Number of moves that were already done.
 * @return Cost of the best available move
 */
std::pair<int, int> Bot::alfaBeta(int playerNumber,
                  int depth,
                  int alfa,
                  int beta,
                  uint64_t current_game_board,
                  int num_of_moves) {
  int enemy_player = player_ == 1 ? 2 : 1;
  if (isBoardFinal(current_game_board) || depth == 0) {
    return {heuristic(current_game_board, num_of_moves), 0};
  }
  if (playerNumber == enemy_player) {
    int best_move;
    for (int move : getAvailableMoves(current_game_board)) {
      std::pair<int, int> cost =
          alfaBeta(player_,
                   depth - 1,
                   alfa,
                   beta,
                   generateGameBoard(move,
                                     enemy_player,
                                     current_game_board),
                   num_of_moves + 1);
      if (cost.first < beta) {
        beta = cost.first;
        best_move = move;
      }
      if (alfa >= beta) {
        break;
      }
    }
    return {beta, best_move};
  } else {
    int best_move;
    for (int move : getAvailableMoves(current_game_board)) {
      std::pair<int, int> cost =
          alfaBeta(enemy_player,
                   depth - 1,
                   alfa,
                   beta,
                   generateGameBoard(move,
                                     player_,
                                     current_game_board),
                   num_of_moves);
      if (cost.first > alfa) {
        alfa = cost.first;
        best_move = move;
      }
      if (alfa >= beta) {
        break;
      }
    }
    return {alfa, best_move};
  }
}

/**
 * This method checks whether current game board is a final one and no more moves can be done.
 *
 * @param current_game_board State of the current game board.
 * @return Is the current board in final state?
 */
bool Bot::isBoardFinal(uint64_t current_game_board) {
  std::vector<std::vector<unsigned int>> formatted_board(5, std::vector<unsigned int>(5, 0));
  int filled_boxes_counter = 0;
  // push current board to two-dimensional array and check all horizontal and vertical lines at the same time
  std::vector<int> three_in_vertical_lines_counters(5, 1);
  for(int i = 0; i < 5; i++) {
    int three_in_horizontal_line_counter = 1;
    for(int j = 0; j < 5; j++) {
      formatted_board.at(i).at(j) = current_game_board & 3U;
      current_game_board >>= 2;
      // increment filled boxes counter
      if(formatted_board.at(i).at(j) > 0) {
        filled_boxes_counter++;
        // check horizontal line
        if (j > 0) {
          if (formatted_board.at(i).at(j) == formatted_board.at(i).at(j - 1)) {
            three_in_horizontal_line_counter++;
            if (three_in_horizontal_line_counter >= 3) {
              return true;
            }
          } else {
            three_in_horizontal_line_counter = 1;
          }
        }
        // check vertical line
        if (i > 0) {
          if (formatted_board.at(i).at(j) == formatted_board.at(i - 1).at(j)) {
            three_in_vertical_lines_counters.at(j)++;
            if (three_in_vertical_lines_counters.at(j) >= 3) {
              return true;
            }
          } else {
            three_in_vertical_lines_counters.at(j) = 1;
          }
        }
      }
    }
  }

  if(filled_boxes_counter == 25) {
    return true;
  }

  // check all diagonals
  for(int k = 2; k >= 0; k--) {
    int i = 1;
    int three_in_line_counter_lr = 1;
    int three_in_line_counter_rl = 1;
    while(i + k < 5) {
      // check diagonal from left to right
      if(formatted_board.at(i+k).at(i) == formatted_board.at(i+k - 1).at(i - 1) &&
          formatted_board.at(i+k).at(i) > 0) {
        three_in_line_counter_lr++;
        if(three_in_line_counter_lr >= 3) {
          return true;
        }
      } else {
        three_in_line_counter_lr = 1;
      }
      // check diagonal from right to left
      if(formatted_board.at(i+k).at(4-i) == formatted_board.at(i+k - 1).at(5 - i) &&
          formatted_board.at(i+k).at(4-i) > 0) {
        three_in_line_counter_rl++;
        if(three_in_line_counter_rl >= 3) {
          return true;
        }
      } else {
        three_in_line_counter_rl = 1;
      }
      i++;
    }
  }

  // check remaining diagonals
  for(int k = 1; k <= 2; k++) {
    int i = 1;
    int three_in_line_counter_lr = 1;
    int three_in_line_counter_rl = 1;
    while(i + k < 5) {
      // check diagonal from left to right
      if(formatted_board.at(i).at(i + k) == formatted_board.at(i - 1).at(i + k - 1) &&
          formatted_board.at(i).at(i + k) > 0) {
        three_in_line_counter_lr++;
        if(three_in_line_counter_lr >= 3) {
          return true;
        }
      } else {
        three_in_line_counter_lr = 1;
      }
      // check diagonal from right to left
      if(formatted_board.at(i).at(4 - (i + k)) == formatted_board.at(i - 1).at(5 - (i + k)) &&
          formatted_board.at(i).at(4 - (i + k)) > 0) {
        three_in_line_counter_rl++;
        if(three_in_line_counter_rl >= 3) {
          return true;
        }
      } else {
        three_in_line_counter_rl = 1;
      }
      i++;
    }
  }

  return false;
}

/**
 * Heuristic function. It finds amount of twos', threes', fours' and possible fours'
 * on the board for each player and calculates the cost of the current state.
 *
 * Calculating heuristic:
 * This method travels through all rows, columns and almost all diagonals (it skips diagonals of length 2).
 * During this travel it counts amount of the same signs next to each other, all signs count in full line,
 * blank places in line and maximum number of the same signs next to each other.
 * Based on that for bot and enemy it calculates numbers of:
 * two same signs places next to each other,
 * three of four signs placed so that only one sign is remaining to win,
 * number of fours, that a player or bot can place on current board (free lines).
 * It also takes into consideration number of moves needed to achieve current game state.
 * Final cost is calculated by subtracting enemy score from score of the bot.
 *
 * Score is calculated by scaling each number found during search:
 * win/lose : 10000,
 * one remaining to win: 100,
 * two in line: 5,
 * number of fours that can be places by bot/player: 10,
 * already made moves: -20
 *
 * @param current_game_board Current state of the game board.
 * @param num_of_moves Number of already done moves.
 * @return Cost of the current state of the board.
 */
int Bot::heuristic(uint64_t current_game_board, int num_of_moves) const {
//  printBoard(current_game_board);
  int score = 0;
  int enemy_score = 0;
  int two_in_line_count = 0;
  int enemy_two_in_line_count = 0;
  int possible_four_count = 0;
  int enemy_possible_four_count = 0;
  int available_fours_count = 0;
  int enemy_available_fours_count = 0;
  std::vector<std::vector<unsigned int>> board =
      std::vector<std::vector<unsigned int>>(5, std::vector<unsigned int>(5,0));
  // check all horizontal lines for wins/loses
  int max_count = 0;
  int max_enemy_count = 0;
  for(int i = 0; i < 5; i++) {
    // fields for finding 2 in a row
    int current_max_row_count = 0;
    int current_max_enemy_row_count = 0;

    int row_count = 0;
    int full_row_count = 0;
    int enemy_row_count = 0;
    int enemy_full_row_count = 0;

    bool blocked = false;
    bool has_possible_four = false;
    bool enemy_blocked = false;
    bool enemy_has_possible_four = false;

    int range = -1;
    int enemy_range = -1;
    int blank_count = 0;
    for(int j = 0; j < 5; j++) {
      unsigned int current_number = current_game_board & 3U;
      current_game_board >>= 2;
      board.at(i).at(j) = current_number;

      // count row_counts and update max counts
      if(current_number == player_) {
        full_row_count++;
        row_count++;
        if(range == -1)
          range = j;
        // update available fours to place
        if(!blocked && full_row_count + blank_count >= 4 && std::abs(range - j) < 4) {
          available_fours_count++;
        }
        if(current_max_row_count + row_count >= 3 && blank_count == 1 && !blocked)
          has_possible_four = true;

        if(enemy_row_count > current_max_enemy_row_count)
          current_max_enemy_row_count = enemy_row_count;
        if(enemy_row_count == 2)
          enemy_two_in_line_count++;
        if(enemy_row_count > 0 || j > 0)
          enemy_blocked = true;
        enemy_row_count = 0;
      } else if(current_number != 0) {  // enemy
        enemy_full_row_count++;
        enemy_row_count++;
        if(enemy_range == -1)
          enemy_range = j;
        // update available fours to place
        if(!enemy_blocked && enemy_full_row_count + blank_count >= 4 && std::abs(enemy_range - j) < 4) {
          enemy_available_fours_count++;
        }
        if(current_max_enemy_row_count + enemy_row_count >= 3 && blank_count == 1 && !enemy_blocked)
          enemy_has_possible_four = true;

        if(row_count > current_max_row_count)
          current_max_row_count = row_count;
        // update two in line
        if(row_count == 2) {
          two_in_line_count++;
        }
        if(row_count > 0 || j > 0)
          blocked = true;
        row_count = 0;
      } else {  // blank field
        blank_count++;
        
        if(enemy_row_count > current_max_enemy_row_count)
          current_max_enemy_row_count = enemy_row_count;
        if(!enemy_blocked && enemy_full_row_count > 0 && enemy_full_row_count + blank_count >= 4
         && std::abs(enemy_range - j) < 4) {
          enemy_available_fours_count++;
        }
        if(enemy_row_count == 2)
          enemy_two_in_line_count++;
        enemy_row_count = 0;

        if(row_count > current_max_row_count)
          current_max_row_count = row_count;
        if(!blocked && full_row_count > 0 && full_row_count + blank_count >= 4
        && (range - j) < 4) {
          available_fours_count++;
        }
        if(row_count == 2) {
          two_in_line_count++;
        }
        row_count = 0;
      }
    }  // inner loop
    if(row_count > current_max_row_count)
      current_max_row_count = row_count;
    if(enemy_row_count > current_max_enemy_row_count)
      current_max_enemy_row_count = enemy_row_count;

    // max_counts update
    if(current_max_row_count > max_count)
      max_count = current_max_row_count;
    if(current_max_enemy_row_count > max_enemy_count)
      max_enemy_count = current_max_enemy_row_count;

    // update twos' in line
    if(row_count == 2) {
      two_in_line_count++;
    }

    if(has_possible_four)
      possible_four_count++;
    if(enemy_has_possible_four)
      enemy_possible_four_count++;
  }  // outer loop

  // check all vertical lines for win/loses
  for(int i = 0; i < 5; i++) {
    int current_max_column_count = 0;
    int current_enemy_max_column_count = 0;

    int column_count = 0;
    int full_column_count = 0;
    int enemy_column_count = 0;
    int enemy_full_column_count = 0;

    bool blocked = false;
    bool has_possible_four = false;
    bool enemy_blocked = false;
    bool enemy_has_possible_four = false;

    int range = -1;
    int enemy_range = -1;
    int blank_count = 0;
    for(int j = 0; j < 5; j++) {
      unsigned int current_number = board.at(j).at(i);
      // count row_counts and update max counts
      if(current_number == player_) {
        full_column_count++;
        column_count++;
        if(range == -1)
          range = j;
        // update available fours to place
        if(!blocked && full_column_count + blank_count >= 4 && std::abs(range - j) < 4) {
          available_fours_count++;
        }
        if(current_max_column_count + column_count >= 3 && blank_count == 1 && !blocked)
          has_possible_four = true;

        if(enemy_column_count > current_enemy_max_column_count)
          current_enemy_max_column_count = enemy_column_count;
        if(enemy_column_count == 2)
          enemy_two_in_line_count++;
        if(enemy_column_count > 0 || j > 0)
          enemy_blocked = true;
        enemy_column_count = 0;
      } else if(current_number != 0) {
        enemy_full_column_count++;
        enemy_column_count++;
        if(enemy_range == -1)
          enemy_range = j;
        if(!enemy_blocked && enemy_full_column_count + blank_count >= 4 && std::abs(enemy_range - j) < 4) {
          enemy_available_fours_count++;
        }
        if(current_enemy_max_column_count + enemy_column_count >= 3 && blank_count == 1)
          enemy_has_possible_four = true;

        if(column_count > current_max_column_count)
          current_max_column_count = column_count;
        if(column_count == 2)
          two_in_line_count++;
        if(column_count > 0 || j > 0)
          blocked = true;
        column_count = 0;
      } else {
        blank_count++;

        if(enemy_column_count > current_enemy_max_column_count)
          current_enemy_max_column_count = enemy_column_count;
        if(!enemy_blocked && enemy_full_column_count > 0 && enemy_full_column_count + blank_count >= 4
            && std::abs(enemy_range - j) < 4) {
          enemy_available_fours_count++;
        }
        if(enemy_column_count == 2)
          enemy_two_in_line_count++;
        enemy_column_count = 0;

        if(column_count > current_max_column_count)
          current_max_column_count = column_count;
        if(!blocked && full_column_count > 0 && full_column_count + blank_count >= 4
            && std::abs(range - j) < 4) {
          available_fours_count++;
        }
        if(column_count == 2)
          two_in_line_count++;
        column_count = 0;
      }
    }  // inner loop
    if(column_count > current_max_column_count)
      current_max_column_count = column_count;
    if(enemy_column_count > current_enemy_max_column_count)
      current_enemy_max_column_count = enemy_column_count;

    // max_counts update
    if(current_max_column_count > max_count)
      max_count = current_max_column_count;
    if(current_enemy_max_column_count > max_enemy_count)
      max_enemy_count = current_enemy_max_column_count;

    // update twos' in line
    if(column_count == 2)
      two_in_line_count++;
    if(enemy_column_count == 2)
      enemy_two_in_line_count++;

    // add possible fours
    if(has_possible_four)
      possible_four_count++;
    if(enemy_has_possible_four)
      enemy_possible_four_count++;
  }  // outer loop

  // check all diagonals from left and right side of board for win/loses
  for(int k = 2; k >= 0; k--) {
    int i = 0;
    // bot score
    // diagonals from left to right
    int current_max_count_lr = 0;
    int diagonal_count_lr = 0;
    int full_diagonal_count_lr = 0;
    bool blocked_lr = false;
    bool has_possible_four_lr = false;

    // diagonals from right to left
    int current_max_count_rl = 0;
    int diagonal_count_rl = 0;
    int full_diagonal_count_rl = 0;
    bool blocked_rl = false;
    bool has_possible_four_rl = false;

    // enemy score
    // diagonals from left to right
    int current_enemy_max_count_lr = 0;
    int enemy_diagonal_count_lr = 0;
    int enemy_full_diagonal_count_lr = 0;
    bool enemy_blocked_lr = false;
    bool enemy_has_possible_four_lr = false;

    // diagonals from right to left
    int current_enemy_max_count_rl = 0;
    int enemy_diagonal_count_rl = 0;
    int enemy_full_diagonal_count_rl = 0;
    bool enemy_blocked_rl = false;
    bool enemy_has_possible_four_rl = false;

    int range_lr = -1;
    int range_rl = -1;
    int enemy_range_lr = -1;
    int enemy_range_rl = -1;

    int blank_count_lr = 0;
    int blank_count_rl = 0;
    while(i + k < 5) {
      // check diagonals from left to right
      unsigned int current_number = board.at(i+k).at(i);
      if(current_number == player_) {
        full_diagonal_count_lr++;
        diagonal_count_lr++;
        if(range_lr == -1)
          range_lr = i;
        if(!blocked_lr && full_diagonal_count_lr + blank_count_lr >= 4 && std::abs(range_lr - i) < 4) {
          available_fours_count++;
        }
        if(current_max_count_lr + diagonal_count_lr >= 3 && blank_count_lr == 1 && !blocked_lr)
          has_possible_four_lr = true;

        if(enemy_diagonal_count_lr > current_enemy_max_count_lr)
          current_enemy_max_count_lr = enemy_diagonal_count_lr;
        if(enemy_diagonal_count_lr == 2)
          enemy_two_in_line_count++;
        if(enemy_diagonal_count_lr > 0 || i + k > 0)
          enemy_blocked_lr = true;
        enemy_diagonal_count_lr = 0;
      } else if(current_number != 0) {
        enemy_full_diagonal_count_lr++;
        enemy_diagonal_count_lr++;
        if(enemy_range_lr == -1)
          enemy_range_lr = i;
        if(!enemy_blocked_lr && enemy_full_diagonal_count_lr + blank_count_lr >= 4
            && std::abs(enemy_range_lr - i) < 4) {
          enemy_available_fours_count++;
        }
        if(current_enemy_max_count_lr + enemy_diagonal_count_lr >= 3 && blank_count_lr == 1 && !enemy_blocked_lr)
          enemy_has_possible_four_lr = true;

        if(diagonal_count_lr > current_max_count_lr)
          current_max_count_lr = diagonal_count_lr;
        if(diagonal_count_lr == 2)
          two_in_line_count++;
        if(diagonal_count_lr > 0 || i + k > 0)
          blocked_lr = true;
        diagonal_count_lr = 0;
      } else {
        blank_count_lr++;

        if(diagonal_count_lr > current_max_count_lr)
          current_max_count_lr = diagonal_count_lr;
        if(!blocked_lr && full_diagonal_count_lr > 0
            && full_diagonal_count_lr + blank_count_lr >= 4 && std::abs(range_lr - i) < 4) {
          available_fours_count++;
        }
        if(diagonal_count_lr == 2)
          two_in_line_count++;
        diagonal_count_lr = 0;

        if(enemy_diagonal_count_lr > current_enemy_max_count_lr)
          current_enemy_max_count_lr = enemy_diagonal_count_lr;
        if(!enemy_blocked_lr && enemy_full_diagonal_count_lr > 0
            && enemy_full_diagonal_count_lr + blank_count_lr >= 4 && std::abs(enemy_range_lr - i) < 4) {
          enemy_available_fours_count++;
        }
        if(enemy_diagonal_count_lr == 2)
          enemy_two_in_line_count++;
        enemy_diagonal_count_lr = 0;
      }

      // check diagonals from right to left
      current_number = board.at(i + k).at(4-i);
      if(current_number == player_) {
        full_diagonal_count_rl++;
        diagonal_count_rl++;
        if(range_rl == -1)
          range_rl = 4 - i;
        if(!blocked_rl && full_diagonal_count_rl + blank_count_rl >= 4 && std::abs(range_rl - i) < 4) {
          available_fours_count++;
        }
        if(current_max_count_rl + diagonal_count_rl >= 3 && blank_count_rl == 1 && !blocked_rl)
          has_possible_four_rl = true;

        if(enemy_diagonal_count_rl > current_enemy_max_count_rl)
          current_enemy_max_count_rl = enemy_diagonal_count_rl;
        if(enemy_diagonal_count_rl == 2)
          enemy_two_in_line_count++;
        if(enemy_diagonal_count_rl > 0 || i+k > 0)
          enemy_blocked_rl = true;
        enemy_diagonal_count_rl = 0;
      } else if(current_number != 0) {
        enemy_full_diagonal_count_rl++;
        enemy_diagonal_count_rl++;
        if(enemy_range_rl == -1)
          enemy_range_rl = 4 - i;
        if(!enemy_blocked_rl && enemy_full_diagonal_count_rl + blank_count_rl >= 4
            && std::abs(enemy_range_rl - i) < 4) {
          enemy_available_fours_count++;
        }
        if(current_enemy_max_count_rl + enemy_diagonal_count_rl >= 3 && blank_count_rl == 1 && !enemy_blocked_rl)
          enemy_has_possible_four_rl = true;

        if(current_max_count_rl < diagonal_count_rl)
          current_max_count_rl = diagonal_count_rl;
        if(diagonal_count_rl == 2)
          two_in_line_count++;
        if(diagonal_count_rl > 0 || i + k > 0)
          blocked_rl = true;
        diagonal_count_rl = 0;
      } else {
        blank_count_rl++;

        if(diagonal_count_rl > current_max_count_rl)
          current_max_count_rl = diagonal_count_rl;
        if(!blocked_rl && full_diagonal_count_rl > 0 && full_diagonal_count_rl + blank_count_rl >= 4
            && std::abs(range_rl - i) < 4) {
          available_fours_count++;
        }
        if(diagonal_count_rl == 2)
          two_in_line_count++;
        diagonal_count_rl = 0;

        if(enemy_diagonal_count_rl > current_enemy_max_count_rl)
          current_enemy_max_count_rl = enemy_diagonal_count_rl;
        if(!enemy_blocked_rl && enemy_full_diagonal_count_rl > 0
            && enemy_full_diagonal_count_rl + blank_count_rl >= 4 && std::abs(enemy_range_rl - i) < 4) {
          enemy_available_fours_count++;
        }
        if(enemy_diagonal_count_rl == 2)
          enemy_two_in_line_count++;
        enemy_diagonal_count_rl = 0;
      }
      i++;
    }  // inner loop
    if(diagonal_count_rl > current_max_count_rl)
      current_max_count_rl = diagonal_count_rl;
    if(diagonal_count_lr > current_max_count_lr)
      current_max_count_lr = diagonal_count_lr;
    if(enemy_diagonal_count_rl > current_enemy_max_count_rl)
      current_enemy_max_count_rl = enemy_diagonal_count_rl;
    if(enemy_diagonal_count_lr > current_enemy_max_count_lr)
      current_enemy_max_count_lr = enemy_diagonal_count_lr;

    // max_counts update
    if(current_enemy_max_count_lr > max_enemy_count)
      max_enemy_count = current_enemy_max_count_lr;
    if(current_enemy_max_count_rl > max_enemy_count)
      max_enemy_count = current_enemy_max_count_rl;
    if(current_max_count_lr > max_count)
      max_count = current_max_count_lr;
    if(current_max_count_rl > max_count)
      max_count = current_max_count_rl;

    if(diagonal_count_lr == 2)
      two_in_line_count++;
    if(diagonal_count_rl == 2)
      two_in_line_count++;
    if(enemy_diagonal_count_lr == 2)
      enemy_two_in_line_count++;
    if(enemy_diagonal_count_rl == 2)
      enemy_two_in_line_count++;

    // update possible four's count
    if(has_possible_four_rl)
      possible_four_count++;
    if(has_possible_four_lr)
      possible_four_count++;
    if(enemy_has_possible_four_rl)
      enemy_possible_four_count++;
    if(enemy_has_possible_four_lr)
      enemy_possible_four_count++;
  }

  // check rest of the diagonals from top side of board
  for(int k = 1; k <= 2; k++) {
    int i = 0;
    // bot score
    // diagonals from left to right
    int current_max_count_lr = 0;
    int diagonal_count_lr = 0;
    int full_diagonal_count_lr = 0;
    bool blocked_lr = false;
    bool has_possible_four_lr = false;

    // diagonals from right to left
    int current_max_count_rl = 0;
    int diagonal_count_rl = 0;
    int full_diagonal_count_rl = 0;
    bool blocked_rl = false;
    bool has_possible_four_rl = false;

    // enemy score
    // diagonals from left to right
    int current_enemy_max_count_lr = 0;
    int enemy_diagonal_count_lr = 0;
    int enemy_full_diagonal_count_lr = 0;
    bool enemy_blocked_lr = false;
    bool enemy_has_possible_four_lr = false;

    // diagonals from right to left
    int current_enemy_max_count_rl = 0;
    int enemy_diagonal_count_rl = 0;
    int enemy_full_diagonal_count_rl = 0;
    bool enemy_blocked_rl = false;
    bool enemy_has_possible_four_rl = false;

    int range_lr = -1;
    int range_rl = -1;
    int enemy_range_lr = -1;
    int enemy_range_rl = -1;

    int blank_count_lr = 0;
    int blank_count_rl = 0;
    while(i + k < 5) {
      // check diagonals from left to right
      unsigned int current_number = board.at(i).at(i+k);
      if(current_number == player_) {
        full_diagonal_count_lr++;
        diagonal_count_lr++;
        if(range_lr == -1)
          range_lr = i;
        if(!blocked_lr && full_diagonal_count_lr + blank_count_lr >= 4 && std::abs(range_lr - i) < 4) {
          available_fours_count++;
        }
        if(current_max_count_lr + diagonal_count_lr >= 3 && blank_count_lr == 1 && !blocked_lr)
          has_possible_four_lr = true;

        if(enemy_diagonal_count_lr > current_enemy_max_count_lr)
          current_enemy_max_count_lr = enemy_diagonal_count_lr;
        if(enemy_diagonal_count_lr == 2)
          enemy_two_in_line_count++;
        enemy_blocked_lr = true;
        enemy_diagonal_count_lr = 0;
      } else if(current_number != 0) {
        enemy_full_diagonal_count_lr++;
        enemy_diagonal_count_lr++;
        if(enemy_range_lr == -1)
          enemy_range_lr = i;
        if(!enemy_blocked_lr && enemy_full_diagonal_count_lr + blank_count_lr >= 4
            && std::abs(enemy_range_lr - i) < 4) {
          enemy_available_fours_count++;
        }
        if(current_enemy_max_count_lr + enemy_diagonal_count_lr >= 3 && blank_count_lr == 1 && !enemy_blocked_lr)
          enemy_has_possible_four_lr = true;

        if(diagonal_count_lr > current_max_count_lr)
          current_max_count_lr = diagonal_count_lr;
        if(diagonal_count_lr == 2)
          two_in_line_count++;
        blocked_lr = true;
        diagonal_count_lr = 0;
      } else {
        blank_count_lr++;

        if(diagonal_count_lr > current_max_count_lr)
          current_max_count_lr = diagonal_count_lr;
        if(!blocked_lr && full_diagonal_count_lr > 0
            && full_diagonal_count_lr + blank_count_lr >= 4 && std::abs(range_lr - i) < 4) {
          available_fours_count++;
        }
        if(diagonal_count_lr == 2)
          two_in_line_count++;
        diagonal_count_lr = 0;

        if(enemy_diagonal_count_lr > current_enemy_max_count_lr)
          current_enemy_max_count_lr = enemy_diagonal_count_lr;
        if(!enemy_blocked_lr && enemy_full_diagonal_count_lr > 0
            && enemy_full_diagonal_count_lr + blank_count_lr >= 4 && std::abs(enemy_range_lr - i) < 4) {
          enemy_available_fours_count++;
        }
        if(enemy_diagonal_count_lr == 2)
          enemy_two_in_line_count++;
        enemy_diagonal_count_lr = 0;
      }

      // check diagonals from right to left
      current_number = board.at(i).at(4-(i + k));
      if(current_number == player_) {
        full_diagonal_count_rl++;
        diagonal_count_rl++;
        if(range_rl == -1)
          range_rl = i;
        if(!blocked_rl && full_diagonal_count_rl + blank_count_rl >= 4 && std::abs(range_rl - i) < 4) {
          available_fours_count++;
        }
        if(current_max_count_rl + diagonal_count_rl >= 3 && blank_count_rl == 1 && !blocked_rl)
          has_possible_four_rl = true;

        if(enemy_diagonal_count_rl > current_enemy_max_count_rl)
          current_enemy_max_count_rl = enemy_diagonal_count_rl;
        if(enemy_diagonal_count_rl == 2)
          enemy_two_in_line_count++;
        enemy_blocked_rl = true;
        enemy_diagonal_count_rl = 0;
      } else if(current_number != 0) {
        enemy_full_diagonal_count_rl++;
        enemy_diagonal_count_rl++;
        if(enemy_range_rl == -1)
          enemy_range_rl = i;
        if(!enemy_blocked_rl && enemy_full_diagonal_count_rl + blank_count_rl >= 4
            && std::abs(enemy_range_rl - i) < 4) {
          enemy_available_fours_count++;
        }
        if(current_enemy_max_count_rl + enemy_diagonal_count_rl >= 3 && blank_count_rl == 1 && !enemy_blocked_rl)
          enemy_has_possible_four_rl = true;

        if(current_max_count_rl < diagonal_count_rl)
          current_max_count_rl = diagonal_count_rl;
        if(diagonal_count_rl == 2)
          two_in_line_count++;
        blocked_rl = true;
        diagonal_count_rl = 0;
      } else {
        blank_count_rl++;

        if(diagonal_count_rl > current_max_count_rl)
          current_max_count_rl = diagonal_count_rl;
        if(!blocked_rl && full_diagonal_count_rl > 0
            && full_diagonal_count_rl + blank_count_rl >= 4 && std::abs(range_rl - i) < 4) {
          available_fours_count++;
        }
        if(diagonal_count_rl == 2)
          two_in_line_count++;
        diagonal_count_rl = 0;

        if(enemy_diagonal_count_rl > current_enemy_max_count_rl)
          current_enemy_max_count_rl = enemy_diagonal_count_rl;
        if(!enemy_blocked_rl && enemy_full_diagonal_count_rl > 0
            && enemy_full_diagonal_count_rl + blank_count_rl >= 4 && std::abs(enemy_range_rl - i) < 4) {
          enemy_available_fours_count++;
        }
        if(enemy_diagonal_count_rl == 2)
          enemy_two_in_line_count++;
        enemy_diagonal_count_rl = 0;
      }
      i++;
    }  // inner loop
    if(diagonal_count_rl > current_max_count_rl)
      current_max_count_rl = diagonal_count_rl;
    if(diagonal_count_lr > current_max_count_lr)
      current_max_count_lr = diagonal_count_lr;
    if(enemy_diagonal_count_rl > current_enemy_max_count_rl)
      current_enemy_max_count_rl = enemy_diagonal_count_rl;
    if(enemy_diagonal_count_lr > current_enemy_max_count_lr)
      current_enemy_max_count_lr = enemy_diagonal_count_lr;

    // max_counts update
    if(current_enemy_max_count_lr > max_enemy_count)
      max_enemy_count = current_enemy_max_count_lr;
    if(current_enemy_max_count_rl > max_enemy_count)
      max_enemy_count = current_enemy_max_count_rl;
    if(current_max_count_lr > max_count)
      max_count = current_max_count_lr;
    if(current_max_count_rl > max_count)
      max_count = current_max_count_rl;

    // update twos' in line
    if(diagonal_count_rl == 2)
      two_in_line_count++;
    if(diagonal_count_lr == 2)
      two_in_line_count++;
    if(enemy_diagonal_count_lr == 2)
      two_in_line_count++;
    if(enemy_diagonal_count_rl == 2)
      two_in_line_count++;

    // update possible four's count
    if(has_possible_four_rl)
      possible_four_count++;
    if(has_possible_four_lr)
      possible_four_count++;
    if(enemy_has_possible_four_rl)
      enemy_possible_four_count++;
    if(enemy_has_possible_four_lr)
      enemy_possible_four_count++;
  }

  // update score for wins/loses
  if(max_count == 4 || max_enemy_count == 3) {
    score += 10000;
  } if(max_count == 3 || max_enemy_count == 4) {
    enemy_score += 10000;
  }

  // update score for possible fours
  score += possible_four_count * 100;
  enemy_score += enemy_possible_four_count * 100;

  // update score for all two's in a line
  score += two_in_line_count * 5;
  enemy_score += enemy_two_in_line_count * 5;

  // update available fours to place
  score += available_fours_count * 10;
  enemy_score += enemy_available_fours_count * 10;

  // update move costs
  score -= (num_of_moves * 20);
  enemy_score -= (num_of_moves * 20);
  return score - enemy_score;
}

/**
 * This method creates a list of all fields that are empty.
 *
 * @param current_game_board Current state of the game board.
 * @return List of available fields on the board.
 */
std::vector<int> Bot::getAvailableMoves(uint64_t current_game_board) {
  std::vector<int> available_moves;
  for(int i = 1; i <= 5; i++) {
    int move = i * 10 + 1;
    for(int j = 0; j < 5; j++) {
      if(!(current_game_board & 3))
        available_moves.push_back(move);
      move++;
      current_game_board >>= 2;
    }
  }
  return available_moves;
}

/**
 * Method used to print current game board.
 */
void Bot::printBoard() const {
  uint64_t board = game_board_;
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      std::cout << (board & 3) << " ";
      board >>= 2;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

/**
 * Method used to print given game board.
 *
 * @param board Game board to be printed.
 */
void Bot::printBoard(uint64_t board) {
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      std::cout << (board & 3) << " ";
      board >>= 2;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

}  // namespace bot
