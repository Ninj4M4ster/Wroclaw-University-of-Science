#include "Coder.cpp"
#include "Decoder.cpp"

int main(int argc, char* argv[]) {
  std::cout << "Start\n";
  Coder coder;
  coder.setCodingType(CodingType::DELTA);
  coder.compress("data/pan-tadeusz-czyli-ostatni-zajazd-na-litwie.txt", "compressed.txt");
  std::cout << "Compressed\n";
  Decoder decoder;
  decoder.setCodingType(CodingType::DELTA);
  decoder.decompress("compressed.txt", "decompressed.txt");
  std::cout << "Decompressed\n";
}