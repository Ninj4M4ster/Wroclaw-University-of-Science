#include "inc/cycle_creator.h"

/**
 * Constructor, it saves pointers to graph and mst.
 *
 * @param mst Mst created on given graph.
 * @param graph Graph loaded from file.
 */
CycleCreator::CycleCreator(std::shared_ptr<Graph> mst, std::shared_ptr<Graph> graph) {
  mst_ = mst;
  graph_ = graph;
}

/**
 * Find MST in given graph using dfs algorithm.
 * This is main dfs pipeline.
 * Based on order of visited vertices, cycle is created.
 *
 * @param curr_vert Current vertex
 * @param cycle Array in which cycle is created
 * @param visited Array indicating if given vertex has been already visited.
 */
void CycleCreator::createCycle(int curr_vert, std::vector<int> & cycle, std::vector<bool> & visited) {
  visited.at(curr_vert) = true;
  cycle.push_back(curr_vert);
  for(auto & pair : mst_->at(curr_vert)) {
    if(!visited.at(pair.first)) {
      createCycle(pair.first, cycle, visited);
    }
  }
}

/**
 * Create cycle based on given MST by travelling it using DFS algorithm.
 * Cycle is created by pushing vertices to an array when they are visited for the first time.
 *
 * @param source Starting vertex.
 * @return Array that indicates a cycle.
 */
void CycleCreator::createCycle(int source) {
  std::vector<bool> visited(graph_->size(), false);
  std::vector<int> cycle;
  createCycle(source, cycle, visited);
  cycle_ = cycle;
  cycle_cost_ = calculateCycleCost(cycle_, graph_);
}

/**
 * Calculate the cost to travel created cycle.
 *
 * @return Cost of travelling the cycle.
 */
size_t CycleCreator::calculateCycleCost(std::vector<int> & cycle, std::shared_ptr<Graph> graph) {
  std::size_t cost = 0;
  for(std::size_t i = 0; i < cycle.size() - 1; i++) {
    cost += graph->at(cycle.at(i)).at(cycle.at(i+1));
  }
  cost += graph->at(cycle.at(cycle.size() - 1)).at(cycle.at(0));
  return cost;
}

/**
 * @brief Return created cycle.
 * @return Created cycle.
 */
std::vector<int> CycleCreator::getCycle() const {
  return cycle_;
}

/**
 * @brief Return cost of created cycle.
 * @return Cost of created cycle.
 */
size_t CycleCreator::getCycleCost() const {
  return cycle_cost_;
}