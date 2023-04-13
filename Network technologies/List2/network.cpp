#include "network.hpp"
#include <fstream>

namespace network {

Network::Network(std::string graph_file_name, double probability, double max_delay, int mean_packet_size) {
  p_ = probability;
  max_delay_ = max_delay;
  mean_packet_size_ = mean_packet_size;
  loadGraphFromFile(graph_file_name);
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
        clear_flow_matrix();
        return status;
      }
    }
  }
  double mean_delay = calculateMeanDelay();
  clear_flow_matrix();
  return mean_delay < max_delay_;
}

void Network::loadGraphFromFile(std::string file_name) {
  std::fstream file;
  file.open(file_name.c_str());
  std::string input;
  std::getline(file, input);
  nodes_count_ = std::stoi(input);
  graph_ = std::vector<std::vector<int>>(nodes_count_, std::vector<int>());
  intensity_matrix_ = std::vector<std::vector<int>>(nodes_count_, std::vector<int>(nodes_count_, 0));
  throughput_matrix_ = std::vector<std::vector<int>>(nodes_count_, std::vector<int>(nodes_count_, 0));
  flow_matrix_ = std::vector<std::vector<int>>(nodes_count_, std::vector<int>(nodes_count_, 0));

  while(std::getline(file, input)) {
    std::vector<int> data = splitAndFormat(input);
    graph_.at(data.at(0)).push_back(data.at(1));
    intensity_matrix_.at(data.at(0)).at(data.at(1)) = data.at(2);
    throughput_matrix_.at(data.at(0)).at(data.at(1)) = data.at(3);
  }
  file.close();
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
  if(distribution_(gen_) > p_)
    return false;
  std::vector<int> route = findRoute(start_node, end_node);
  while(start_node != end_node) {
    int max_packet_count = throughput_matrix_.at(start_node).at(route.at(start_node)) * mean_packet_size_;
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
  return true;
}

std::vector<int> Network::findRoute(int start_node, int end_node) {

}

double Network::calculateMeanDelay() {

}

void Network::clear_flow_matrix() {
  flow_matrix_ = std::vector<std::vector<int>>(nodes_count_, std::vector<int>(nodes_count_, 0));
}

}  // namespace network
