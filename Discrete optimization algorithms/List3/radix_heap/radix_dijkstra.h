#ifndef AOD_L3_RADIX_HEAP_RADIX_DIJKSTRA_H_
#define AOD_L3_RADIX_HEAP_RADIX_DIJKSTRA_H_

#include "radix_buckets.h"

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
      std::vector<unsigned long int>(graph.size(), std::numeric_limits<unsigned long int>::max());
  // create priority queue
  RadixBuckets Q;
  // mark distance for source and push it to the queue
  distances.at(source) = 0;
  Q.push({source, 0});
  while(!Q.empty()) {
    // pop current closes vertex from queue
    std::pair<unsigned int, unsigned long int> current_closest_vertex = Q.pop();
    if(current_closest_vertex.second > distances.at(current_closest_vertex.first))
      continue;
    // for all neighbours of current closes vertex
    for(std::pair<unsigned int, unsigned long int> & neighbour : graph.at(current_closest_vertex.first)) {
      unsigned long int current_dist = distances.at(current_closest_vertex.first) + neighbour.second;
      if(current_dist < distances.at(neighbour.first)) {
        // update distance
        distances.at(neighbour.first) = current_dist;
        previous_vertices.at(neighbour.first) = current_closest_vertex.first;
        Q.push({neighbour.first, current_dist});
      }
    }
  }
  return {distances, previous_vertices};
}

#endif //AOD_L3_RADIX_HEAP_RADIX_DIJKSTRA_H_
