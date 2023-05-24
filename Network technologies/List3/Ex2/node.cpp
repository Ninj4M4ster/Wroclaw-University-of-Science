#pragma once
#include "node.hpp"


namespace simulation {

Node::Node(std::size_t size, int message_number, int waiting_coefficient) {
  medium_size_ = size;
  message_size_ = 2 * size;
  current_message_size_ = message_size_;
  generator_ = std::mt19937_64{std::random_device{}()};
  distribution_ = std::uniform_int_distribution<int>{0, (int)std::pow(2, 10)};
  message_number_ = message_number;
  waiting_coefficient_ = waiting_coefficient;
}

int Node::tick() {
  if(stop_transmission_)
    return 0;
  if(current_delay_ > 0)
    current_delay_--;
  if(current_delay_ != 0)
    return 0;

  if(collision_in_medium_ && !prev_status_collision_) {
    current_message_size_ = message_size_;
    prev_status_collision_ = true;
    return 0;
  } else if(collision_in_medium_ && prev_status_collision_) {
    return 0;
  }
  if(is_blocked_) {
    is_blocked_ = false;
    current_delay_++;
    return 0;
  }

  if(current_message_size_ > 0) {
    current_message_size_--;
    return message_number_;
  } else if(current_message_size_ == 0 && last_message_to_deliver_) {
    stop_transmission_ = true;
  }
  return 0;
}

int Node::informFree() {
  if(stop_transmission_)
    return 0;
  if(delivered_) {
    delivered_ = false;
    last_message_to_deliver_ = true;
    return 1;
  }

  if(prev_status_collision_) {
    prev_status_collision_ = false;
    collision_in_medium_ = false;
    // add delay calculations
    collision_counter_++;
    if(collision_counter_ >= 15) {
      stop_transmission_ = true;
    }
    else {
      int K = collision_counter_ <= 10 ? collision_counter_ : 10;
      int R = distribution_(generator_) % (int)std::pow(2, K) * waiting_coefficient_;
      current_delay_ = R;
    }
  }
  return 0;
}

void Node::informCollision() {
  collision_in_medium_ = true;
}

void Node::informBlocked() {
  is_blocked_ = true;
  delivered_ = true;
}

}  // namespace simulation
