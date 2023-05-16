#pragma once
#include "node.hpp"
#include "transmission_medium.cpp"


namespace node {

Node::Node(std::string node_name, int index_pose, std::shared_ptr<transmission_medium::TransmissionMedium> & medium) {
  node_name_ = node_name;
  node_index_pos_ = index_pose;
  medium_ = medium;
}

int Node::getIndexPose() const {
  return node_index_pos_;
}

bool Node::passData(int data) {
  if(data == 1) {
    std::cout << node_name_ << " otrzymal wiadomosc bez kolizji.\n";
    access_mutex_.lock();
    retry_counter_ = 0;
    sending_message_ = false;
    access_mutex_.unlock();
    return true;
  } else {
    std::cout << node_name_ << " otrzymal wiadomosc po kolizji.\n";
    access_mutex_.lock();
    access_mutex_.unlock();
  }
  return false;
}

void Node::run(int number_of_messages_to_send) {
  sendKMessages(number_of_messages_to_send);
}

void Node::sendKMessages(int number_of_messages) {
  send_mutex_.lock();
  while(sent_messages_ < number_of_messages) {
    send_mutex_.unlock();
    send_mutex_.lock();
    if(!sending_message_) {
      sending_message_ = true;
      int status = 0;
      std::thread([this, &status]() {
        medium_->sendData(node_index_pos_, std::ref(status));
      }).join();
      if(status == 0) {
        sent_messages_++;
        sending_message_ = false;
      } else if(status == 1) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        sending_message_ = false;
      } else {
        full_collision_counter_++;
        retry_counter_++;
        int K = retry_counter_ <= 10 ? retry_counter_ : 10;
        std::uniform_int_distribution<int> distribution{0, (int)std::pow(2, K)};
        int R = distribution(rand_gen);
        time_delay_ = 100 * (double)R;
        retry_ = true;
        retry_ = true;
      }
    }
    if(retry_) {
      std::this_thread::sleep_for(std::chrono::nanoseconds((int)time_delay_));
      retry_ = false;
      int status = 0;
      std::thread([this, &status]() {
        medium_->sendData(node_index_pos_, std::ref(status));
      }).join();
      if(status == 0) {
        sent_messages_++;
        sending_message_ = false;
      } else if(status == 1) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        sending_message_ = false;
      } else {
        full_collision_counter_++;
        retry_counter_++;
        int K = retry_counter_ <= 10 ? retry_counter_ : 10;
        std::uniform_int_distribution<int> distribution{0, (int)std::pow(2, K)};
        int R = distribution(rand_gen);
        time_delay_ = 100 * (double)R;
        retry_ = true;
        retry_ = true;
      }
    }
    send_mutex_.unlock();
    send_mutex_.lock();
  }
  send_mutex_.unlock();
}

int Node::getFullCollisionCounter() {
  return full_collision_counter_;
}

}  // namespace node
