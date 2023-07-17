#ifndef AOD_L3_DIAL_DIAL_DIJKSTRA_H_
#define AOD_L3_DIAL_DIAL_DIJKSTRA_H_

#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
#include "bin_heap.h"

typedef struct shortest_paths {
  std::vector<unsigned long int> distances;
  std::vector<unsigned int> paths;
} ShortestPaths;

unsigned long int max_cost(std::vector<std::vector<std::pair<unsigned int, unsigned long int>>> & graph) {
  unsigned long int max_cost = 0;
  for(std::vector<std::pair<unsigned int, unsigned long int>> & neighbour_list : graph) {
    for(std::pair<unsigned int, unsigned long int> & neighbour : neighbour_list) {
      if(neighbour.second > max_cost)
        max_cost = neighbour.second;
    }
  }
  return max_cost;
}

ShortestPaths dijkstra(
    std::vector<std::vector<std::pair<unsigned int, unsigned long int>>> & graph,
    unsigned int source) {
  // find the biggest cost in graph
  unsigned long int C = max_cost(graph);
  // initialize vectors for storing distances and paths
  std::vector<unsigned int> previous_vertices = std::vector<unsigned int>(graph.size());
  std::vector<unsigned long int> distances(graph.size(), std::numeric_limits<unsigned long int>::max());
  distances.at(source) = 0;

  // initialize buckets
  std::vector<std::unordered_map<unsigned long int, bool>> buckets(
      C + 1,
      std::unordered_map<unsigned long int, bool>()
          );
  buckets.at(0)[source] = true;

  unsigned int checked_vertices_counter = 1;
  unsigned long int index = 0;
  // travel through buckets while there is any bucket not empty and there are vertices to explore
  while(checked_vertices_counter < graph.size()) {
    unsigned long int counter = 0;
    while(buckets.at(index).empty() && counter < C+1) {
      index++;
      counter++;
      if(index == C+1)
        index = 0;
    }
    if(counter == C+1) {
      break;
    }
    // unordered_map::iterator allows to delete from the hashmap while iterating
    auto bucket_it = buckets.at(index).begin();
    // iterate over all vertices in current bucket
    while(bucket_it != buckets.at(index).end()) {
      checked_vertices_counter++;
      // iterate over all neighbours
      for(std::pair<unsigned int, unsigned long int>  neighbour : graph.at(bucket_it->first)) {
        // update distances and buckets
        if(distances.at(bucket_it->first) + neighbour.second < distances.at(neighbour.first)) {
          // remove node from previous bucket
          buckets.at(distances.at(neighbour.first) % (C + 1)).erase(neighbour.first);
          // add node to new bucket
          buckets.at((distances.at(bucket_it->first) + neighbour.second) % (C + 1))[neighbour.first] = true;
          // update distances and paths
          distances.at(neighbour.first) =  distances.at(bucket_it->first) + neighbour.second;
          previous_vertices.at(neighbour.first) = bucket_it->first;
        }
      }
      // erase vertex from bucket and get new iterator
      bucket_it = buckets.at(index).erase(bucket_it);
    }
  }

  return {distances, previous_vertices};
}

#endif  // AOD_L3_DIAL_DIAL_DIJKSTRA_H_
