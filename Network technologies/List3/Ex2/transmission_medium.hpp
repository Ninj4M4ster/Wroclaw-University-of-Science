#include <vector>
#include <unordered_map>
#include <mutex>
#include <memory>
#include <thread>
#include <iostream>
#include <random>
#include <chrono>
#include <queue>
#include "node.cpp"

namespace simulation {

/**
 * This class represents a medium used to transmit data between nodes connected to it.
 */
class TransmissionMedium {
 public:
  TransmissionMedium(std::size_t size);
  void registerNode(std::size_t position, int message_number, int waiting_coefficient);

  void runSimulation();
  void print();
 private:
  typedef struct data_node {
    int data = 0;
    bool go_left_ = false;
    bool go_right_ = false;
  } DataNode;

  std::size_t size_;
  std::vector<DataNode> medium_;
  std::vector<std::queue<DataNode>> medium_queue_;
  std::vector<std::pair<std::shared_ptr<Node>, int>> nodes_;
  std::size_t delivered_messages_ = 0;

  void tick();
};

}  // namespace simulation
