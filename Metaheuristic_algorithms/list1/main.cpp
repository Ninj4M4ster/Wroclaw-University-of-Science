#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <limits>
#include <cmath>
#include <random>
#include <algorithm>

/**
 * Graph structure
 */
typedef std::unordered_map<int, std::unordered_map<int, int>> Graph;

/**
 * 2D euclidean distance between two points rounded to closest decimal number.
 *
 * @param l First point
 * @param r Second point
 * @return 2D euclidean distance
 */
int euc_2d(const std::pair<int, int>& l, const std::pair<int, int>& r) {
  return (int)std::round(std::sqrt(std::pow(l.first - r.first, 2) + std::pow(l.second - r.second, 2)));
}

/**
 * Read graph data from given .tsp file name and save it to given graph structure.
 *
 * @param file_name Name of the .tsp file
 * @param empty_graph Empty graph structure
 */
void readFile(std::string file_name, Graph& empty_graph) {
  std::fstream f;
  f.open(file_name.c_str(), std::ios::in);
  if(f.bad()) {
    f.close();
    std::cerr << "Could not open given file\n";
    throw std::exception();
  }
  std::string buff;
  while(buff != "NODE_COORD_SECTION") {
    std::getline(f, buff);
  }

  // read all coordinates to unordered map
  std::unordered_map<int, std::pair<int, int>> coords;
  std::string single_num;
  std::getline(f, buff);
  while(buff != "EOF") {
    std::stringstream ss;
    ss << buff;
    int a, b, c;
    std::getline(ss, single_num, ' ');
    a = std::stoi(single_num);
    std::getline(ss, single_num, ' ');
    b = std::stoi(single_num);
    std::getline(ss, single_num, ' ');
    c = std::stoi(single_num);

    coords[a] = {b, c};
    std::getline(f, buff);
  }

  // create graph by calculating distance for each pair of coords
  for(auto iter = coords.begin(); iter != coords.end(); iter++) {
    auto inner_iter = iter;
    inner_iter++;
    for(; inner_iter != coords.end(); inner_iter++) {
      int dist = euc_2d(iter->second, inner_iter->second);
      empty_graph[iter->first - 1][inner_iter->first - 1] = dist;
      empty_graph[inner_iter->first - 1][iter->first - 1] = dist;
    }
  }

  f.close();
}

/**
 * Find MST in given graph. This function implements Prim's algorithm.
 *
 * @param source Source vert
 * @param graph Graph to find mst
 * @return Cost of the mst.
 */
std::size_t primMst(int source, Graph graph) {
  std::vector<int> C(graph.size(), std::numeric_limits<int>::max());
  std::vector<int> parent(graph.size(), -1);
  auto compare =
      [](std::pair<int, int> l, std::pair<int, int> r) {return l.second > r.second;};
  std::vector<bool> visited(graph.size(), false);

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(compare)> pq(compare);
  C.at(source) = 0;
  pq.emplace(source, 0);
  while(!pq.empty()) {
    auto curr = pq.top();
    pq.pop();

    if(visited.at(curr.first)) {
      continue;
    }
    visited.at(curr.first) = true;
    for(auto neighbours : graph[curr.first]) {
      if(!visited.at(neighbours.first) && C.at(neighbours.first) > neighbours.second) {
        C.at(neighbours.first) = neighbours.second;
        pq.emplace(neighbours.first, C.at(neighbours.first));
        parent.at(neighbours.first) = curr.first;
      }
    }
  }

  std::size_t result = 0;
  for(int i = 0; i < parent.size(); i++) {
    if(parent.at(i) != -1) {
      result += graph[parent.at(i)][i];
    }
  }
  return result;
}

/**
 * Find MST in given graph using Prim's algorithm.
 * Based on order of visited vertex, cycle is created.
 *
 * @param source Source vert
 * @param graph Graph to find mst
 * @return Vector with vertex in order of the cycle.
 */
