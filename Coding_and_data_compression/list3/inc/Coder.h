#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST3_CODER_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST3_CODER_H_

#include <vector>
#include "CodingType.h"

class Coder {
 public:
  void compress(std::string in_file, std::string out_file);

  void setCodingType(CodingType coding_type);
 private:
  std::unordered_map<std::string, size_t> dict_;
  CodingType coding_type_ = CodingType::OMEGA;
  std::vector<int> tmp_buffer_;
  int buffer_ = 0;
  int bits_in_buffer_ = 0;
  std::fstream f_in_;
  std::fstream f_out_;
  size_t outputted_bits_ = 0;

  std::vector<size_t> fibonacci_sequence_{1, 2};

  void addToDict(std::string sign);
  void createDefaultDict();
  void writeBit(int bit);
  void writeNumber(size_t number);
  void outputTempBuffer();
  void encodeSign(std::string sign);
  void endEncoding();

  void encodeGamma(size_t val);
  void encodeDelta(size_t val);
  void encodeOmega(size_t val);
  void encodeFibonacci(size_t val);
  int getFirstLowerEqualFib(size_t number);
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST3_CODER_H_
