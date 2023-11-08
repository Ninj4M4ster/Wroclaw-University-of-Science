#include "decoder.h"

/**
 * Constructor. Initializes helper arrays, start cdf values.
 */
Decoder::Decoder() {
  for(int i = 0; i < 256; i++) {
    symbols_indexes.at(i) = i+1;
    index_to_char.at(i+1) = i;
  }
  for(int i = 0; i <= 257; i++) {
    cdf.at(i) = 257 - i;
  }
  frequencies.at(0) = 0;
}

/**
 * Decompress data from given file and print output in given output file.
 *
 * @param file_name Name of file to be decompressed.
 * @param output_file Name of output file.
 */
void Decoder::decompress_data(std::string& file_name, std::string output_file) {
  int L = 0, R = 0xFFFF;
  std::fstream f, f_out;
  f.open(file_name, std::ios::binary | std::ios::in);
  f_out.open(output_file, std::ios::out);
  if(!f.is_open()) {
    std::cerr << "Nie udalo sie otworzyc pliku\n";
    throw std::exception();
  }
  init_V(f);
  while(last_8_iterations_counter > 0) {
    int sym_index = decode_sign(f, L, R);
    if(sym_index == 257)
      break;
    int character = index_to_char.at(sym_index);
    f_out.put(character);
    update_cdf(sym_index);
    if(last_8_iterations)
      last_8_iterations_counter--;
  }
  f.close();
  f_out.close();
}

/**
 * Initialize V value used later for decoding.
 *
 * @param f Input file.
 */
void Decoder::init_V(std::fstream & f) {
  for(int i = 0; i < 16; i++) {
    V = 2 * V + get_bit(f);
  }
}

/**
 * Get single bit from given file.
 *
 * @param f Input file.
 * @return Single bit, either 0 or 1.
 */
int Decoder::get_bit(std::fstream &f) {
  if(bits_in_buffer == 0) {
    buffer = f.get();
    if(f.eof()) {  // decode last 8 bits
      last_8_iterations = true;
    }
    bits_in_buffer = 8;
  }
  int bit = buffer & 1;
  bits_in_buffer--;
  buffer >>= 1;
  return bit;
}

/**
 * Decode single sign from input file and return it (index of the sign is returned).
 *
 * @param f Input file.
 * @param L Left end of the current range.
 * @param R Right end of the current range.
 * @return Index of the range of the decoded symbol.
 */
int Decoder::decode_sign(std::fstream &f, int &L, int &R) {
  int sign;
  int Range = R - L;
  int cumulative_freq = ((((V - L) + 1) * cdf.at(0) - 1) / Range);
  for(sign = 1; cdf.at(sign) > cumulative_freq; sign++);
  R = L + (Range * cdf.at(sign - 1)) / cdf.at(0);
  L = L + (Range * cdf.at(sign)) / cdf.at(0);
  while(true) {
    if (R < kHalf) {

    } else if(L >= kHalf) {
      V -= kHalf;
      L -= kHalf;
      R -= kHalf;
    } else if(L >= kQuarter && R < k3Quarters) {
      V -= kQuarter;
      L -= kQuarter;
      R -= kQuarter;
    } else {
      break;
    }
    L = L * 2;
    R = R * 2;
    V = V * 2 + get_bit(f);
  }
  return sign;
}


/**
 * Update cumulative distribution function.
 * This method also updates frequencies and moves index of the given char backwards
 * so that cumulative distribution function stays non-descending.
 * @param c
 */
void Decoder::update_cdf(int c) {
  if(cdf.at(0) == 16383) {
    int cumulative_freq = 0;
    for(int i = 257; i >= 0; i--) {
      frequencies.at(i) = (frequencies.at(i) + 1) / 2;
      cdf.at(i) = cumulative_freq;
      cumulative_freq += frequencies.at(i);
    }
  }
  // find new index for given char
  int i;
  for(i = c; frequencies.at(i) == frequencies.at(i-1); i--) {}
  // update helper arrays
  if(i < c) {
    int ch_i, ch_symbol;
    ch_i = index_to_char.at(i);
    ch_symbol = index_to_char.at(c);
    index_to_char.at(i) = ch_symbol;
    index_to_char.at(c) = ch_i;
    symbols_indexes.at(ch_i) = c;
    symbols_indexes.at(ch_symbol) = i;
  }
  frequencies.at(i) += 1;
  while(i > 0) {
    i--;
    cdf.at(i) += 1;
  }
}