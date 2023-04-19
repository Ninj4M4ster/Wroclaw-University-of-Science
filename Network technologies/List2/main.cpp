#include "network.cpp"
#include <memory>
#define N 100000

int main() {
  std::string graph_file = "Network technologies/List2/graph.txt";
  std::string intensity_matrix_file = "Network technologies/List2/intensity_matrix.txt";
  std::shared_ptr<network::Network> net =
      std::make_shared<network::Network>(graph_file,
                                         intensity_matrix_file,
                                         0.999,
                                         0.75,
                                         8);
//  net->printIntensityMatrix();
  int counter = 0;
  for(int i = 0; i < N; i++) {
    bool status = net->simulateFlow();
    if(status)
      counter++;
  }
  std::cout << "Niezawodnosc: " << (double)counter / (double)N << std::endl;
//  net->printPreviousFlow();

  return 0;
}