std::vector<int> primMstCycle(int source, Graph graph) {
  std::vector<int> C(graph.size(), std::numeric_limits<int>::max());
  std::vector<int> parent(graph.size(), -1);
  auto compare =
      [](std::pair<int, int> l, std::pair<int, int> r) {return l.second > r.second;};
  std::vector<bool> visited(graph.size(), false);

  std::vector<int> vertex_history;

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(compare)> pq(compare);
  C.at(source) = 0;
  pq.emplace(source, 0);
  while(!pq.empty()) {
    auto curr = pq.top();
    pq.pop();

    if(visited.at(curr.first)) {
      continue;
    }
    visited.at(curr.first) = true;
    vertex_history.push_back(curr.first);
    for(auto neighbours : graph[curr.first]) {
      if(!visited.at(neighbours.first) && C.at(neighbours.first) > neighbours.second) {
        C.at(neighbours.first) = neighbours.second;
        pq.emplace(neighbours.first, C.at(neighbours.first));
        parent.at(neighbours.first) = curr.first;
      }
    }
  }

  return vertex_history;
}

/**
 * Calculate the cost to travel given cycle.
 *
 * @param cycle Vector with vertex in order of the cycle
 * @param graph Graph in which cycle was created
 * @return Cost of travelling given cycle.
 */
std::size_t calculateCycleCost(std::vector<int>& cycle, Graph & graph) {
  std::size_t cost = 0;
  for(std::size_t i = 0; i < cycle.size() - 1; i++) {
    cost += graph[cycle.at(i)][cycle.at(i+1)];
  }
  cost += graph[cycle.at(cycle.size() - 1)][cycle.at(0)];
  return cost;
}

/**
 * Generate 1000 permutations of the cycles and put data about mean minimum costs to file.
 *
 * @param graph Graph to find costs of travelling the cycles.
 */
void generateCycles(Graph & graph) {
  std::vector<int> cycle;
  for(int i = 0; i < graph.size(); i++)
    cycle.push_back(i);

  std::mt19937_64 rand_gen{std::random_device{}()};
  std::vector<std::size_t> results;
  for(int i = 0; i < 1000; i++) {
    std::shuffle(cycle.begin(), cycle.end(), rand_gen);
    results.push_back(calculateCycleCost(cycle, graph));
  }

  std::vector<std::size_t> groups_100_10;
  for(int i = 0; i < 1000; i += 10) {
    std::size_t minimum = results.at(i);
    for(int j = 1; j < 10; j++) {
      if(results.at(i+j) < minimum)
        minimum = results.at(i+j);
    }
    groups_100_10.push_back(minimum);
  }
  long double mean_100_10 = 0.0;
  for(auto c : groups_100_10) {
    mean_100_10 += c;
  }
  mean_100_10 /= groups_100_10.size();

  std::vector<std::size_t> groups_20_50;
  for(int i = 0; i < 1000; i += 50) {
    std::size_t minimum = results.at(i);
    for(int j = 1; j < 50; j++) {
      if(results.at(i+j) < minimum)
        minimum = results.at(i+j);
    }
    groups_20_50.push_back(minimum);
  }
  long double mean_20_50 = 0.0;
  for(auto c : groups_20_50) {
    mean_20_50 += c;
  }
  mean_20_50 /= groups_20_50.size();

  std::size_t all_minimum = results.at(0);
  for(int i = 1; i < 1000; i++) {
    if(results.at(i) < all_minimum)
      all_minimum = results.at(i);
  }

  std::cout << "Srednia z minimum dla 10 losowan: " << mean_100_10 << std::endl;
  std::cout << "Srednia z minimum dla 50 losowan: " << mean_20_50 << std::endl;
  std::cout << "Minimalna wartosc: " << all_minimum << std::endl;
}

int main() {
  Graph graph;
  readFile("data/xqf131.tsp", graph);

  std::cout << "Koszt MST: " << primMst(0, graph) << std::endl;
  std::vector<int> cycle = primMstCycle(0, graph);
  std::cout << "Koszt cyklu: " << calculateCycleCost(cycle, graph) << std::endl;
  generateCycles(graph);
}