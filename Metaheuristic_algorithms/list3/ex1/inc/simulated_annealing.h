#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST3_EX1_SIMULATED_ANNEALING_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST3_EX1_SIMULATED_ANNEALING_H_

#include "cycle_creator.h"

class SimulatedAnnealing {
 public:
  SimulatedAnnealing(int temperature,
                     double temperature_scale,
                     int epoch_size,
                     int max_epoch_count,
                     size_t max_no_result_change_count,
                     std::shared_ptr<Graph> graph,
                     std::shared_ptr<CycleCreator> cycle_creator);
  void simulate();
  size_t result() const;

 private:
  std::shared_ptr<Graph> graph_;
  std::shared_ptr<CycleCreator> cycle_creator_;
  std::vector<std::pair<int, int>> neighbourhood_;
  std::vector<int> best_cycle_;
  size_t best_result_;

  int temperature_;
  double temperature_scale_;
  int epoch_size_;
  int max_epoch_count_;
  size_t max_no_result_change_count_;

  std::mt19937_64 rand_gen_{std::random_device{}()};

  size_t calculateNewCycleCost(int start_ind, int end_ind, size_t curr_cost, std::vector<int> curr_cycle);
  void invertCycle(int start_vert, int end_vert, std::vector<int> &curr_cycle);
  double boltzmannDist(size_t curr_cycle_cost, size_t new_cycle_cost);
};

inline double SimulatedAnnealing::boltzmannDist(size_t curr_cycle_cost, size_t new_cycle_cost) {
  double curr_cost = static_cast<double>(curr_cycle_cost);
  double new_cost = static_cast<long long int>(new_cycle_cost);
  double diff = curr_cost - new_cost;
  return std::exp(diff / temperature_);
}

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST3_EX1_SIMULATED_ANNEALING_H_
