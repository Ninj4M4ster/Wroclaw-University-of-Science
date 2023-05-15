#include "node.cpp"

int main() {
  using transmission_medium::TransmissionMedium;
  std::shared_ptr<TransmissionMedium> medium =
      std::make_shared<TransmissionMedium>(500);

  using node::Node;
  std::shared_ptr<Node> node1 =
      std::make_shared<Node>("Node_1", 20, medium);
  std::shared_ptr<Node> node2 =
      std::make_shared<Node>("Node_2", 400, medium);
  std::shared_ptr<Node> node3 =
      std::make_shared<Node>("Node_3", 200, medium);

  medium->connectToMedium(node1->getIndexPose(), node1);
  medium->connectToMedium(node2->getIndexPose(), node2);
  medium->connectToMedium(node3->getIndexPose(), node3);

  std::vector<std::thread> threads;
  threads.emplace_back([node1](){node1->run(500);});
  threads.emplace_back([node2](){node2->run(500);});
  threads.emplace_back([node3](){node3->run(500);});

  for(std::thread & t : threads) {
    t.join();
  }

  std::cout << "Pelna ilosc kolizji: " << node1->getFullCollisionCounter() << std::endl;

  return 0;
}
