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
  std::fstream f_in_;
  std::fstream f_out_;

  int buffer_ = 0b0;
  int bits_in_buffer_ = 0;
  bool finish_reading_ = false;

  void addToDict(std::string sign);
  void createDefaultDict();
  int getBit();
  size_t decodeSign();

  size_t decodeGamma();
  size_t decodeDelta();
  size_t decodeOmega();
  size_t decodeFibonacci();
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST3_DECODER_H_
