#include "inc/modified_local_search_solver.h"

/**
 * Constructor, initializes base class.
 *
 * @param graph
 * @param cycle
 * @param cycle_cost
 * @param rand_gen
 */
ModifiedLocalSearchSolver::ModifiedLocalSearchSolver(std::shared_ptr<Graph> graph,
                                                     std::vector<int> cycle,
                                                     size_t cycle_cost,
                                                     std::mt19937_64 &rand_gen)
                                                     : LocalSearchSolver(graph, cycle, cycle_cost) {
  rand_gen_ = rand_gen;
  // create array of all possibilities
  for (int i = 0; i < n_ - 1; i++) {
    for (int j = i + 1; j < n_; j++) {
      if (i == 0 && j == n_ - 1)
        continue;
      possible_neighbours_.push_back({i, j});
    }
  }
}

/**
 * Main pipeline of modified local search algorithm.
 */
void ModifiedLocalSearchSolver::localSearch() {
  bool found_better_solution = true;
  while(found_better_solution) {
    found_better_solution = false;
    std::pair<int, int> best_pair;
    size_t best_cost = cycle_cost_;
    // evaluate costs for n random neighbours
    std::shuffle(possible_neighbours_.begin(), possible_neighbours_.end(), rand_gen_);
    for(int i = 0; i < n_; i++) {
      auto curr_pair = possible_neighbours_.at(i);
      size_t new_cost = calculateNewCycleCost(curr_pair.first, curr_pair.second);
      if(new_cost < best_cost) {
        best_cost = new_cost;
        best_pair = curr_pair;
      }
    }
    // if best_cost < cycle_cost_, update cycle
    if(best_cost < cycle_cost_) {
      invertCycle(best_pair.first, best_pair.second);
      cycle_cost_ = best_cost;
      steps_counter_++;
      found_better_solution = true;
    }
    // for large graphs, stop after 100 iterations
    if(n_ > 1000 && steps_counter_ >= 100)
      found_better_solution = false;
  }
}