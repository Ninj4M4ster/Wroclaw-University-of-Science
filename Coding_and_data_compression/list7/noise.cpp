#include <iostream>
#include <fstream>
#include <random>

void applyNoise(std::string input, std::string output, double p) {
  std::mt19937_64 random_gen{std::random_device{}()};
  std::uniform_real_distribution<double> distribution{0.0, 1.0};
  std::fstream f_in, f_out;
  f_in.open(input, std::ios::binary | std::ios::in);
  f_out.open(output, std::ios::binary | std::ios::out);

  int val = f_in.get();
  while(!f_in.eof()) {
    int offset = 0;
    int output_val = 0;
    while(offset < 8) {
      double chance = distribution(random_gen);
      int bit = ((val & (1 << offset)) >> offset);
      if(chance < p) {
        bit = !bit;
      }
      output_val |= (bit << offset);
      offset++;
    }
    f_out.put(output_val);
    val = f_in.get();
  }

  f_in.close();
  f_out.close();
}

int main(int argc, char* argv[]) {
  if(argc != 4) {
    std::cerr << "Wrong number of arguments, got " << argc << " but 4 were expected\n";
    return 1;
  }
  double p = std::stod(argv[1]);
  std::string input = argv[2];
  std::string output = argv[3];
  applyNoise(input, output, p);
}