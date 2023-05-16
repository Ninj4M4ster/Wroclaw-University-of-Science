#pragma once
#include "transmission_medium.hpp"
#include "node.cpp"


namespace transmission_medium {

TransmissionMedium::TransmissionMedium(int medium_size) {
  medium_ = std::vector<DataNode>(medium_size, {0,
                                                false,
                                                false});
  nodes_indexes_ = std::vector<int>(medium_size, 0);
  medium_length_ = medium_size;
}

bool TransmissionMedium::connectToMedium(int index, std::shared_ptr<node::Node> &node) {
  if(nodes_indexes_.at(index) == 1)
    return false;
  nodes_indexes_.at(index) = 1;
  nodes_map_[index] = node;
  connected_nodes_count_++;
  return true;
}

int TransmissionMedium::sendData(int index, int data) {
//  medium_mutex_.lock();
  if(medium_.at(index).data == 1) {
//    medium_mutex_.unlock();
    return 1;
  }
  DataNode new_node;
  new_node.data = data;
  new_node.go_left = true;
  new_node.go_right = true;
  medium_.at(index) = new_node;

  displayMedium();
//  medium_mutex_.unlock();
  return 0;
}

void TransmissionMedium::startFlow() {
  medium_mutex_.lock();
  while(flow_allowed_ && connected_nodes_count_ > delivered_messages_) {
    medium_mutex_.unlock();
    medium_mutex_.lock();
    simulateOneFlowTick();
    displayMedium();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    medium_mutex_.unlock();
    medium_mutex_.lock();
  }
  medium_mutex_.unlock();
}

void TransmissionMedium::simulateOneFlowTick() {
  for(int i = 0; i < medium_length_; i++) {
    DataNode node = medium_.at(i);
    if(node.go_left && node.go_right) {
      if(i != 0) {  // moving data left
        DataNode prev_node = medium_.at(i-1);
        if(prev_node.data > 0) {  // collision
          prev_node.data = 2;
          prev_node.go_left = true;
        } else {  // pass data to the left
          prev_node.data = node.data;
          prev_node.go_left = true;
        }
        medium_.at(i-1) = prev_node;

        // check if data arrived
        if(isIndexConnected(i-1)) {
          nodes_map_[i-1]->passData(prev_node.data);
        }
      }
      bool collision = false;

      if(i != medium_length_ - 1) {  // moving data right
        DataNode next_node = medium_.at(i+1);
        if(next_node.data > 0) {  // collision
          next_node.data = 2;
          next_node.go_right = true;
          collision = true;
        } else {  // pass data to the right
          next_node.data = node.data;
          next_node.go_right = true;
        }
        medium_.at(i+1) = next_node;

        // check if data arrived
        if(isIndexConnected(i+1)) {
          nodes_map_[i+1]->passData(next_node.data);
        }
      }

      // clear node
      node.data = 0;
      node.go_left = false;
      node.go_right = false;
      if(collision) {
        node.data = 2;
        node.go_left = true;
      }
      medium_.at(i) = node;
      i++;
    } else if(node.go_left) {
      if(i != 0) {
        DataNode prev_node = medium_.at(i-1);
        if(prev_node.data > 0) {  // collision
          prev_node.data = 2;
          prev_node.go_left = true;
        } else {  // pass data to the left
          prev_node.go_left = true;
          prev_node.data = node.data;
        }

        medium_.at(i-1) = prev_node;

        // check if data arrived
        if(isIndexConnected(i-1)) {
          nodes_map_[i-1]->passData(prev_node.data);
        }
      }
      // clear data from flow node
      node.go_left = false;
      node.go_right = false;
      node.data = 0;
      medium_.at(i) = node;
    } else if(node.go_right) {
      if(i != medium_length_ - 1) {
        DataNode next_node = medium_.at(i+1);
        if(next_node.data > 0) {  // collision
          next_node.data = 2;
          node.data = 2;
          next_node.go_right = true;
          next_node.go_left = false;
          node.go_left = true;
          node.go_right = false;
        } else {  // pass data to the right
          next_node.data = node.data;
          next_node.go_right = true;
          node.data = 0;
          node.go_right = false;
        }

        medium_.at(i+1) = next_node;
        medium_.at(i) = node;

        // check if data arrived
        if(isIndexConnected(i+1)) {
          nodes_map_[i+1]->passData(next_node.data);
        }
        // move index two places forward
        i++;
      } else {
        // clear data from flow node
        node.go_right = false;
        node.data = 0;
        node.go_left = false;
        medium_.at(i) = node;
      }
    }
  }
}

bool TransmissionMedium::isIndexConnected(int index) {
  if(nodes_indexes_.at(index) == 1) {
    return true;
  }
  return false;
}

void TransmissionMedium::displayMedium() {
  for(DataNode & node : medium_) {
    std::cout << node.data;
  }
  std::cout << std::endl;
}

void TransmissionMedium::incDeliveredMessagesCount() {
  delivered_messages_++;
}

TransmissionMedium::~TransmissionMedium() {
  medium_mutex_.lock();
  flow_allowed_ = false;
  medium_mutex_.unlock();
}

}  // namespace transmission_medium