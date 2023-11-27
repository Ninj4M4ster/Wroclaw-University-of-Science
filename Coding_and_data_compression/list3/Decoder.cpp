#include "inc/Decoder.h"

void Decoder::decompress(std::string in_file, std::string out_file) {
  createDefaultDict();
  f_in_.open(in_file, std::ios_base::binary | std::ios_base::in);
  f_out_.open(out_file, std::ios_base::out);

  size_t prev = decodeSign();
  std::string S, C;
  f_out_ << dict_[prev];
  while(!f_in_.eof()) {
    size_t next = decodeSign();
    if(next == dict_.size() + 1) {
      break;
    }
    if(dict_.find(next) == dict_.end()) {
      S = dict_[prev];
      S = S + C;
    } else {
      S = dict_[next];
    }
    f_out_ << S;
    C = S[0];
    addToDict(dict_[prev] + C);
    prev = next;
  }
  f_in_.close();
  f_out_.close();
}

void Decoder::setCodingType(CodingType coding_type) {
  coding_type_ = coding_type;
}

void Decoder::addToDict(std::string sign) {
  dict_[dict_.size()] = sign;
}

void Decoder::createDefaultDict() {
  dict_.clear();
  for(int i = 0; i < 256; i++) {
    std::string s = std::string(1, i);
    dict_[i] = s;
  }
}

int Decoder::getBit() {
  if(bits_in_buffer_ == 0) {
    buffer_ = f_in_.get();
    if(f_in_.eof()) {
      finish_reading_ = true;
    }
    bits_in_buffer_ = 8;
  }
  bits_in_buffer_--;
  int val = buffer_ & 1;
  buffer_ >>= 1;
  return val;
}

size_t Decoder::decodeSign() {
  switch (coding_type_) {
    case CodingType::OMEGA: {
      return decodeOmega();
    }
    case CodingType::DELTA: {
      return decodeDelta();
    }
    case CodingType::GAMMA: {
      return decodeGamma();
    }
    case CodingType::FIBONACCI: {
      return decodeFibonacci();
    }
  }
}

size_t Decoder::decodeGamma() {
  return 0;
}

size_t Decoder::decodeDelta() {
  return 0;
}

size_t Decoder::decodeOmega() {
  size_t n = 1;
  size_t val = getBit();
  while(val > 0) {
    for(int i = 0; i < n; i++) {
      val <<= 1;
      val |= getBit();
    }
    n = val;
    val = getBit();
  }
  return n;
}

size_t Decoder::decodeFibonacci() {
  std::vector<int> bits;
  bits.push_back(getBit());
  int val = getBit();
  while(bits.at(bits.size() - 1) != 1 || val != 1) {
    bits.push_back(val);
    val = getBit();
  }
  size_t return_val = 0;
  int index = 0;
  for(auto bit : bits) {
    if(bit)
      return_val += getFibonacciByIndex(index);
    index++;
  }
  return return_val;
}

size_t Decoder::getFibonacciByIndex(int index) {
  while(index >= fibonacci_sequence_.size()) {
    fibonacci_sequence_.push_back(
        fibonacci_sequence_.at(fibonacci_sequence_.size() - 1) +
        fibonacci_sequence_.at(fibonacci_sequence_.size() - 2));
  }
  return fibonacci_sequence_.at(index);
}