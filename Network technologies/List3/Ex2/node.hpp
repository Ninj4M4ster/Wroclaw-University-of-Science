#include <vector>
#include <unordered_map>
#include <mutex>
#include <memory>
#include <thread>
#include <iostream>
#include <random>
#include <chrono>

namespace transmission_medium {
class TransmissionMedium;
}

namespace node {

class Node {
 public:
  explicit Node(std::string node_name,
       int index_pose,
       std::shared_ptr<transmission_medium::TransmissionMedium> &medium,
       std::mt19937_64 & generator,
       std::uniform_int_distribution<int> & distribution);
  int getIndexPose() const;
  bool passData(int data);
  void run();
  int getFullCollisionCounter();
 private:
  std::shared_ptr<transmission_medium::TransmissionMedium> medium_;
  std::string node_name_;
  int node_index_pos_;
  std::mt19937_64 rand_gen;
  std::uniform_int_distribution<int> distribution_;

  int retry_counter_ = 0;
  bool message_not_received_ = true;
  std::mutex access_mutex_;
  bool sending_message_ = false;
  bool retry_ = false;
  int full_collision_counter_ = 0;
};

}  // namespace node
