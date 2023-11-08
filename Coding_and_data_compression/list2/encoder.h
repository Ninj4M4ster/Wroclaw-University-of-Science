#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST2_ENCODER_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST2_ENCODER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <cmath>

/**
 * Encoder class responsible for encoding files using adaptive arithmetic coding.
 */
class Encoder {
 public:
  Encoder();
  void compress_data(std::string& file_name, std::string output_file_name);
  long double calculate_entropy();
  long double mean_code_length();
  long double compression_factor();
 private:
  void encode_sign(int sign,
                   int & L,
                   int & R,
                   std::fstream & f_out);
  void update_cdf(int c);
  void output_bit(int bit, std::fstream& f_out);
  std::vector<int> symbols_indexes = std::vector<int>(256);
  std::vector<unsigned char> index_to_char = std::vector<unsigned char>(257);
  std::vector<int> cdf = std::vector<int>(258, 0);
  std::vector<int> frequencies = std::vector<int>(258, 1);
  std::vector<size_t> full_frequencies = std::vector<size_t>(257, 0);
  int buffer = 0;
  int bits_in_buffer = 0;
  size_t counter = 0;
  size_t full_bits_counter = 0;
  size_t outputted_bits = 0;

  static constexpr int kHalf = 0x8000;
  static constexpr int kQuarter = 0x4000;
  static constexpr int k3Quarters = 0xC000;
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST2_ENCODER_H_
