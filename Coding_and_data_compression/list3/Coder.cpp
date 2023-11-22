//
// Created by kubad on 21.11.2023.
//

#include "inc/Coder.h"


void Coder::compress(std::string in_file, std::string out_file) {
  createDefaultDict();
  f_in_.open(in_file, std::ios::binary | std::ios::in);
  f_out_.open(out_file, std::ios::binary | std::ios::out);
  int val = f_in_.get();
  std::string prev_sign = std::string(1, val);
  while(!f_in_.eof()) {
    val = f_in_.get();
    std::string next_sign = std::string(1, val);
    std::string sequence = prev_sign + next_sign;
    if(dict_.find(sequence) != dict_.end()) {
      prev_sign += next_sign;
    } else {
      encodeSign(prev_sign);
      addToDict(prev_sign + next_sign);
      prev_sign = next_sign;
    }
  }
  f_in_.close();
  f_out_.close();
}

void Coder::setCodingType(CodingType coding_type) {
  coding_type_ = coding_type;
}


void Coder::addToDict(std::string sign) {
  dict_[sign] = dict_.size();
}

void Coder::createDefaultDict() {
  dict_.clear();
  for(int i = 0; i < 256; i++) {
    std::string s = std::string(1, i);
    dict_[s] = i;
  }
}

void Coder::writeBit(int bit) {
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

void Coder::writeNumber(size_t number) {
  if(number == 0)
    writeBit(0);
  while(number > 0) {
    writeBit(number & 0b1);
    number >>= 1;
  }
}

void Coder::encodeSign(std::string sign) {
  size_t sign_val = dict_[sign];
  switch (coding_type_) {
    case CodingType::OMEGA:encodeOmega(sign_val);
    case CodingType::DELTA:encodeDelta(sign_val);
    case CodingType::GAMMA:encodeGamma(sign_val);
    case CodingType::FIBONACCI:encodeFibonacci(sign_val);
  }
}

void Coder::encodeGamma(size_t val) {
  size_t n = 64 - __builtin_clzll(val);
  for(int i = 0; i < n - 1; i++) {
    writeBit(0);
  }
  if(val == 0) {
    writeBit(0);
    return;
  }
  while(val > 0) {
    writeBit(val & 0b1);
    val >>= 1;
  }
}

void Coder::encodeDelta(size_t val) {
  size_t n = 64 - __builtin_clzll(val);
  size_t k = 64 - __builtin_clzll(n);
  for(int i = 0; i < k - 1; i++) {
    writeBit(0);
  }
  while(n > 0) {
    writeBit(n & 0b1);
    n >>= 1;
  }
  while(val > 1) {
    writeBit(val & 0b1);
    val >>= 1;
  }
}

void Coder::encodeOmega(size_t val) {
  writeBit(0);
  while(val > 1) {
    val = 64 - __builtin_clzll(val);
    writeNumber(val);
    val--;
  }
}

void Coder::encodeFibonacci(size_t val) {

}



