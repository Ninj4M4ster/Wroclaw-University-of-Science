#pragma once
#include "node.hpp"
#include "transmission_medium.cpp"


namespace node {

/**
 * Constructor. Creates a new node with given parameters.
 *
 * @param node_name Name of the node.
 * @param index_pose Index where the node will be connected with the medium.
 * @param medium Medium to connect the node.
 * @param generator Random numbers generator.
 * @param distribution Distribution.
 */
Node::Node(std::string node_name,
           int index_pose,
           int basic_delay,
           std::shared_ptr<transmission_medium::TransmissionMedium> & medium,
           std::mt19937_64 & generator,
           std::uniform_int_distribution<int> & distribution) {
  node_name_ = node_name;
  node_index_pos_ = index_pose;
  medium_ = medium;
  rand_gen = generator;
  distribution_ = distribution;
  basic_delay_ = basic_delay;
}

/**
 * Return index, where the node is connected with medium.
 *
 * @return Index where the node is connected.
 */
int Node::getIndexPose() const {
  return node_index_pos_;
}

/**
 * Pass data to the node. This method is called when data passes from another node through medium.
 *
 * @param data Passed data.
 * @return Was the data passed without collision?
 */
bool Node::passData(int data) {
  if(data == 1) {
    std::cout << node_name_ << " otrzymal wiadomosc bez kolizji.\n";
    retry_counter_ = 0;
    message_not_received_ = false;
    medium_->incDeliveredMessagesCount();
    return true;
  } else if(data == 2){
    std::cout << node_name_ << " otrzymal wiadomosc po kolizji.\n";
    retry_ = true;
  }
  return false;
}

/**
 * Run node. This method starts transmitting on given medium.
 * Every time a collision occurs data is re-sent after random, exponential time delay.
 */
void Node::run() {
  access_mutex_.lock();
  while(message_not_received_ || !sending_message_) {
    access_mutex_.unlock();
    access_mutex_.lock();
    if(!sending_message_) {
      sending_message_ = true;
      int status = medium_->sendData(node_index_pos_, 1);
      if(status == 1) {
        std::this_thread::sleep_for(std::chrono::microseconds (10));
        sending_message_ = false;
      }
    }
    // retry sending the message
    if(retry_) {
      // calculate time delay before sending another message
      full_collision_counter_++;
      retry_counter_++;
      if(retry_counter_ >= 15) {
        std::cout << node_name_ << " stopped sending data after 15 collisions\n";
        medium_->stop();
      }
      int K = retry_counter_ <= 10 ? retry_counter_ : 10;
      int R = distribution_(rand_gen) % K;
      double time_delay = basic_delay_ * (double)R;
      std::this_thread::sleep_for(std::chrono::milliseconds((int)time_delay));
      // turn off retries
      retry_ = false;
      int status = medium_->sendData(node_index_pos_, 1);
      if(status == 1) {
        std::this_thread::sleep_for(std::chrono::microseconds (10));
        sending_message_ = false;
      }
    }
    access_mutex_.unlock();
    access_mutex_.lock();
  }
  access_mutex_.unlock();
}

/**
 * Get number of collisions that occurred during transmission.
 *
 * @return Number of collisions.
 */
int Node::getFullCollisionCounter() {
  return full_collision_counter_;
}

/**
 * Stop node from sending data.
 */
void Node::stop() {
  std::cout << node_name_ << " stopped sending data\n";
  message_not_received_ = false;
  sending_message_ = false;
}

}  // namespace node
