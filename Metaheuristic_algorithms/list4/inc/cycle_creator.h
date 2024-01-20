#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST4_CYCLE_CREATOR_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST4_CYCLE_CREATOR_H_

#include <algorithm>
#include <random>
#include "graph_handler.h"

/**
 * Cycle creator class. It handles creation of cycles
 * using given mst and graph.
 * It can also create random cycles.
 */
class CycleCreator {
 public:
  CycleCreator(std::shared_ptr<Graph> graph);
  std::vector<int> createRandomCycle();

  static size_t calculateCycleCost(std::vector<int> & cycle, std::shared_ptr<Graph> graph);

 private:
  std::shared_ptr<Graph> graph_;
  std::mt19937_64 random_generator_{std::random_device{}()};
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST4_CYCLE_CREATOR_H_
