#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <limits>
#include <cmath>

typedef std::unordered_map<int, std::unordered_map<int, int>> Graph;

int euc_2d(const std::pair<int, int>& l, const std::pair<int, int>& r) {
  return (int)std::round(std::sqrt(std::pow(l.first - r.first, 2) + std::pow(l.second - r.second, 2)));
}

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


Graph primMst(int source, Graph graph) {
  Graph mst;
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
    std::cout << i << " - " << parent.at(i) << std::endl;
    if(parent.at(i) != -1) {
      result += graph[parent.at(i)][i];
    }
  }
  std::cout << result << "\n";
  return mst;
}

int main() {
  Graph graph;
  readFile("data/xql662.tsp", graph);

  primMst(0, graph);
}