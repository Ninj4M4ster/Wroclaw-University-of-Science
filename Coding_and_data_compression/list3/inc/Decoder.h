#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST3_DECODER_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST3_DECODER_H_

#include "CodingType.h"

class Decoder {
 public:
  void decompress(std::string in_file, std::string out_file);

  void setCodingType(CodingType coding_type);
 private:
  std::unordered_map<size_t, std::string> dict_;
  CodingType coding_type_ = CodingType::OMEGA;
  int buffer_ = 0b0;
  int bits_in_buffer_ = 0;
  std::fstream f_in_;
  std::fstream f_out_;
  size_t outputted_bits_ = 0;

  void addToDict(std::string sign);
  void createDefaultDict();
  void writeBit(int bit);
  void writeNumber(size_t number);
  std::string decodeSign(size_t sign);

  std::string decodeGamma(size_t val);
  std::string decodeDelta(size_t val);
  std::string decodeOmega(size_t val);
  std::string decodeFibonacci(size_t val);
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST3_DECODER_H_
