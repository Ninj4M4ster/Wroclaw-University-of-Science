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
}

/**
 * Return graph read from file.
 *
 * @return Graph read from previously given file.
 */
std::shared_ptr<Graph> GraphHandler::getGraph() const {
  return graph_;
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
      graph_->operator[](iter->first - 1)[inner_iter->first - 1] = dist;
      graph_->operator[](inner_iter->first - 1)[iter->first - 1] = dist;
    }
  }

  f.close();
}
