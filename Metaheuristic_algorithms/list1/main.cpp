#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <limits>

typedef std::unordered_map<int, std::unordered_map<int, int>> Graph;

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

    empty_graph[a][b] = c;
    empty_graph[b][a] = c;
    std::getline(f, buff);
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