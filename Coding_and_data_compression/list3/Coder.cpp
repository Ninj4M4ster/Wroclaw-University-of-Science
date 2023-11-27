#include <bitset>
#include <algorithm>
#include <cmath>
#include "inc/Coder.h"


void Coder::compress(std::string in_file, std::string out_file) {
  createDefaultDict();
  f_in_.open(in_file, std::ios::binary | std::ios::in);
  f_out_.open(out_file, std::ios::binary | std::ios::out);
  int val = f_in_.get();
  std::string prev_sign = std::string(1, val);
  while(!f_in_.eof()) {
    val = f_in_.get();
    updateInputFreq(val);
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
  endEncoding();
  f_out_.put(buffer_ >> (8 - bits_in_buffer_));
  f_in_.close();
  f_out_.close();
  f_out_.open(out_file, std::ios::binary | std::ios::in);
  calculateStatistics();
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
  tmp_buffer_.push_back(bit);
  outputted_bits_++;
}

void Coder::outputTempBuffer() {
  int index = tmp_buffer_.size() - 1;
  while(index >= 0) {
    bits_in_buffer_++;
    buffer_ >>= 1;
    if (tmp_buffer_.at(index)) {
      buffer_ |= 0x80;
    }
    if (bits_in_buffer_ == 8) {
      f_out_.put(buffer_);
      bits_in_buffer_ = 0;
      buffer_ = 0;
    }
    index--;
  }
  tmp_buffer_.clear();
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
    case CodingType::OMEGA: {
      encodeOmega(sign_val);
      break;}
    case CodingType::DELTA: {
      encodeDelta(sign_val);
      break;}
    case CodingType::GAMMA: {
      encodeGamma(sign_val);
      break;}
    case CodingType::FIBONACCI: {
      encodeFibonacci(sign_val);
      break;}
  }
  outputTempBuffer();
}

void Coder::endEncoding() {
  size_t sign_val = dict_.size();
  switch (coding_type_) {
    case CodingType::OMEGA: {
      encodeOmega(sign_val);
      break;}
    case CodingType::DELTA: {
      encodeDelta(sign_val);
      break;}
    case CodingType::GAMMA: {
      encodeGamma(sign_val);
      break;}
    case CodingType::FIBONACCI: {
      encodeFibonacci(sign_val);
      break;}
  }
  outputTempBuffer();
}

void Coder::encodeGamma(size_t val) {
  size_t n = 64 - __builtin_clzll(val);
  if(val == 0) {
    writeBit(0);
    return;
  }
  while(val > 0) {
    writeBit(val & 0b1);
    val >>= 1;
  }
  for(int i = 0; i < n - 1; i++) {
    writeBit(0);
  }
}

void Coder::encodeDelta(size_t val) {
  size_t n = 64 - __builtin_clzll(val);
  size_t k = 64 - __builtin_clzll(n);
  while(val > 1) {
    writeBit(val & 0b1);
    val >>= 1;
  }
  while(n > 0) {
    writeBit(n & 0b1);
    n >>= 1;
  }
  for(int i = 0; i < k - 1; i++) {
    writeBit(0);
  }
}

void Coder::encodeOmega(size_t val) {
  writeBit(0);
  while(val > 1) {
    writeNumber(val);
    val = 64 - __builtin_clzll(val);
    val--;
  }
}

void Coder::encodeFibonacci(size_t val) {
  writeBit(1);
  int index = getFirstLowerEqualFib(val);
  while(val > 0) {
    writeBit(1);
    val -= fibonacci_sequence_.at(index);
    index--;
    while(index >= 0 && fibonacci_sequence_.at(index) > val) {
      writeBit(0);
      index--;
    }
  }
}

int Coder::getFirstLowerEqualFib(size_t number) {
  int index = 0;
  while(index < fibonacci_sequence_.size() && fibonacci_sequence_.at(index) <= number) {
    index++;
  }
  if(index == fibonacci_sequence_.size()) {
    for(; fibonacci_sequence_.at(index - 1) <= number; index++) {
      fibonacci_sequence_.push_back(fibonacci_sequence_.at(index - 1) + fibonacci_sequence_.at(index - 2));
    }
    index -= 2;
  } else if(index != 0){
    index--;
  }
  return index;
}

void Coder::calculateStatistics() {
  int val = f_out_.get();
  while(!f_out_.eof()) {
    updateOutputFreq(val);
    val = f_out_.get();
  }
  long double sum = 0.0;
  size_t input_size = 0;
  for(auto pair : input_counter_) {
    input_size += pair.second;
  }
  std::cout << "Dlugosc kodowanego pliku: " << input_size << std::endl;
  size_t output_size = 0;
  for(auto pair : output_counter_) {
    output_size += pair.second;
  }
  std::cout << "Dlugosc kodu wynikowego: " << output_size << std::endl;
  for(auto pair : input_counter_) {
    long double prob = (long double)pair.second / (long double)input_size;
    sum -= prob * std::log2(prob);
  }
  std::cout << "Stopien kompresji: " << output_size / (double) input_size << std::endl;
  std::cout << "Entropia pliku wejsciowego: " << sum << std::endl;
  sum = 0.0;
  for(auto pair : output_counter_) {
    long double prob = (long double)pair.second / (long double)output_size;
    sum -= prob * std::log2(prob);
  }
  std::cout << "Entropia pliku wyjsciowego: " << sum << std::endl;
}

void Coder::updateOutputFreq(int val) {
  if(output_counter_.find(val) == output_counter_.end()) {
    output_counter_[val] = 1;
  } else {
    output_counter_[val]++;
  }
}

void Coder::updateInputFreq(int val) {
  if(input_counter_.find(val) == input_counter_.end()) {
    input_counter_[val] = 1;
  } else {
    input_counter_[val]++;
  }
}
