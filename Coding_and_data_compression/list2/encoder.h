#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST2_ENCODER_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST2_ENCODER_H_

#include <iostream>
#include <vector>

class Encoder {
 public:
  Encoder();
  void compress_data(std::string& file_name);
  void encode_sign(unsigned int sign,
                   unsigned int & L,
                   unsigned int & R);
  void update_cdf(unsigned int c);
  long double calculate_entropy();
  void save_compressed_data(std::string file_name);
 private:
  std::vector<unsigned int> symbols_indexes = std::vector<unsigned int>(256);
  std::vector<int> index_to_char = std::vector<int>(257);
  std::vector<size_t> cdf = std::vector<size_t>(258, 0);
  std::vector<size_t> frequencies = std::vector<size_t>(257, 1);
  std::vector<bool> buffer;
  size_t counter = 0;

  static constexpr auto kCharToIntOffset = 128;
  static constexpr auto kHalf = 0x80000000U;
  static constexpr auto kQuarter = 0x40000000U;
  static constexpr auto k3Quarters = 0xC0000000U;
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST2_ENCODER_H_
