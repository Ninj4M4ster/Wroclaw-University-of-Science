#include "edmondsKarp.h"
#include <chrono>
#include <fstream>

void saveGraph(std::string file_name, Cube & graph) {
  std::fstream f;
  f.open(file_name, std::fstream::out);

  f << graph.size() << "\n";

  for(int i = 0; i < graph.size(); i++) {
    for(auto & pair : graph.at(i)) {
      f << i << " " << pair.first << " " << pair.second << "\n";
    }
  }

  f.close();
}

int main(int argc, char* argv[]) {
  bool save_graph = true;
  bool test = false;

  if(!test) {
    Cube cube = genCube(6);

    if (save_graph) {
      saveGraph("cube_graph.txt", cube);
    }

    std::cout << "Graph generated\n";
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::unordered_map<unsigned int, long long>> flow = edmondsKarp(cube, 0, cube.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();

    std::cerr << "Czas: " << (end - start) / std::chrono::nanoseconds(1) << std::endl;

//    if (cube.size() < (std::size_t) std::pow(2, 10)) {
//      int i = 0;
//      for (auto &row : flow) {
//        std::cout << "Vertex " << i << ": ";
//        for (auto val : row) {
//          std::cout << val.second << " ";
//        }
//        std::cout << "\n";
//        i++;
//      }
//    }

    std::size_t max_flow = 0;
    for (auto &pair : flow.at(cube.size() - 1)) {
      max_flow -= pair.second;
    }

    std::cout << "Max flow: " << max_flow << std::endl;
  } else {

  }
  return 0;
}