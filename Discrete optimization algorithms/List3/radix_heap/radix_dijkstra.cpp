#include "radix_dijkstra.h"
#include "./../utils/graph_parser.h"
#include <chrono>

void generate_result_for_sources(
    std::vector<std::vector<std::pair<unsigned int, unsigned long int>>> & graph,
    std::vector<unsigned int> & sources,
    std::string result_file_name,
    std::string sources_file_name,
    std::string graph_file_name) {
  std::vector<long double> time_list;

  std::fstream output_file;
  output_file.open(result_file_name.c_str(), std::fstream::out);

  output_file << "p res sp ss radix_dikstra\n";
  output_file << "f " << graph_file_name << " " << sources_file_name << "\n";

  unsigned long long int arcs_count = 0;
  unsigned long int min_cost = std::numeric_limits<unsigned long int>::max();
  unsigned long int max_cost = std::numeric_limits<unsigned long int>::min();

  for(std::vector<std::pair<unsigned int, unsigned long int>> & pairs : graph) {
    for(std::pair<unsigned int, unsigned long int> & pair : pairs) {
      arcs_count++;
      if(pair.second > max_cost) {
        max_cost = pair.second;
      } else if(pair.second < min_cost) {
        min_cost = pair.second;
      }
    }
  }

  output_file << "g " << graph.size() << " " << arcs_count << " " << min_cost << " " << max_cost << "\n";

  int index = 0;
  for(unsigned int source : sources) {
    std::cout << "Current index: " << index << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    dijkstra(graph, source);
    auto end = std::chrono::high_resolution_clock::now();
    time_list.push_back((end - start) / std::chrono::nanoseconds(1) / 1000000.0);
    index++;
  }

  long double sum = 0.0;
  for(long double time : time_list) {
    sum += time;
  }

  output_file << "c sredni czas wyznaczenia najkrotszych sciezek w milisekundach:\n";
  output_file << "t " << sum / (long double)(time_list.size()) << "\n";

  output_file.close();
}

void generate_result_for_pairs(
    std::vector<std::vector<std::pair<unsigned int, unsigned long int>>> & graph,
    std::unordered_map<unsigned int, std::vector<unsigned int>>  & vertices_pairs,
    std::string result_file_name,
    std::string p2p_file_name,
    std::string graph_file_name) {
  std::fstream output_file;
  output_file.open(result_file_name.c_str(), std::fstream::out);

  output_file << "p res sp p2p radix_dikstra\n";
  output_file << "f " << graph_file_name << " " << p2p_file_name << "\n";

  unsigned long long int arcs_count = 0;
  unsigned long int min_cost = std::numeric_limits<unsigned long int>::max();
  unsigned long int max_cost = std::numeric_limits<unsigned long int>::min();

  for(std::vector<std::pair<unsigned int, unsigned long int>> & pairs : graph) {
    for(std::pair<unsigned int, unsigned long int> & pair : pairs) {
      arcs_count++;
      if(pair.second > max_cost) {
        max_cost = pair.second;
      } else if(pair.second < min_cost) {
        min_cost = pair.second;
      }
    }
  }

  output_file << "g " << graph.size() << " " << arcs_count << " " << min_cost << " " << max_cost << "\n";

  output_file << "c\nc dlugosc sciezki miedzy para wierzcholkow\nc\n";

  int index = 0;

  auto it = vertices_pairs.begin();

  while(it != vertices_pairs.end()) {
    std::cout << "Current index: " << index << std::endl;
    unsigned int source = it->first;
    ShortestPaths results = dijkstra(graph, source);
    for(auto target : it->second) {
      std::size_t path_length = 0;
      unsigned current_vertex = target;
      while(current_vertex != source) {
        current_vertex = results.paths.at(current_vertex);
        path_length++;
      }
      output_file << "d " << source << " " << target << " " << path_length << "\n";
    }
    index++;
    it++;
  }

  output_file.close();
}

int main(int argc, char* argv[]) {
  std::vector<std::vector<std::pair<unsigned int, unsigned long int>>> graph;
  std::vector<unsigned int> sources;
  std::unordered_map<unsigned int, std::vector<unsigned int>> vertices_pairs;
  std::string output_file_name;
  std::string graph_file_name;
  std::string sources_file_name;
  std::string p2p_file_name;
  bool sources_only_mode = false;
  bool p2p_mode = false;
  bool output_file = false;
  bool graph_source = false;
  if(argc > 7) {
    std::cout << "Podano za duzo parametrow\n";
    return -1;
  }
  for(int i = 1; i < argc; i++) {
    if(std::string("-d") == argv[i]) {
      if(i+1 >= argc) {
        std::cout << "Nie podano nazwy pliku z danymi\n";
        return -1;
      }
      if(graph_source) {
        std::cout << "Nie mozna podac dwoch grafow \n";
        return -1;
      }
      graph_source = true;
      graph = parse_graph(std::string(argv[i+1]));
      graph_file_name = std::string(argv[i+1]);
      i++;
    } else if(std::string("-ss") == argv[i]) {
      if(i+1 >= argc) {
        std::cout << "Nie podano nazwy pliku ze zrodlami\n";
        return -1;
      }
      if(p2p_mode) {
        std::cout << "Nie mozna podac jednoczesnie zrodel i par wierzcholkow\n";
        return -1;
      }
      sources_only_mode = true;
      sources = parse_sources(std::string(argv[i+1]));
      sources_file_name = std::string(argv[i+1]);
      i++;
    } else if(std::string("-oss") == argv[i] || std::string("-op2p") == argv[i]) {
      if(i+1 >= argc) {
        std::cout << "Nie podano nazwy pliku wynikowego\n";
        return -1;
      }
      if(output_file) {
        std::cout << "Nie mozna podac dwoch plikow wynikowych\n";
        return -1;
      }
      output_file = true;
      output_file_name = std::string(argv[i+1]);
      i++;
    } else if(std::string("-p2p") == argv[i]) {
      if(i+1 >= argc) {
        std::cout << "Nie podano nazwy pliku z parami wierzcholkow\n";
        return -1;
      }
      if(sources_only_mode) {
        std::cout << "Nie mozna podac jednoczesnie zrodel i par wierzcholkow\n";
        return -1;
      }
      p2p_mode = true;
      vertices_pairs = parse_pairs(std::string(argv[i+1]));
      p2p_file_name = std::string(argv[i+1]);
      i++;
    }
  }

  if(!output_file) {
    std::cout << "Nie podano pliku wynikowego\n";
    return -1;
  }

  if(!graph_source) {
    std::cout << "Nie podano pliku z grafem\n";
    return -1;
  }

  if(sources_only_mode) {
    generate_result_for_sources(graph,
                                sources,
                                output_file_name,
                                sources_file_name,
                                graph_file_name);
  } else if(p2p_mode) {
    generate_result_for_pairs(graph,
                              vertices_pairs,
                              output_file_name,
                              p2p_file_name,
                              graph_file_name);
  } else {
    std::cout << "Nie podano pliku ze zrodlami grafu lub parami wierzcholkow\n";
    return -1;
  }

  return 0;
}