#include "utils.h"
#include "./../Ex1/edmondsKarp.h"
#include <chrono>
#include <fstream>

void saveGraph(std::string file_name, Graph & graph) {
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
    Graph graph = genGraph(4, 2);

    if (save_graph) {
      saveGraph("bipartite_graph.txt", graph);
    }

    std::cout << "Graph generated\n";
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::unordered_map<unsigned int, long long>> flow = edmondsKarp(graph, 0, graph.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();

    std::cerr << "Czas: " << (end - start) / std::chrono::milliseconds(1) << std::endl;

    if (graph.size() < (std::size_t) std::pow(2, 10)) {
      int i = 0;
      for (auto &row : flow) {
        for (auto val : row) {
          if(val.second > 0) {
            std::cout << i << " " << val.first << " " << val.second << "\n";
          }
        }
        i++;
      }
    }

    std::size_t max_flow = 0;
    for (auto &pair : flow.at(graph.size() - 1)) {
      max_flow -= pair.second;
    }

    std::cout << "Max flow: " << max_flow << std::endl;

    std::cout << "Finished\n";
  } else {

  }
  return 0;
}