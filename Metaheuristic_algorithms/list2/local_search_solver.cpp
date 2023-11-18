#include "inc/local_search_solver.h"

/**
 * Constructor. Initializes all fields.
 *
 * @TODO(Jakub Drzewiecki): Missing params
 * @param mst
 */
LocalSearchSolver::LocalSearchSolver(std::shared_ptr<Graph> graph,
                                     std::vector<int> cycle,
                                     size_t cycle_cost) {
  graph_ = graph;
  n_ = graph_->size();
  cycle_ = cycle;
  cycle_cost_ = cycle_cost;
}

/**
 * Get result cycle cost.
 *
 * @return Result cycle cost.
 */
size_t LocalSearchSolver::getCycleCost() const {
  return cycle_cost_;
}

/**
 * Get number of iterations done by algorithm.
 *
 * @return Number of iterations.
 */
size_t LocalSearchSolver::getStepsCounter() const {
  return steps_counter_;
}

/**
 * Get result cycle.
 *
 * @return Array representing a cycle.
 */
std::vector<int> LocalSearchSolver::getCycle() const {
  return cycle_;
}

/**
 * Main pipeline of local search algorithm.
 */
void LocalSearchSolver::localSearch() {
  bool found_better_solution = true;
  while(found_better_solution) {
    found_better_solution = false;
    std::pair<int, int> best_pair;
    size_t best_cost = cycle_cost_;
    // evaluate costs for all neighbouring states
    for (int i = 0; i < graph_->size() - 1; i++) {
      for (int j = i + 1; j < graph_->size(); j++) {
        if (i == 0 && j == graph_->size() - 1)
          continue;
        size_t new_cost = calculateNewCycleCost(i, j);
        if(new_cost < best_cost) {
          best_cost = new_cost;
          best_pair = {i, j};
        }
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

/**
 * This method calculates new cycle cost after inverting all vertices from start_vert to end_vert.
 * After inverting all vertices from start_vert to end_vert, it is needed only to subtract
 * costs of edges (start_vert - 1, start_vert) and (end_vert, end_vert + 1) from current cycle cost.
 * Rest of the costs does not change. Then add (start_vert - 1, end_vert) and (start_vert, end_vert + 1),
 * which gives cost of new cycle.
 * @param start_ind Start index of invert in given cycle
 * @param end_ind End index of invert in given cycle.
 * @return Cost of new cycle.
 */
size_t LocalSearchSolver::calculateNewCycleCost(int start_ind, int end_ind) {
  size_t new_cost = cycle_cost_;
  int prev_start_ind = start_ind - 1;
  if(prev_start_ind < 0)
    prev_start_ind += n_;
  int next_end_ind = end_ind + 1;
  if(next_end_ind == n_)
    next_end_ind -= n_;
  int start_vertex = cycle_.at(start_ind);
  int prev_start_vertex = cycle_.at(prev_start_ind);
  int end_vertex = cycle_.at(end_ind);
  int next_end_vertex = cycle_.at(next_end_ind);
  new_cost -= graph_->at(prev_start_vertex).at(start_vertex);
  new_cost -= graph_->at(end_vertex).at(next_end_vertex);
  new_cost += graph_->at(prev_start_vertex).at(end_vertex);
  new_cost += graph_->at(start_vertex).at(next_end_vertex);
  return new_cost;
}

/**
 * Invert all elements in cycle between given indexes.
 *
 * @param start_vert Start index.
 * @param end_vert End index.
 */
void LocalSearchSolver::invertCycle(int start_vert, int end_vert) {
  while(start_vert < end_vert) {
    std::swap(cycle_.at(start_vert), cycle_.at(end_vert));
    start_vert++;
    end_vert--;
  }
}
