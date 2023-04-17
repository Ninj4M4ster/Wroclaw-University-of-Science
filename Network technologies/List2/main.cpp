#include "network.hpp"
#include <memory>

int main() {
  std::shared_ptr<network::Network> network =
      std::make_shared<network::Network>("graph.txt",
                                         "intensity_matrix.txt",
                                         0.95,
                                         200, 5);
  network->simulateFlow();
}