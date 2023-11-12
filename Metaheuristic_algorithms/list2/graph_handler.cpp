#include "inc/graph_handler.h"

/**
 * Constructor. It reads graph from given file,
 * creates mst based on this graph starting from vertex 0
 * and calculates cost of created mst.
 *
 * @param file_name Name of the file containing graph.
 */
GraphHandler::GraphHandler(std::string file_name) {
  readFile(file_name);
  primMst(0);
  mst_cost_ = calculateMstCost();
}

/**
 * 2D euclidean distance between two points rounded to closest decimal number.
 *
 * @param l First point
 * @param r Second point
 * @return 2D euclidean distance
 */
int GraphHandler::euc_2d(const std::pair<int, int>& l, const std::pair<int, int>& r) {
  return (int)std::round(std::sqrt(std::pow(l.first - r.first, 2) + std::pow(l.second - r.second, 2)));
}

/**
 * Read graph data from given .tsp file name and save it to given graph structure.
 *
 * @param file_name Name of the .tsp file
 * @param empty_graph Empty graph structure
 */
void GraphHandler::readFile(std::string file_name) {
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
      graph_[iter->first - 1][inner_iter->first - 1] = dist;
      graph_[inner_iter->first - 1][iter->first - 1] = dist;
    }
  }

  f.close();
}

/**
 * Find MST in given graph. This function implements Prim's algorithm.
 *
 * @param source Source vertex
 * @param graph Graph to find mst
 * @return Cost of the mst.
 */
void GraphHandler::primMst(int source) {
  std::vector<int> C(graph_.size(), std::numeric_limits<int>::max());
  std::vector<int> parent(graph_.size(), -1);
  auto compare =
      [](std::pair<int, int> l, std::pair<int, int> r) {return l.second > r.second;};
  std::vector<bool> visited(graph_.size(), false);

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
    for(auto neighbours : graph_[curr.first]) {
      if(!visited.at(neighbours.first) && C.at(neighbours.first) > neighbours.second) {
        C.at(neighbours.first) = neighbours.second;
        pq.emplace(neighbours.first, C.at(neighbours.first));
        parent.at(neighbours.first) = curr.first;
      }
    }
  }
  // push mst to graph structure
  for(int i = 0; i < parent.size(); i++) {
    if(parent.at(i) != -1) {
      mst_[i][parent.at(i)] = graph_[i][parent.at(i)];
      mst_[parent.at(i)][i] = graph_[parent.at(i)][i];
    }
  }
}

/**
 * Calculate cost of given MST tree by travelling it using BFS algorithm.
 *
 * @param mst MST which cost will be calculated.
 * @return Cost of given MST.
 */
std::size_t GraphHandler::calculateMstCost() {
  std::vector<bool> visited(mst_.size(), false);
  size_t final_cost = 0;
  std::queue<int> Q;
  Q.push(0);
  visited.at(0) = true;
  while(!Q.empty()) {
    int curr_vert = Q.front();
    Q.pop();
    for(auto pair : mst_.at(curr_vert)) {
      if(!visited.at(pair.first)) {
        final_cost += pair.second;
        Q.push(pair.first);
        visited.at(pair.first) = true;
      }
    }
  }
  return final_cost;
}