#include "transmission_medium.cpp"

int main() {
  std::shared_ptr<simulation::TransmissionMedium> medium =
      std::make_shared<simulation::TransmissionMedium>(50);

  medium->registerNode(0, 1, 10);
  medium->registerNode(49, 2, 10);

  medium->runSimulation();
  return 0;
}
