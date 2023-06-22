#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_DISCRETE_OPTIMIZATION_ALGORITHMS_LIST4_EX4_DYNIC_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_DISCRETE_OPTIMIZATION_ALGORITHMS_LIST4_EX4_DYNIC_H_

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

typedef std::vector<std::unordered_map<unsigned int, long long>> Flow;

typedef std::vector<std::vector<unsigned int>> Graph;

Graph BFS(Cube & cube,
         Flow & flow,
         unsigned int source) {
  std::queue<unsigned int> Q;
  Graph back_track(cube.size());
  Q.push(source);
  std::vector<unsigned int> dist(cube.size(), std::numeric_limits<unsigned int>::max());
  dist.at(source) = 0;

  while(!Q.empty()) {
    unsigned int curr_ver = Q.front();
    Q.pop();
    for(auto & nei : cube.at(curr_ver)) {
      if(dist.at(nei.first) > dist.at(curr_ver) + 1 &&
          nei.second - flow.at(curr_ver)[nei.first] > 0) {
        dist.at(nei.first) = dist.at(curr_ver) + 1;
        back_track.at(nei.first).push_back(curr_ver);
        Q.push(nei.first);
      }
    }
  }

  return back_track;
}

long long DFS(Cube & cube,
              Flow & flow,
              Graph & paths,
              unsigned int curr_node,
              unsigned int source,
              long long curr_flow) {
  if(curr_flow == 0)
    return 0;
  if(source == curr_node)
    return curr_flow;
  for(auto & nei : paths.at(curr_node)) {
    if(cube.at(nei)[curr_node] - flow.at(nei)[curr_node] == 0)
      continue;
    long long new_flow = DFS(cube,
                             flow,
                             paths,
                             nei,
                             source,
                             std::min(curr_flow, cube.at(nei)[curr_node] - flow.at(nei)[curr_node]));
    if(new_flow == 0)
      continue;
    flow.at(nei)[curr_node] += new_flow;
    flow.at(curr_node)[nei] -= new_flow;
    return new_flow;
  }
  return 0;
}

Flow dinic(
    Cube & cube,
    unsigned int source,
    unsigned int target) {
  Flow flow(cube.size(), std::unordered_map<unsigned int, long long>());

  for(int i = 0; i < cube.size(); i++) {
    for(auto & pair : cube.at(i)) {
      flow.at(i)[pair.first] = 0;
      flow.at(pair.first)[i] = 0;
    }
  }

  while(true) {
    Graph back_paths = BFS(cube, flow, source);
    if(back_paths.at(target).empty()) {
      break;
    }
    DFS(cube, flow, back_paths, target, source, std::numeric_limits<long long>::max());
  }

  return flow;
}

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_DISCRETE_OPTIMIZATION_ALGORITHMS_LIST4_EX4_DYNIC_H_
