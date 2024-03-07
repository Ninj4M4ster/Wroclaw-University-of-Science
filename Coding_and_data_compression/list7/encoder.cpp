#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>

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

int main() {
  std::string input_file = "data/pan-tadeusz-czyli-ostatni-zajazd-na-litwie.txt";
  std::string output_file = "tmp_output.txt";
  encode(input_file, output_file);
}
