#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST2_CYCLE_CREATOR_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST2_CYCLE_CREATOR_H_

#include <algorithm>
#include "graph_handler.h"

/**
 * Cycle creator class. It handles creation of cycles
 * using given mst and graph.
 * It can also create random cycles.
 */
class CycleCreator {
 public:
  CycleCreator(std::shared_ptr<Graph> mst, std::shared_ptr<Graph> graph);
  void createCycle(int source);
  std::vector<int> getCycle() const;
  size_t getCycleCost() const;

  static std::vector<int> createRandomCycle(int cycle_size, std::mt19937_64 & generator);

 private:
  std::shared_ptr<Graph> mst_;
  std::shared_ptr<Graph> graph_;
  std::vector<int> cycle_;
  size_t cycle_cost_;

  size_t calculateCycleCost();
  void createCycle(int curr_vert, std::vector<int> & cycle, std::vector<bool> & visited);
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST2_CYCLE_CREATOR_H_
