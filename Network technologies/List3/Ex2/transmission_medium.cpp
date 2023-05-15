#pragma once
#include "transmission_medium.hpp"
#include "node.cpp"


namespace transmission_medium {

TransmissionMedium::TransmissionMedium(int medium_size) {
  medium_ = std::vector<int>(medium_size, 0);
  nodes_indexes_ = std::vector<int>(medium_size, 0);
  medium_length_ = medium_size;
}

bool TransmissionMedium::connectToMedium(int index, std::shared_ptr<node::Node> &node) {
  if(nodes_indexes_.at(index) == 1)
    return false;
  nodes_indexes_.at(index) = 1;
  nodes_map_[index] = node;
  return true;
}

void TransmissionMedium::sendData(int index, int & status) {
  medium_mutex_.lock();
  if(medium_.at(index) == 1) {
    status = 1;
    return;
  }
  transmitting_nodes_counter_ += 2;
  medium_.at(index) = 1;
  medium_mutex_.unlock();

  std::thread t1 = std::thread([this, index]() { push_left(index);});
  std::thread t2 = std::thread([this, index]() { push_right(index);});
  t1.join();
  t2.join();

  medium_mutex_.lock();
  status = final_status_num_;
  if(!collision_)
    final_status_num_ = 0;
  medium_mutex_.unlock();
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
      bool status = nodes_map_[start_index]->passData(medium_.at(start_index));
      if(!status) {
        final_status_num_ = 2;
      }
    }
    medium_mutex_.unlock();
  }

  medium_mutex_.lock();
  medium_.at(start_index) = 0;
  transmitting_nodes_counter_--;
  if(transmitting_nodes_counter_ == 0) {
    collision_ = false;
  }
  medium_mutex_.unlock();
}

void TransmissionMedium::push_right(int start_index) {
  medium_mutex_.lock();
  int length = medium_length_ - 1;
  medium_mutex_.unlock();

  while(start_index < length) {
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
      bool status = nodes_map_[start_index]->passData(medium_.at(start_index));
      if(!status) {
        final_status_num_ = 2;
      }
    }
    medium_mutex_.unlock();
  }

  medium_mutex_.lock();
  medium_.at(start_index) = 0;
  transmitting_nodes_counter_--;
  if(transmitting_nodes_counter_ == 0) {
    collision_ = false;
  }
  medium_mutex_.unlock();
}

bool TransmissionMedium::isIndexConnected(int index) {
  if(nodes_indexes_.at(index) == 1) {
    return true;
  }
  return false;
}

}  // namespace transmission_medium