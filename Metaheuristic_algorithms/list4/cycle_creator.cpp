#include "inc/cycle_creator.h"

/**
 * Constructor, it saves pointers to graph and mst.
 *
 * @param graph Graph loaded from file.
 */
CycleCreator::CycleCreator(std::shared_ptr<Graph> graph) {
  graph_ = graph;
}

/**
 * Create cycle based on given MST by travelling it using DFS algorithm.
 * Cycle is created by pushing vertices to an array when they are visited for the first time.
 *
 * @return Array that indicates a cycle.
 */
std::vector<int> CycleCreator::createRandomCycle() {
  std::vector<int> start_cycle(graph_->size());
  for(int i = 0; i < graph_->size(); i++) {
    start_cycle.at(i) = i;
  }
  std::shuffle(start_cycle.begin(), start_cycle.end(), random_generator_);
  return start_cycle;
}

/**
 * Calculate the cost to travel created cycle.
 *
 * @return Cost of travelling the cycle.
 */
size_t CycleCreator::calculateCycleCost(std::vector<int> & cycle) {
  std::size_t cost = 0;
  for(std::size_t i = 0; i < cycle.size() - 1; i++) {
    cost += graph_->at(cycle.at(i)).at(cycle.at(i+1));
  }
  cost += graph_->at(cycle.at(cycle.size() - 1)).at(cycle.at(0));
  return cost;
}
