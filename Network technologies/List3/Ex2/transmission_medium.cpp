#pragma once
#include "transmission_medium.hpp"
#include "node.cpp"


namespace transmission_medium {

/**
 * Constructor.
 *
 * @param medium_size Size of the medium.
 */
TransmissionMedium::TransmissionMedium(int medium_size, int FPS) {
  medium_ = std::vector<DataNode>(medium_size, {0,
                                                false,
                                                false});
  nodes_indexes_ = std::vector<int>(medium_size, 0);
  medium_length_ = medium_size;
  FPS_ = FPS;
}

/**
 * Connect a node to the medium at given index.
 *
 * @param index Index at which node will be connected.
 * @param node Node to be connected.
 * @return Was the node connected successfully?
 */
bool TransmissionMedium::connectToMedium(int index, std::shared_ptr<node::Node> &node) {
  if(nodes_indexes_.at(index) == 1)
    return false;
  nodes_indexes_.at(index) = 1;
  nodes_map_[index] = node;
  connected_nodes_count_++;
  return true;
}

/**
 * Send data through medium, starting on given index.
 * This method inserts single data on given index. Further, this data will be handled by flow simulation.
 *
 * @param index Index where data will be inserted.
 * @param data Data to be inserted.
 * @return Status of insertion (0 if data was inserted, 1 if medium was busy on given index).
 */
int TransmissionMedium::sendData(int index, int data) {
  if(medium_.at(index).data == 1) {
    return 1;
  }
  DataNode new_node;
  new_node.data = data;
  new_node.go_left = true;
  new_node.go_right = true;
  medium_.at(index) = new_node;

  displayMedium();
  return 0;
}

/**
 * Method for starting flow in the medium. Every 30 milliseconds it simulates one tick of the flow.
 */
void TransmissionMedium::startFlow() {
  medium_mutex_.lock();
  while(flow_allowed_ && connected_nodes_count_ > delivered_messages_) {
    medium_mutex_.unlock();
    medium_mutex_.lock();
    simulateOneFlowTick();
    displayMedium();
    std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000 * (1.0 / (double)FPS_))));
    medium_mutex_.unlock();
    medium_mutex_.lock();
  }
  medium_mutex_.unlock();
}

/**
 * Simulate one tick of the flow. Every index in medium containing data is pushed in proper direction.
 * This method also detects collisions.
 */
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

/**
 * This method checks if there is a node connected at given index.
 *
 * @param index Index to be checked.
 * @return Is there a node connected at given index?
 */
bool TransmissionMedium::isIndexConnected(int index) {
  if(nodes_indexes_.at(index) == 1) {
    return true;
  }
  return false;
}

/**
 * Method for displaying data currently in the medium.
 */
void TransmissionMedium::displayMedium() {
  for(DataNode & node : medium_) {
    int number = node.data;
    if(number == 1)
    {
      std::cout << "\u001b[32m" << number << "\u001b[0m";
    } else if(number == 2) {
      std::cout << "\u001b[31m" << number << "\u001b[0m";
    } else {
      std::cout << number;
    }
  }
  std::cout << std::endl;
}

/**
 * Increase counter for messages delivered without collisions.
 */
void TransmissionMedium::incDeliveredMessagesCount() {
  delivered_messages_++;
}

/**
 * Destructor. Stops the flow simulation.
 */
TransmissionMedium::~TransmissionMedium() {
  flow_allowed_ = false;
}

/**
 * Stop the work of every connected node.
 */
void TransmissionMedium::stop() {
  auto it = nodes_map_.begin();
  while(it != nodes_map_.end()) {
    it->second->stop();
    it++;
  }
  flow_allowed_ = false;
}

}  // namespace transmission_medium