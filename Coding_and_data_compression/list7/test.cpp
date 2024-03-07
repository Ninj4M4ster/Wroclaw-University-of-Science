#include <iostream>
#include <fstream>
#include <vector>
#include <random>

double applyNoise(std::string input, std::string output, double p) {
  size_t single_bit = 0;
  size_t two_bits = 0;
  size_t three_bits = 0;
  size_t four_bits = 0;
  size_t count = 0;
  size_t count_with_noise = 0;
  std::mt19937_64 random_gen{std::random_device{}()};
  std::uniform_real_distribution<double> distribution{0.0, 1.0};
  std::fstream f_in, f_out;
  f_in.open(input, std::ios::binary | std::ios::in);
  f_out.open(output, std::ios::binary | std::ios::out);

  int val = f_in.get();
  while(!f_in.eof()) {
    count += 2;
    int offset = 0;
    int output_val = 0;
    int noise_count = 0;
    bool second_block = true;
    while(offset < 8) {
      double chance = distribution(random_gen);
      int bit = ((val & (1 << offset)) >> offset);
      if(chance < p) {
        bit = !bit;
        noise_count += 1;
      }
      output_val |= (bit << offset);
      offset++;
      if(offset > 3 && second_block && noise_count > 0) {
        second_block = false;
        count_with_noise++;
        switch (noise_count) {
          case 1:
            single_bit++;
            break;
          case 2:
            two_bits++;
            break;
          case 3:
            three_bits++;
            break;
          case 4:
            four_bits++;
            break;
        }
        noise_count = 0;
      }
    }

    f_out.put(output_val);
    val = f_in.get();
  }

  f_in.close();
  f_out.close();
  std::cout << "Single: " << static_cast<double>(single_bit) / static_cast<double>(count) << std::endl;
  std::cout << "Double: " << static_cast<double>(two_bits) / static_cast<double>(count) << std::endl;
  std::cout << "triple: " << static_cast<double>(three_bits) / static_cast<double>(count) << std::endl;
  std::cout << "Four: " << static_cast<double>(four_bits) / static_cast<double>(count) << std::endl;
  return static_cast<double>(count_with_noise) / static_cast<double>(count);
}

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
      error_column -= 1;
      if(error_column < 0)
        error_column += 8;
      double_bit_error = 1;
    }
  }
  return ((bits.at(2) << 3) | (bits.at(4) << 2) | (bits.at(5) << 1) | bits.at(6)) << 4;
}

double decode(std::string input, std::string output) {
  std::vector<std::vector<int>> H {
      {1, 0, 1, 0, 1, 0, 1, 0},
      {0, 1, 1, 0, 0, 1, 1, 0},
      {0, 0, 0, 1, 1, 1, 1, 0},
      {1, 1, 1, 1, 1, 1, 1, 1}
  };
  size_t blocks_count = 0;
  size_t double_bit_errors_count = 0;
  std::fstream f_in, f_out;
  f_in.open(input, std::ios::binary | std::ios::in);
  f_out.open(output, std::ios::binary | std::ios::out);

  int val = f_in.get();
  unsigned int out_val = 0;
  int buff = 0;
  while(!f_in.eof()) {
    blocks_count++;
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
//  std::cout << "Number of double bits errors: " << double_bit_errors_count << std::endl;
  return static_cast<double>(double_bit_errors_count) / static_cast<double>(blocks_count);
}

void encode(std::string input_name, std::string output_name) {
  static std::vector<std::vector<int>> G {
      {1, 1, 0, 1},
      {1, 0, 1, 1},
      {1, 0, 0, 0},
      {0, 1, 1, 1},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1},
      {1, 1, 1, 0}
  };
  std::fstream in_f, out_f;
  in_f.open(input_name, std::ios::binary | std::ios::in);
  out_f.open(output_name, std::ios::binary | std::ios::out);

  int input = in_f.get();
  unsigned int output = 0;
  while(!in_f.eof()) {
    for(int i = 0; i < 2; i++) {
      output = 0;
      int bits = input & (0b1111);
      input >>= 4;
      std::vector<int> single_bits;
      for(int j = 3; j >= 0; j--) {
        single_bits.push_back((bits & (0b1 << j)) >> j);
      }
      std::vector<int> output_bits = scalar_product(G, single_bits);
      int offset = 7;
      for(auto val : output_bits) {
        output |= (val << offset);
        offset--;
      }
      out_f.put((int)output);
    }
    output = 0;
    input = in_f.get();
  }

  in_f.close();
  out_f.close();
}

double compare(std::string before_encoding, std::string after_encoding) {
  size_t counter = 0;
  size_t blocks_count = 0;
  std::fstream f1, f2;
  f1.open(before_encoding, std::ios::binary | std::ios::in);
  f2.open(after_encoding, std::ios::binary | std::ios::in);

  int val1 = f1.get();
  int val2 = f2.get();

  while(!f1.eof() && !f2.eof()) {
    blocks_count += 2;
    int check_1 = (val1 & 0b1111);
    int check_2 = (val2 & 0b1111);
    if(check_1 != check_2)
      counter++;

    val1 >>= 4;
    val2 >>= 4;

    check_1 = (val1 & 0b1111);
    check_2 = (val2 & 0b1111);
    if(check_1 != check_2)
      counter++;
    val1 = f1.get();
    val2 = f2.get();
  }

  f1.close();
  f2.close();
  std::cout << "Number of wrong sequences: " << counter << std::endl;
  return static_cast<double>(counter) / static_cast<double>(blocks_count);
}

int main() {
  std::string input = "data/pan-tadeusz-czyli-ostatni-zajazd-na-litwie.txt";
  std::string output = "encoded.txt";
  std::string noise_output = "encoded_noise.txt";
  std::string decoded = "decoded.txt";
  double start_p = 0.01;
  double step = 2.0;
  std::fstream f1, f2, f3;

  std::vector<double> res1;
  std::vector<double> res2;
  std::vector<double> res3;

  while(start_p <= 1.0) {
    res1.push_back(applyNoise(input, output, start_p));
    encode(input, output);
    applyNoise(output, noise_output, start_p);
    res2.push_back(decode(noise_output, decoded));
    res3.push_back(compare(input, decoded));
    start_p += step;
  }

  for(auto val : res1) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
  for(auto val : res2) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
  for(auto val : res3) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
}