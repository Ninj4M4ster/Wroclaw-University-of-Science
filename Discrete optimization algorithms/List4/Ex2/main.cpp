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

void saveToFile(std::string file_name,
                std::size_t flow,
                double time) {
  std::fstream f;
  f.open(file_name, std::fstream::out);

  f << flow << ";" << time;

  f.close();
}

int main(int argc, char* argv[]) {
  bool save_graph = false;
  bool print_flow = false;
  bool save_to_file = std::stoi(argv[3]);
  std::string file_name = "zad2.txt";

  long long paths_count = 0;

  int size = std::stoi(argv[1]);
  int neighbours_count = std::stoi(argv[2]);

  Graph graph = genGraph(size, neighbours_count);

  if (save_graph) {
    saveGraph("bipartite_graph.txt", graph);
  }

  auto start = std::chrono::high_resolution_clock::now();
  std::vector<std::unordered_map<unsigned int, long long>> flow =
      edmondsKarp(graph, 0, graph.size() - 1, paths_count);
  auto end = std::chrono::high_resolution_clock::now();

  double time = (end - start) / (std::chrono::nanoseconds(1) * 1000000.0);

  std::cerr << "Czas: " << time << std::endl;

  if (print_flow) {
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

  if(save_to_file) {
    saveToFile(file_name, max_flow, time);
  }

  return 0;
}