#include "network.cpp"
#include <memory>
#define N 1000000

int main() {
  std::string graph_file = "Network technologies/List2/graph.txt";
  std::string intensity_matrix_file = "Network technologies/List2/intensity_matrix.txt";
  std::shared_ptr<network::Network> net =
      std::make_shared<network::Network>(graph_file,
                                         intensity_matrix_file,
                                         0.9995,
                                         0.6,
                                         8);

  int counter = 0;
  for(int i = 0; i < N; i++) {
    bool status = net->simulateFlow();
    if(status)
      counter++;
  }
  std::cout << "Niezawodnosc: " << (double)counter / (double)N << std::endl;

  return 0;
}