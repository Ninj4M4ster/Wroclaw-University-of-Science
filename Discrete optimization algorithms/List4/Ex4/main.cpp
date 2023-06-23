#include "dinic.h"
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

void saveToFile(std::string file_name,
                std::size_t flow,
                double time,
                long long paths_count) {
  std::fstream f;
  f.open(file_name, std::fstream::out);

  f << flow << ";" << time << ";" << paths_count;

  f.close();
}

int main(int argc, char* argv[]) {
  bool save_graph = false;
  bool print_graph = false;
  bool test = false;

  int size = std::stoi(argv[1]);
  bool save_results = std::stoi(argv[2]);

  long long paths_count = 0;

  Cube cube = genCube(size);

  if (save_graph) {
    saveGraph("cube_graph.txt", cube);
  }

  auto start = std::chrono::high_resolution_clock::now();
  Flow flow = dinic(cube, 0, cube.size() - 1, paths_count);
  auto end = std::chrono::high_resolution_clock::now();

  double time = (end - start) / (std::chrono::nanoseconds(1) * 1000000.0);

  std::cerr << "Czas: " << time << std::endl;

  if(print_graph) {
    int i = 0;
    for (auto &row : flow) {
      std::cout << "Vertex " << i << ": ";
      for (auto val : row) {
        std::cout << val.second << " ";
      }
      std::cout << "\n";
      i++;
    }
  }

  std::size_t max_flow = 0;
  for (auto &pair : flow.at(cube.size() - 1)) {
    max_flow -= pair.second;
  }

  std::cout << "Max flow: " << max_flow << std::endl;

  if(save_results) {
    saveToFile("zad4.txt", max_flow, time, paths_count);
  }

  return 0;
}