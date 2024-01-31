#include <iostream>
#include <fstream>

void compare(std::string before_encoding, std::string after_encoding) {
  std::fstream f1, f2;
  size_t counter = 0;
  f1.open(before_encoding, std::ios::binary | std::ios::in);
  f2.open(after_encoding, std::ios::binary | std::ios::in);

  int val1 = f1.get();
  int val2 = f2.get();

  while(!f1.eof() && !f2.eof()) {
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
}

int main(int argc, char* argv[]) {
  if(argc != 3) {
    std::cerr << "Wrong number of arguments. Got " << argc - 1 << ", but expected 2\n";
    return 1;
  }
  std::string input = argv[1];
  std::string output = argv[2];
  compare(input, output);
}