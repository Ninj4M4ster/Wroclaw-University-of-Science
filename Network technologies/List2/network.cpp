#include "network.hpp"
#include <fstream>
#include <queue>
#include <iterator>

namespace network {

Network::Network(std::string graph_file_name,
                 std::string intensity_matrix_file_name,
                 double probability,
                 double max_delay,
                 int mean_packet_size) {
  p_ = probability;
  max_delay_ = max_delay;
  mean_packet_size_ = mean_packet_size;
  loadGraphFromFile(graph_file_name);
  loadIntensityMatrixFromFile(intensity_matrix_file_name);
}

bool Network::simulateFlow() {
  bool status = true;
  for (int i = 0; i < (int) intensity_matrix_.size(); i++) {
    for (int j = 0; j < (int) intensity_matrix_.at(i).size(); j++) {
      int flow = intensity_matrix_.at(i).at(j);
      if (flow > 0) {
        status = sendFlow(i, j, flow);
      }
      if(!status) {
        reset_network();
        return status;
      }
    }
  }
  double mean_delay = calculateMeanDelay();
  reset_network();
  return mean_delay < max_delay_;
}

void Network::loadGraphFromFile(std::string file_name) {
  std::fstream file;
  file.open(file_name.c_str());
  std::string input;
  std::getline(file, input);
  nodes_count_ = std::stoi(input);
  original_graph_ = std::vector<std::vector<int>>(nodes_count_, std::vector<int>());
  original_reverse_graph_ =
      std::vector<std::vector<int>>(nodes_count_, std::vector<int>());
  throughput_matrix_ =
      std::vector<std::vector<int>>(nodes_count_, std::vector<int>(nodes_count_, 0));
  flow_matrix_ =
      std::vector<std::vector<int>>(nodes_count_, std::vector<int>(nodes_count_, 0));

  while(std::getline(file, input)) {
    std::vector<int> data = splitAndFormat(input);
    original_graph_.at(data.at(0)).push_back(data.at(1));
    throughput_matrix_.at(data.at(0)).at(data.at(1)) = data.at(2);
  }
  file.close();

  // create reverse graph
  for(int vertex = 0; vertex < original_graph_.size(); vertex++) {
    for(int neighbour : original_graph_.at(vertex)) {
      original_reverse_graph_.at(neighbour).push_back(vertex);
    }
  }

  graph_ = original_graph_;
  reverse_graph_ = original_reverse_graph_;
}

void Network::loadIntensityMatrixFromFile(std::string file_name) {
  std::fstream file;
  file.open(file_name.c_str());
  std::string input;
  intensity_matrix_ =
      std::vector<std::vector<int>>(nodes_count_, std::vector<int>(nodes_count_, 0));

  int row = 0, column = 0;
  while(std::getline(file, input, ';')) {
    intensity_matrix_.at(row).at(column) = std::stoi(input);
    column++;
    if(column == nodes_count_) {
      column = 0;
      row++;
    }
  }

  file.close();

  // calculate G for future
  for(std::vector<int> & line : intensity_matrix_) {
    for(int intensity : line) {
      G_ += intensity;
    }
  }
}

std::vector<int> Network::splitAndFormat(std::string text_line) {
  std::vector<int> result;
  std::string current_word = "";
  for(char c : text_line) {
    if(c == ' ') {
      result.push_back(std::stoi(current_word));
      current_word = "";
      continue;
    }
    current_word += c;
  }
  result.push_back(std::stoi(current_word));
  return result;
}

bool Network::sendFlow(int start_node, int end_node, int flow) {
  if(distribution_(gen_) > p_) {
    auto iterator = graph_.at(start_node).cbegin();
    while(*iterator != end_node) {
      iterator++;
    }
    graph_.at(start_node).erase(iterator);
    iterator = reverse_graph_.at(end_node).cbegin();
    while(*iterator != start_node) {
      iterator++;
    }
    graph_.at(end_node).erase(iterator);
    if(!isGraphConsistent())
      return false;
  }
  std::vector<int> route = findRoute(start_node, end_node);
  std::cout << "Printing route from " << start_node << " to " << end_node << std::endl;
  while(start_node != end_node) {
    int max_packet_count = throughput_matrix_.at(start_node).at(route.at(start_node)) * mean_packet_size_;
    std::cout << start_node << std::endl;
    if(flow_matrix_.at(start_node).at(route.at(start_node)) + flow < max_packet_count) {
      flow_matrix_.at(start_node).at(route.at(start_node)) += flow;
    } else {
      flow = max_packet_count - flow_matrix_.at(start_node).at(route.at(start_node)) - 1;
      if(flow == 0)
        return true;
      flow_matrix_.at(start_node).at(route.at(start_node)) = max_packet_count - 1;
    }
    start_node = route.at(start_node);
  }
  std::cout << std::endl;
  return true;
}

bool Network::isGraphConsistent() {
  std::queue<int> vertices_queue;
  vertices_queue.push(0);
  std::vector<int> visited_vertices(nodes_count_, 0);
  visited_vertices.at(0) = 1;
  // bfs
  while(!vertices_queue.empty()) {
    int current_vertex = vertices_queue.front();
    vertices_queue.pop();
    for(int neighbour : graph_.at(current_vertex)) {
      if(visited_vertices.at(neighbour) != 0) {
        vertices_queue.push(neighbour);
        visited_vertices.at(neighbour) = 1;
      }
    }
  }

  vertices_queue = std::queue<int>();
  vertices_queue.push(0);
  std::vector<int> reverse_visited_vertices(nodes_count_, 0);
  reverse_visited_vertices.at(0) = 1;
  // reverse search
  while(!vertices_queue.empty()) {
    int current_vertex = vertices_queue.front();
    vertices_queue.pop();
    for(int neighbour : reverse_graph_.at(current_vertex)) {
      if(reverse_visited_vertices.at(neighbour) != 0) {
        vertices_queue.push(neighbour);
        reverse_visited_vertices.at(neighbour) = 1;
      }
    }
  }

  // check if there is any unvisited vertex
  for(int i = 0; i < visited_vertices.size(); i++) {
    if(visited_vertices.at(i) == 0 && reverse_visited_vertices.at(i) == 0)
      return false;
  }
  return true;
}

std::vector<int> Network::findRoute(int start_node, int end_node) {
  std::queue<int> vertices_queue;
  vertices_queue.push(start_node);
  std::vector<int> visited_vertices(nodes_count_, -1);
  visited_vertices.at(start_node) = start_node;
  while(!vertices_queue.empty()) {
    int current_vertex = vertices_queue.front();
    vertices_queue.pop();
    if(current_vertex == end_node) {
      break;
    }
    for(int neighbour : graph_.at(current_vertex)) {
      if(visited_vertices.at(neighbour) != -1) {
        vertices_queue.push(neighbour);
        visited_vertices.at(neighbour) = current_vertex;
      }
    }
  }
  std::vector<int> route(nodes_count_, -1);
  while(end_node != start_node) {
    int current_vertex = visited_vertices.at(end_node);
    route.at(current_vertex) = end_node;
    end_node = current_vertex;
  }
  return route;
}

double Network::calculateMeanDelay() {
  double sum = 0.0;
  for(int start_vertex = 0; start_vertex < graph_.size(); start_vertex++) {
    for(int neighbour : graph_.at(start_vertex)) {
      sum +=
          flow_matrix_.at(start_vertex).at(neighbour) /
          (throughput_matrix_.at(start_vertex).at(neighbour) / mean_packet_size_ -
          flow_matrix_.at(start_vertex).at(neighbour));
    }
  }
  return sum * (1.0 / (double)G_);
}

void Network::reset_network() {
  flow_matrix_ =
      std::vector<std::vector<int>>(nodes_count_, std::vector<int>(nodes_count_, 0));
  graph_ = original_graph_;
  reverse_graph_ = original_reverse_graph_;
}

}  // namespace network
