/**
 * Jakub Drzewiecki
 * 268418
 * Bot class.
 */

#ifndef AI_LIST2_BOT_BOT_HPP_
#define AI_LIST2_BOT_BOT_HPP_

#include <iostream>
#include <vector>
#include <unordered_map>

namespace bot {

class Bot {
 private:
  int depth_;
  int player_;
  uint64_t game_board_ = 0;

  static uint64_t generateGameBoard(int move, int playerNumber, uint64_t current_game_board);
  std::pair<int, int> alfaBeta(int playerNumber,
               int depth,
               int alfa,
               int beta,
               uint64_t current_game_board,
               int num_of_moves);
  static bool isBoardFinal(uint64_t current_game_board);
  int heuristic(uint64_t current_game_board, int num_of_moves) const;
  static std::vector<int> getAvailableMoves(uint64_t current_game_board);
  static void printBoard(uint64_t board);
 public:
  explicit Bot(int depth, int player);
  void makeMove(int move, int playerNumber);
  int findBestMove(int playerNumber);
  void printBoard() const;
};

}  // namespace bot

#endif //AI_LIST2_BOT_BOT_HPP_
