#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST2_DECODER_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST2_DECODER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <cmath>

class Decoder {
 public:
  Decoder();
  void decompress_data(std::string& file_name, std::string output_file);
  void init_V(std::fstream & f);
  int get_bit(std::fstream & f);
  unsigned int decode_sign(std::fstream & f,
                  unsigned int & L,
                  unsigned int & R);
  void update_cdf(unsigned int c);
 private:
  std::vector<unsigned int> symbols_indexes = std::vector<unsigned int>(256);
  std::vector<int> index_to_char = std::vector<int>(258);
  std::vector<size_t> cdf = std::vector<size_t>(258, 0);
  std::vector<size_t> frequencies = std::vector<size_t>(258, 1);
  unsigned int V;
  unsigned int buffer;
  int bits_in_buffer = 0;

  static constexpr auto kCharToIntOffset = 128;
  static constexpr auto kHalf = 0x80000000U;
  static constexpr auto kQuarter = 0x40000000U;
  static constexpr auto k3Quarters = 0xC0000000U;
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST2_DECODER_H_
