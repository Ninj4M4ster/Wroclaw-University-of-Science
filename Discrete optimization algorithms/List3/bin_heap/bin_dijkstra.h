#ifndef AOD_L3_BIN_HEAP_BIN_DIJKSTRA_H_
#define AOD_L3_BIN_HEAP_BIN_DIJKSTRA_H_

#include <iostream>
#include <limits>
#include "bin_heap.h"

typedef struct shortest_paths {
  std::vector<unsigned long int> distances;
  std::vector<unsigned int> paths;
} ShortestPaths;

ShortestPaths dijkstra(
    std::vector<std::vector<std::pair<unsigned int, unsigned long int>>> & graph,
    unsigned int source) {
  static constexpr auto inf = std::numeric_limits<unsigned long int>::max();
  // initialize vectors for storing distances and paths
  std::vector<unsigned int> previous_vertices = std::vector<unsigned int>(graph.size());
  std::vector<unsigned long int> distances =
      std::vector<unsigned long int>(graph.size(), inf);
  // create priority queue
  BinHeap Q;
  // mark distance for source and push it to the queue
  distances.at(source) = 0;
  Q.push({source, 0});
  while(!Q.empty()) {
    // pop current closes vertex from queue
    std::pair<unsigned int, unsigned long int> current_closest_vertex = Q.pop();
    // for all neighbours of current closes vertex
    for(std::pair<unsigned int, unsigned long int> & neighbour : graph.at(current_closest_vertex.first)) {
      unsigned long int current_dist = distances.at(current_closest_vertex.first) + neighbour.second;
      if(distances.at(neighbour.first) == inf) {
        distances.at(neighbour.first) = current_dist;
        previous_vertices.at(neighbour.first) = current_closest_vertex.first;
        // place vertex in queue with calculated distance
        Q.push({neighbour.first, current_dist});
      }
      else if(current_dist < distances.at(neighbour.first)) {
        // update distance
        Q.decreaseKey({neighbour.first, distances.at(neighbour.first)}, current_dist);
        distances.at(neighbour.first) = current_dist;
        previous_vertices.at(neighbour.first) = current_closest_vertex.first;
      }
    }
  }
  return {distances, previous_vertices};
}

#endif  // AOD_L3_BIN_HEAP_BIN_DIJKSTRA_H_
