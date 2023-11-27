#include "Coder.cpp"
#include "Decoder.cpp"

int main(int argc, char* argv[]) {
  std::cout << "Start\n";
  CodingType coding_type_ = CodingType::OMEGA;
  Coder coder;
  coder.setCodingType(coding_type_);
  coder.compress("data/pan-tadeusz-czyli-ostatni-zajazd-na-litwie.txt", "compressed.txt");
  std::cout << "Compressed\n";
  Decoder decoder;
  decoder.setCodingType(coding_type_);
  decoder.decompress("compressed.txt", "decompressed.txt");
  std::cout << "Decompressed\n";
}