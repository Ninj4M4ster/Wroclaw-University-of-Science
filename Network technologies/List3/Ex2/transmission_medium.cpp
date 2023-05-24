#pragma once
#include "transmission_medium.hpp"
#include "node.cpp"

namespace simulation {

TransmissionMedium::TransmissionMedium(std::size_t size) {
    size_ = size;
    medium_ = std::vector<DataNode>(size, {0, false, false});
    medium_queue_ = std::vector<std::queue<DataNode>>(size, std::queue<DataNode>());
}

void TransmissionMedium::registerNode(std::size_t position, int message_number, int waiting_coefficient) {
  std::shared_ptr<Node> node = std::make_shared<Node>(size_, message_number, waiting_coefficient);
  nodes_.push_back({node, position});
}

void TransmissionMedium::runSimulation() {
  while(delivered_messages_ < nodes_.size()) {
    print();
    tick();
    for(auto & pair : nodes_) {
      if(medium_.at(pair.second).data == 1) {
        pair.first->informBlocked();
      } else if(medium_.at(pair.second).data == 3) {
        pair.first->informCollision();
      } else if(medium_.at(pair.second).data == 0) {
        delivered_messages_ += pair.first->informFree();
      }

      int data = pair.first->tick();

      if(data != 0) {  // insert data to medium
        medium_.at(pair.second) = {data, true, true};
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}

void TransmissionMedium::tick() {
  for(int i = 0; i < size_; i++) {
    DataNode current_node = medium_.at(i);
    if(current_node.go_right_ && i + 1 <= size_ - 1) {
      medium_queue_.at(i+1).push({current_node.data, false, true});
    }
    if(current_node.go_left_ && i - 1 >= 0) {
      medium_queue_.at(i-1).push({current_node.data, true, false});
    }
    medium_.at(i) = {0, false, false};
  }

  for(int i = 0; i < size_; i++) {
    while(!medium_queue_.at(i).empty()) {
      DataNode current_node = medium_queue_.at(i).front();
      medium_queue_.at(i).pop();
      if(medium_.at(i).data != 0) {
        medium_.at(i).data = 3;
      } else {
        medium_.at(i).data = current_node.data;
      }
      if(current_node.go_left_) {
        medium_.at(i).go_left_ = true;
      }
      if(current_node.go_right_) {
        medium_.at(i).go_right_ = true;
      }
    }
  }
}

void TransmissionMedium::print() {
  for(std::size_t i = 0; i < size_; i++) {
    int number = medium_.at(i).data;
    if(number == 1) {
      std::cout << "\u001b[32m" << number << "\u001b[0m";
    } else if(number == 2) {
      std::cout << "\u001b[33m" << number << "\u001b[0m";
    } else if(number == 3){
      std::cout << "\u001b[31m" << number << "\u001b[0m";
    } else {
      std::cout << number;
    }
  }
  std::cout << "\n";
}

}  // namespace simulation
