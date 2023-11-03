#include "decoder.cpp"

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cerr << "Wrong number of arguments\n";
    return -1;
  }
  std::string file_name = argv[1];

  Decoder decoder;
  decoder.decompress_data(file_name, "decompressed.txt");

  return 0;
}