#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_NETWORK_HPP
#define WROCLAW_UNIVERSITY_OF_SCIENCE_NETWORK_HPP

#include <iostream>
#include <vector>
#include <random>

namespace network {

class Network {
 public:
  explicit Network(std::string graph_file_name, double probability, double max_delay, int mean_packet_size);
  bool simulateFlow();
 private:
  std::random_device rd_;
  std::mt19937 gen_{rd_()};
  std::uniform_real_distribution<double> distribution_{0.0, 1.0};

  std::vector<std::vector<int>> graph_;
  std::vector<std::vector<int>> intensity_matrix_;
  std::vector<std::vector<int>> throughput_matrix_;
  std::vector<std::vector<int>> flow_matrix_;

  int nodes_count_ = 0;

  int G = 0;
  int mean_packet_size_ = 0;
  double p_ = 0.0;
  double max_delay_ = 0.0;

  void loadGraphFromFile(std::string file_name);
  std::vector<int> splitAndFormat(std::string text_line);
  bool sendFlow(int start_node, int end_node, int flow);
  std::vector<int> findRoute(int start_node, int end_node);
  double calculateMeanDelay();
  void clear_flow_matrix();
};

}  // namespace network

#endif  // WROCLAW_UNIVERSITY_OF_SCIENCE_NETWORK_HPP
