#include "inc/Decoder.h"

void Decoder::decompress(std::string in_file, std::string out_file) {

}

void Decoder::addToDict(std::string sign) {
  dict_[dict_.size()] = sign;
}

void Decoder::createDefaultDict() {

}

void Decoder::writeBit(int bit) {
  outputted_bits_++;
  bits_in_buffer_++;
  buffer_ >>= 1;
  if(bit)
    buffer_ |= 0x80;
  if(bits_in_buffer_ == 8) {
    f_out_.put(buffer_);
    bits_in_buffer_ = 0;
  }
}

void Decoder::writeNumber(size_t number) {
  if(number == 0)
    writeBit(0);
  while(number > 0) {
    writeBit(number & 0b1);
    number >>= 1;
  }
}

std::string Decoder::decodeSign(size_t sign) {
  switch (coding_type_) {
    case CodingType::OMEGA:return decodeOmega(sign);
    case CodingType::DELTA:return decodeDelta(sign);
    case CodingType::GAMMA:return decodeGamma(sign);
    case CodingType::FIBONACCI:return decodeFibonacci(sign);
  }
}

std::string Decoder::decodeGamma(size_t val) {

}

std::string Decoder::decodeDelta(size_t val) {

}

std::string Decoder::decodeOmega(size_t val) {

}

std::string Decoder::decodeFibonacci(size_t val) {

}
