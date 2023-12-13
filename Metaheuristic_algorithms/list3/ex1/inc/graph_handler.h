#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST2_GRAPH_HANDLER_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST2_GRAPH_HANDLER_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <cmath>
#include <memory>

/**
 * Graph structure
 */
typedef std::unordered_map<int, std::unordered_map<int, int>> Graph;

/**
 * Graph handler class.
 * It reads file given to constructor, creates graph using this file
 * and automatically calculates mst for it.
 */
class GraphHandler {
 public:
  GraphHandler(std::string file_name);
  size_t getMstCost() const;
  std::shared_ptr<Graph> getMst() const;
  std::shared_ptr<Graph> getGraph() const;

 private:
  int euc_2d(const std::pair<int, int>& l, const std::pair<int, int>& r);
  void readFile(std::string file_name);
  void primMst(int source);
  std::size_t calculateMstCost();

  std::shared_ptr<Graph> graph_ = std::make_shared<Graph>();
  std::shared_ptr<Graph> mst_ = std::make_shared<Graph>();
  size_t mst_cost_;
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST2_GRAPH_HANDLER_H_