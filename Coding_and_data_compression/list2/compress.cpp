#include <iostream>
#include "encoder.cpp"

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cerr << "Wrong number of arguments\n";
    return -1;
  }
  std::string file_name = argv[1];

  Encoder encoder;
  encoder.compress_data(file_name, "compressed.txt");

  std::cout << "Entropy: " << encoder.calculate_entropy() << std::endl;
  std::cout << "Mean code length: " << encoder.mean_code_length() << std::endl;
  std::cout << "Compression factor: " << encoder.compression_factor() << std::endl;

  return 0;
}