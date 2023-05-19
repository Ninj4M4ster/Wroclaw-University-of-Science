#include <vector>
#include <unordered_map>
#include <mutex>
#include <memory>
#include <thread>
#include <iostream>
#include <random>
#include <chrono>

namespace node {
class Node;
}

namespace transmission_medium {

/**
 * This class represents a medium used to transmit data between nodes connected to it.
 */
class TransmissionMedium {
 public:
  explicit TransmissionMedium(int medium_size, int FPS);
  bool connectToMedium(int index, std::shared_ptr<node::Node> &node);
  int sendData(int index, int data);
  ~TransmissionMedium();
  void displayMedium();
  void startFlow();
  void incDeliveredMessagesCount();
  void stop();
 private:
  typedef struct data_node {
    int data;
    bool go_left;
    bool go_right;
  } DataNode;

  std::vector<DataNode> medium_;
  std::vector<int> nodes_indexes_;
  std::unordered_map<int, std::shared_ptr<node::Node>> nodes_map_;
  int connected_nodes_count_ = 0;
  int delivered_messages_ = 0;

  std::mutex medium_mutex_;
  int medium_length_ = 0;
  bool flow_allowed_ = true;

  int FPS_;

  void push_right(int start_index);
  void push_left(int start_index);
  void simulateOneFlowTick();
  bool isIndexConnected(int index);
};

}  // namespace transmission_medium
