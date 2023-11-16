#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST2_LOCAL_SEARCH_SOLVER_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST2_LOCAL_SEARCH_SOLVER_H_

#include "cycle_creator.h"

/**
 * Local search solver class.
 * It implements local search algorithm and saves results.
 */
class LocalSearchSolver {
 public:
  LocalSearchSolver(std::shared_ptr<Graph> graph,
                    std::vector<int> cycle,
                    size_t cycle_cost);
  size_t getCycleCost() const;
  size_t getStepsCounter() const;

 private:
  std::shared_ptr<Graph> graph_;
  size_t n_;
  size_t cycle_cost_;
  std::vector<int> cycle_;

  size_t steps_counter_ = 0;

  // local search functions
  void localSearch();
  size_t calculateNewCycleCost(int start_ind, int end_ind);
  void invertCycle(int start_vert, int end_vert);
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST2_LOCAL_SEARCH_SOLVER_H_
