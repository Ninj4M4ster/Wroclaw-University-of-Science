#include "inc/simulated_annealing.h"

SimulatedAnnealing::SimulatedAnnealing(int temperature,
                                       double temperature_scale,
                                       int epoch_size,
                                       int max_epoch_count,
                                       std::shared_ptr<Graph> graph,
                                       std::shared_ptr<CycleCreator> cycle_creator) {
  temperature_ = temperature;
  temperature_scale_ = temperature_scale;
  epoch_size_ = epoch_size;
  max_epoch_count_ = max_epoch_count;
  graph_ = graph;
  cycle_creator_ = cycle_creator;
}