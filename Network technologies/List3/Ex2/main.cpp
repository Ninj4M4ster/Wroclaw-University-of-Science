#include "node.cpp"

int main() {
  std::mt19937_64 rand_gen1(std::random_device{}());
  std::this_thread::sleep_for(std::chrono::milliseconds(150));
  std::mt19937_64 rand_gen2(std::random_device{}());
  std::uniform_int_distribution<int> distribution{0, (int)std::pow(2, 10)};

  using transmission_medium::TransmissionMedium;
  std::shared_ptr<TransmissionMedium> medium =
      std::make_shared<TransmissionMedium>(50, 30);

  using node::Node;
  std::shared_ptr<Node> node1 =
      std::make_shared<Node>("Node_1", 0, 1000, medium, rand_gen1, distribution);
  std::shared_ptr<Node> node2 =
      std::make_shared<Node>("Node_2", 49, 1000, medium, rand_gen2, distribution);

  medium->connectToMedium(node1->getIndexPose(), node1);
  medium->connectToMedium(node2->getIndexPose(), node2);

  std::vector<std::thread> threads;
  threads.emplace_back([medium]() {medium->startFlow();});
  threads.emplace_back([node1](){node1->run();});
  threads.emplace_back([node2](){node2->run();});

  for(std::thread & t : threads) {
    t.join();
  }

  std::cout << "Pelna ilosc kolizji: " << node1->getFullCollisionCounter() << std::endl;

  return 0;
}
