#include <iostream>
#include <vector>
#include <unordered_map>
#include <mutex>
#include "node.cpp"
#include <memory>
#include <thread>

namespace transmission_medium {

class TransmissionMedium {
 public:
  TransmissionMedium(int medium_size);
  bool connectToMedium(int index, std::shared_ptr<Node> & node);
  bool sendData(int index);
 private:
  std::vector<int> medium_;
  std::vector<int> nodes_indexes_;
  std::unordered_map<int, std::shared_ptr<Node>> nodes_map_;

  bool collision_ = false;
  std::mutex medium_mutex_;
  int transmitting_nodes_counter_ = 0;
  int medium_length_ = 0;

  void push_right(int start_index);
  void push_left(int start_index);
  bool isIndexConnected(int index);
};

TransmissionMedium::TransmissionMedium(int medium_size) {
  medium_ = std::vector<int>(medium_size, 0);
  nodes_indexes_ = std::vector<int>(medium_size, 0);
  medium_length_ = medium_size;
}

bool TransmissionMedium::connectToMedium(int index, std::shared_ptr<Node> & node) {
  if(nodes_indexes_.at(index) == 1)
    return false;
  nodes_indexes_.at(index) = 1;
  nodes_map_[index] = node;
  return true;
}

bool TransmissionMedium::sendData(int index) {
  medium_mutex_.lock();
  if(medium_.at(index) == 1)
    return false;
  transmitting_nodes_counter_ += 2;
  medium_.at(index) = 1;
  medium_mutex_.unlock();
  std::thread([this, index]() { push_left(index);});
  std::thread([this, index]() { push_right(index);});
  return true;
}

void TransmissionMedium::push_left(int start_index) {
  while(start_index > 0) {
    medium_mutex_.lock();
    if(medium_.at(start_index - 1) == 1) {
      collision_ = true;
    }

    if(collision_) {
      medium_.at(start_index - 1) = 2;
    } else {
      medium_.at(start_index - 1) = 1;
    }

    medium_.at(start_index) = 0;

    start_index--;
    if(isIndexConnected(start_index)) {
      nodes_map_[start_index]->passData(medium_.at(start_index));
    }
    medium_mutex_.unlock();
  }

  medium_mutex_.lock();
  transmitting_nodes_counter_--;
  if(transmitting_nodes_counter_ == 0) {
    collision_ = false;
  }
  medium_mutex_.unlock();
}

void TransmissionMedium::push_right(int start_index) {
  while(start_index < medium_length_) {
    medium_mutex_.lock();
    if(medium_.at(start_index + 1) == 1) {
      collision_ = true;
    }

    if(collision_) {
      medium_.at(start_index + 1) = 2;
    } else {
      medium_.at(start_index + 1) = 1;
    }

    medium_.at(start_index) = 0;

    start_index++;
    if(isIndexConnected(start_index)) {
      nodes_map_[start_index]->passData(medium_.at(start_index));
    }
    medium_mutex_.unlock();
  }

  medium_mutex_.lock();
  transmitting_nodes_counter_--;
  if(transmitting_nodes_counter_ == 0) {
    collision_ = false;
  }
  medium_mutex_.unlock();
}

bool TransmissionMedium::isIndexConnected(int index) {
  for(int node_index : nodes_indexes_) {
    if(node_index == index)
      return true;
  }
  return false;
}



}  // namespace transmission_medium