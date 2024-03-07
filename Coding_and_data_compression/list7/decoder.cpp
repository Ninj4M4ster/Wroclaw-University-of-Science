#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> scalar_product(std::vector<std::vector<int>> mat, std::vector<int> x) {
  std::vector<int> result;
  for(auto set : mat) {
    int res = 0;
    for(int i = 0; i < x.size(); i++) {
      res += set.at(i) * x.at(i);
    }
    result.push_back(res % 2);
  }
  return result;
}

int correct(std::vector<int> bits, std::vector<int> product, int & double_bit_error) {
  int error_column = (product.at(0) << 2 | product.at(1) << 1 | product.at(2));
  if(product.at(3) == 1) {  // parity error
    error_column -= 1;
    if(error_column < 0)
      error_column += 8;
    bits.at(error_column) = (bits.at(error_column) + 1) % 2;
  } else {
    if(error_column > 0) {
      double_bit_error = 1;
    }
  }
  return ((bits.at(2) << 3) | (bits.at(4) << 2) | (bits.at(5) << 1) | bits.at(6)) << 4;
}

void decode(std::string input, std::string output) {
  std::vector<std::vector<int>> H {
      {1, 0, 1, 0, 1, 0, 1, 0},
      {0, 1, 1, 0, 0, 1, 1, 0},
      {0, 0, 0, 1, 1, 1, 1, 0},
      {1, 1, 1, 1, 1, 1, 1, 1}
  };
  size_t double_bit_errors_count = 0;
  std::fstream f_in, f_out;
  f_in.open(input, std::ios::binary | std::ios::in);
  f_out.open(output, std::ios::binary | std::ios::out);

  int val = f_in.get();
  unsigned int out_val = 0;
  int buff = 0;
  while(!f_in.eof()) {
    out_val >>= 4;
    std::vector<int> single_bits;
    for(int i = 7; i >= 0; i--) {
      single_bits.push_back((val & (0b1 << i)) >> i);
    }
    std::vector<int> product = scalar_product(H, single_bits);
    int double_bit_error = 0;
    out_val |= correct(single_bits, product, double_bit_error);
    double_bit_errors_count += double_bit_error;

    buff++;
    if(buff == 2) {
      f_out.put((int)out_val);
      buff = 0;
    }
    val = f_in.get();
  }
  f_in.close();
  f_out.close();
  std::cout << "Number of double bits errors: " << double_bit_errors_count << std::endl;
}

int main(int argc, char* argv[]) {
  if(argc != 3) {
    std::cerr << "Wrong number of arguments. Got " << argc << ", expected 3\n";
    return 1;
  }
  std::string input = argv[1];
  std::string output = argv[2];
  decode(input, output);
}