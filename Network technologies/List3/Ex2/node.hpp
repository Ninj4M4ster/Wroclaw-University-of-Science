#include <vector>
#include <unordered_map>
#include <mutex>
#include <memory>
#include <thread>
#include <iostream>
#include <random>
#include <chrono>

namespace simulation {

/**
 * Node class. It represents a computer connected to given medium.
 */
class Node {
 public:
  Node(std::size_t size, int message_number, int waiting_coefficient);
  int tick();
  void informBlocked();
  void informCollision();
  int informFree();
  void informDelivered();

 private:
  std::size_t medium_size_;
  std::size_t message_size_;
  std::size_t current_message_size_;
  std::size_t current_delay_ = 0;
  std::size_t collision_counter_ = 0;

  std::mt19937_64 generator_;
  std::uniform_int_distribution<int> distribution_;

  int message_number_;
  int waiting_coefficient_;

  bool is_blocked_ = false;
  bool collision_in_medium_ = false;
  bool prev_status_collision_ = false;
  bool stop_transmission_ = false;
  bool delivered_ = false;
  bool last_message_to_deliver_ = false;
};

}  // namespace simulation
