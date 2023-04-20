#include "network.cpp"
#include <memory>

int main() {
  std::string graph_file = "Network technologies/List2/graphs/graph.txt";
  std::string intensity_matrix_file = "Network technologies/List2/intensity_matrices/intensity_matrix.txt";

  double T_max = 0.6;
  double p = 0.9995;
  int m = 8;

  std::shared_ptr<network::Network> net =
      std::make_shared<network::Network>(graph_file,
                                         intensity_matrix_file,
                                         p,
                                         T_max,
                                         m);

  std::cout << "p = " << p << ", T_max = " << T_max << ", m = " << m << std::endl;

  int N = 100;
  int counter = 0;
  for(int i = 0; i < N; i++) {
    bool status = net->simulateFlow();
    if(status)
      counter++;
  }
  std::cout << "Niezawodnosc dla N = " << N <<", : " << (double)counter / (double)N << std::endl;

  N = 1000;
  counter = 0;
  for(int i = 0; i < N; i++) {
    bool status = net->simulateFlow();
    if(status)
      counter++;
  }
  std::cout << "Niezawodnosc dla N = " << N <<", : " << (double)counter / (double)N << std::endl;

  N = 10000;
  counter = 0;
  for(int i = 0; i < N; i++) {
    bool status = net->simulateFlow();
    if(status)
      counter++;
  }
  std::cout << "Niezawodnosc dla N = " << N <<", : " << (double)counter / (double)N << std::endl;

  N = 100000;
  counter = 0;
  for(int i = 0; i < N; i++) {
    bool status = net->simulateFlow();
    if(status)
      counter++;
  }
  std::cout << "Niezawodnosc dla N = " << N <<", : " << (double)counter / (double)N << std::endl;

  N = 1000000;
  counter = 0;
  for(int i = 0; i < N; i++) {
    bool status = net->simulateFlow();
    if(status)
      counter++;
  }
  std::cout << "Niezawodnosc dla N = " << N <<", : " << (double)counter / (double)N << std::endl;

  return 0;
}