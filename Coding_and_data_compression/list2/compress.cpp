#include <iostream>
#include <fstream>
#include <cmath>
#include <bitset>
#include "encoder.cpp"

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cerr << "Wrong number of arguments\n";
    return -1;
  }
  std::string file_name = argv[1];

  Encoder encoder;
  encoder.compress_data(file_name);
  encoder.save_compressed_data("compressed.txt");

  long double entropy = encoder.calculate_entropy();
  std::cout << "Entropia: " << entropy << std::endl;

  return 0;
}