#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_DISCRETE_OPTIMIZATION_ALGORITHMS_LIST4_EX1_GEN_GRAPH_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_DISCRETE_OPTIMIZATION_ALGORITHMS_LIST4_EX1_GEN_GRAPH_H_

#include <iostream>
#include <vector>
#include <bit>
#include <math.h>
#include <random>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>

inline unsigned int hammingDist(unsigned int x) {
  return std::__popcount(x);
}

typedef std::vector<std::unordered_map<unsigned int, unsigned int>> Cube;

Cube genCube(int size) {
  std::mt19937 rand_gen{std::random_device{}()};

  size = std::pow(2, size);
  Cube cube(size, std::unordered_map<unsigned int, unsigned int>());
  for(unsigned int i = 0; i < size - 1; i++) {
    for(unsigned int j = i + 1; j < size; j++) {
      if(hammingDist(i ^ j) == 1) {
        unsigned int max_pow =
            std::max(
                std::max(hammingDist(i), hammingDist(j)),
                std::max(hammingDist(~i), hammingDist(~j)
                ));
        std::uniform_int_distribution<unsigned int> distribution {1, (unsigned int) std::pow(2, max_pow)};
        unsigned int max_flow = distribution(rand_gen);

        if(hammingDist(i) < hammingDist(j)) {
          cube.at(i)[j] = max_flow;
        } else {
          cube.at(j)[i] = max_flow;
        }
      }
    }
  }
  return cube;
}

std::vector<unsigned int> BFS(
    Cube & cube,
    std::vector<std::unordered_map<unsigned int, long long>> & flow,
    unsigned int source,
    unsigned int target) {
  std::queue<unsigned int> Q;
  std::vector<unsigned int> prev(cube.size());
  std::vector<unsigned int> dist(cube.size(), std::numeric_limits<unsigned int>::max());
  Q.push(source);
  dist.at(source) = 0;

  bool path_found = false;

  while(!Q.empty()) {
    unsigned int curr_vert = Q.front();
    Q.pop();

    for(auto & pair : cube.at(curr_vert)) {
      if(dist.at(pair.first) > dist.at(curr_vert) + 1 &&
          pair.second - flow.at(curr_vert)[pair.first] > 0) {
        dist.at(pair.first) = dist.at(curr_vert) + 1;
        prev.at(pair.first) = curr_vert;

        Q.push(pair.first);
        if(pair.first == target) {
          path_found = true;
          break;
        }
      }
    }
    if(path_found)
      break;
  }
  if(!path_found)
    return {};

  std::vector<unsigned int> path;
  unsigned int curr = target;
  path.push_back(curr);
  while(curr != source) {
    curr = prev.at(curr);
    path.push_back(curr);
  }

  std::reverse(path.begin(), path.end());
  return path;
}

inline long long findMinFlow(std::vector<unsigned int> & path,
                         Cube & cube,
                         std::vector<std::unordered_map<unsigned int, long long>> & flow) {
  long long min_flow = std::numeric_limits<unsigned int>::max();
  for(int i = 0; i < path.size() - 1; i++) {
    unsigned int start = path.at(i);
    unsigned int end = path.at(i+1);
    min_flow = std::min(min_flow, cube.at(start)[end] - flow.at(start)[end]);
  }
  return min_flow;
}

std::vector<std::unordered_map<unsigned int, long long>>
edmondsKarp(Cube & cube, unsigned int source, unsigned int target) {
  std::vector<std::unordered_map<unsigned int, long long>> flow(
      cube.size(),
      std::unordered_map<unsigned int, long long>());

  for(int i = 0; i < cube.size(); i++) {
    for(auto & pair : cube.at(i)) {
      flow.at(i)[pair.first] = 0;
      flow.at(pair.first)[i] = 0;
    }
  }

  bool path_exists = true;
  while(path_exists) {
    std::vector<unsigned int> path = BFS(cube, flow, source, target);
    if(path.empty()) {
      path_exists = false;
    } else {
      // find min flow at the path
      long long min_flow = findMinFlow(path, cube, flow);
      for(int i = 0; i < path.size() - 1; i++) {  // update flows and residual graph
        flow.at(path.at(i))[path.at(i+1)] += min_flow;
        flow.at(path.at(i+1))[path.at(i)] -= min_flow;
      }
    }
  }

  return flow;
}

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_DISCRETE_OPTIMIZATION_ALGORITHMS_LIST4_EX1_GEN_GRAPH_H_
