#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST3_EX1_SIMULATED_ANNEALING_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST3_EX1_SIMULATED_ANNEALING_H_

#include "cycle_creator.h"

class SimulatedAnnealing {
 public:
  SimulatedAnnealing(int temperature,
                     double temperature_scale,
                     int epoch_size,
                     int max_epoch_count,
                     std::shared_ptr<Graph> graph,
                     std::shared_ptr<CycleCreator> cycle_creator);

 private:
  std::shared_ptr<Graph> graph_;
  std::shared_ptr<CycleCreator> cycle_creator_;

  int temperature_;
  double temperature_scale_;
  int epoch_size_;
  int max_epoch_count_;
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST3_EX1_SIMULATED_ANNEALING_H_
