#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>

typedef std::unordered_map<int, std::pair<int, int>> Graph;

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

    empty_graph[a] = {b, c};
    empty_graph[b] = {a, c};
    std::getline(f, buff);
  }

  f.close();
}

int main() {
  Graph graph;
  readFile("data/bcl380.tsp", graph);
}