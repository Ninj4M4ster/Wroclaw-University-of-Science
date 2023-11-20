#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST2_MODIFIED_LOCAL_SEARCH_SOLVER_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST2_MODIFIED_LOCAL_SEARCH_SOLVER_H_

#include <random>
#include "local_search_solver.h"

class ModifiedLocalSearchSolver : public LocalSearchSolver {
 public:
  explicit ModifiedLocalSearchSolver(std::shared_ptr<Graph> graph,
                            std::vector<int> cycle,
                            size_t cycle_cost,
                            std::mt19937_64 & rand_gen);
  void localSearch() override;
 private:
  std::mt19937_64 rand_gen_;
  std::vector<std::pair<int, int>> possible_neighbours_;
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST2_MODIFIED_LOCAL_SEARCH_SOLVER_H_
