#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_DISCRETE_OPTIMIZATION_ALGORITHMS_LIST4_EX2_UTILS_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_DISCRETE_OPTIMIZATION_ALGORITHMS_LIST4_EX2_UTILS_H_

#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include <algorithm>
#include <unordered_map>

typedef std::vector<std::unordered_map<unsigned int, unsigned int>> Graph;

Graph genGraph(unsigned int size, unsigned int neighbours_count) {
  if(size > 31)
    throw std::runtime_error("Max graph size is 31");
  size = std::pow(2, size + 1);
  Graph graph(size + 2, std::unordered_map<unsigned int, unsigned int>());

  std::mt19937 rand_gen{std::random_device{}()};
  std::uniform_int_distribution<unsigned int> distribution{(size / 2) + 1, size};

  for(unsigned int i = 1; i <= (size / 2); i++) {
    graph.at(0)[i] = 1;  // source node connected to
    for(int j = 0; j < neighbours_count; j++) {
      unsigned int neighbour = distribution(rand_gen);
      // check if neighbour is not already connected
      auto f = graph.at(i).find(neighbour);
      if(f == graph.at(i).end()) {
        graph.at(i)[neighbour] = 1;
      }
    }
  }

  for(unsigned int i = (size / 2) + 1; i < size + 1; i++) {
    graph.at(i)[size + 1] = 1;
  }

  return graph;
}

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_DISCRETE_OPTIMIZATION_ALGORITHMS_LIST4_EX2_UTILS_H_
