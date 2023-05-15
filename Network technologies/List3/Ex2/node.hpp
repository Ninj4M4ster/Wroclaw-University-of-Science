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
  Node(std::string node_name, int index_pose, std::shared_ptr<transmission_medium::TransmissionMedium> &medium);
  int getIndexPose() const;
  bool passData(int data);
  void run(int number_of_messages_to_send);
  int getFullCollisionCounter();
 private:
  std::shared_ptr<transmission_medium::TransmissionMedium> medium_;
  std::string node_name_;
  int node_index_pos_;
  std::random_device rd{};
  std::mt19937 rand_gen{rd()};

  int retry_counter_ = 0;
  int sent_messages_ = 0;
  std::mutex access_mutex_;
  std::mutex send_mutex_;
  bool sending_message_ = false;
  bool retry_ = false;
  double time_delay_ = 0.0;
  int full_collision_counter_ = 0;

  void sendKMessages(int number_of_messages);
};

}  // namespace node
