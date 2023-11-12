#include <filesystem>
#include "graph_handler.cpp"

/**
 * Find MST in given graph using dfs algorithm.
 * This is main dfs pipeline.
 * Based on order of visited vertices, cycle is created.
 *
 * @param source Source vertex
 * @param graph Mst to find cycle
 * @param cycle Array in which cycle is created
 * @param visited Array indicating if given vertex has been already visited.
 */
void createCycle(int curr_vert, Graph & mst, std::vector<int> & cycle, std::vector<bool> & visited) {
  visited.at(curr_vert) = true;
  cycle.push_back(curr_vert);
  for(auto & pair : mst.at(curr_vert)) {
    if(!visited.at(pair.first)) {
      createCycle(pair.first, mst, cycle, visited);
    }
  }
}

/**
 * Create cycle based on given MST by travelling it using DFS algorithm.
 * Cycle is created by pushing vertices to an array when they are visited for the first time.
 *
 * @param source Starting vertex.
 * @param mst MST to create cycle based on.
 * @return Array that indicates a cycle.
 */
std::vector<int> createCycle(int source, Graph & mst) {
  std::vector<bool> visited(mst.size(), false);
  std::vector<int> cycle;
  createCycle(source, mst, cycle, visited);
  return cycle;
}

int main() {
  std::string data_dir_path = "data/";
  for(const auto & entry : std::filesystem::directory_iterator(data_dir_path)) {
    std::string file_name = entry.path().string();
  }
}