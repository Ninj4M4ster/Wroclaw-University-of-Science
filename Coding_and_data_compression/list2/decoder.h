#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST2_DECODER_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST2_DECODER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <cmath>

/**
 * Decoder class responsible for decoding files using adaptive arithmetic coding.
 */
class Decoder {
 public:
  Decoder();
  void decompress_data(std::string& file_name, std::string output_file);
  void init_V(std::fstream & f);
  int get_bit(std::fstream & f);
  int decode_sign(std::fstream & f,
                  int & L,
                  int & R);
  void update_cdf(int c);
 private:
  std::vector<int> symbols_indexes = std::vector<int>(256);
  std::vector<unsigned char> index_to_char = std::vector<unsigned char>(257);
  std::vector<int> cdf = std::vector<int>(258, 0);
  std::vector<int> frequencies = std::vector<int>(258, 1);
  int V;
  int buffer;
  int bits_in_buffer = 0;
  bool last_8_iterations = false;
  int last_8_iterations_counter = 8;

  static constexpr int kHalf = 0x8000;
  static constexpr int kQuarter = 0x4000;
  static constexpr int k3Quarters = 0xC000;
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST2_DECODER_H_
