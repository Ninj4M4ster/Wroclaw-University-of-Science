#include "network.cpp"
#include <memory>

int main() {
  std::string graph_file = "Network technologies/List2/graph.txt";
  std::string intensity_matrix_file = "Network technologies/List2/intensity_matrix.txt";
  std::shared_ptr<network::Network> net =
      std::make_shared<network::Network>(graph_file,
                                         intensity_matrix_file,
                                         0.999,
                                         0.85,
                                         8);
  int counter = 0;
  for(int i = 0; i < 20000; i++) {
    bool status = net->simulateFlow();
    if(status)
      counter++;
  }
  std::cout << "Niezawodnosc: " << (double)counter / 20000.0 << std::endl;

  return 0;
}