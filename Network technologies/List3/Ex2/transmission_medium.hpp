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

class TransmissionMedium {
 public:
  TransmissionMedium(int medium_size);
  bool connectToMedium(int index, std::shared_ptr<node::Node> &node);
  void sendData(int index, int & status);
 private:
  std::vector<int> medium_;
  std::vector<int> nodes_indexes_;
  std::unordered_map<int, std::shared_ptr<node::Node>> nodes_map_;

  bool collision_ = false;
  std::mutex medium_mutex_;
  std::mutex send_mutex_;
  int transmitting_nodes_counter_ = 0;
  int medium_length_ = 0;
  int final_status_num_ = 0;

  void push_right(int start_index);
  void push_left(int start_index);
  bool isIndexConnected(int index);
};

}  // namespace transmission_medium
