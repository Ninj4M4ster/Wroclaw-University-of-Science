#include "encoder.h"

/**
 * Constructor. Initializes helper arrays, start cdf values.
 */
Encoder::Encoder() {
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
 * Main data compression flow.
 * This method opens given file and compresses it's data using adaptive arithmetic coding.
 * Compressed data will be written to output file with given name.
 *
 * @param file_name Name of the file to be compressed.
 * @param output_file_name Name of the output file.
 */
void Encoder::compress_data(std::string & file_name, std::string output_file_name) {
  int L = 0, R = 0xFFFF;
  std::fstream f, f_out;
  f.open(file_name, std::ios::binary | std::ios::in);
  f_out.open(output_file_name, std::ios::binary | std::ios::out);
  if(!f.is_open()) {
    std::cerr << "Nie udalo sie otworzyc pliku\n";
    throw std::exception();
  }
  int c;
  c = f.get();
  while(!f.eof()) {
    full_frequencies.at(c)++;
    full_bits_counter++;
    int sym_index = symbols_indexes.at(c);
    encode_sign(sym_index, L, R, f_out);
    update_cdf(sym_index);
    c = f.get();
  }
  f.close();
  // encode special sign for decoding to be possible
  encode_sign(257, L, R, f_out);
  counter++;
  // encode remaining bits
  if(L < kQuarter) {
    output_bit(0, f_out);
    while(counter > 0) {
      output_bit(1, f_out);
      counter--;
    }
  } else {
    output_bit(1, f_out);
    while(counter > 0) {
      output_bit(0, f_out);
      counter--;
    }
  }
  f_out.close();
}

/**
 * Encode one sign and update L and R values.
 *
 * @param sign Sign to be encoded.
 * @param L Left end of the current range.
 * @param R Right end of the current range.
 * @param f_out Output file.
 */
void Encoder::encode_sign(int sign,
                          int & L,
                          int & R,
                          std::fstream & f_out) {
  int Range = R - L;
  R = L + (Range * cdf.at(sign - 1)) / cdf.at(0);
  L = L + (Range * cdf.at(sign)) / cdf.at(0);
  while(true) {
    if(R < kHalf) {
      output_bit(0, f_out);
      while(counter > 0) {
        output_bit(1, f_out);
        counter--;
      }
    } else if(kHalf <= L) {
      output_bit(1, f_out);
      while(counter > 0) {
        output_bit(0, f_out);
        counter--;
      }
      L = L - kHalf;
      R = R - kHalf;
    } else if(L >= kQuarter && R < k3Quarters) {
      counter++;
      L = L - kQuarter;
      R = R - kQuarter;
    } else {
      break;
    }
    L = 2 * L;
    R = 2 * R;
  }
}

/**
 * Update cumulative distribution function.
 * This method also updates frequencies and moves index of the given char backwards
 * so that cumulative distribution function stays non-descending.
 * @param c
 */
void Encoder::update_cdf(int c) {
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
    int char_at_i = index_to_char.at(i);
    int char_at_symbol = index_to_char.at(c);
    index_to_char.at(i) = char_at_symbol;
    index_to_char.at(c) = char_at_i;
    symbols_indexes.at(char_at_i) = c;
    symbols_indexes.at(char_at_symbol) = i;
  }
  frequencies.at(i) += 1;
  while(i > 0) {
    i--;
    cdf.at(i) += 1;
  }
}

/**
 * Put given bit to buffer and output buffer if it is full.
 *
 * @param bit Bit to be written.
 * @param f_out Output file.
 */
void Encoder::output_bit(int bit, std::fstream& f_out) {
  outputted_bits++;
  buffer >>= 1;
  if (bit)
    buffer |= 0x80;
  bits_in_buffer++;
  if (bits_in_buffer == 8)
  {
    f_out.put(buffer);
    bits_in_buffer = 0;
  }
}

/**
 * Calculate entropy for previously encoded file.
 *
 * @return Entropy value.
 */
long double Encoder::calculate_entropy() {
  long double sum = 0.0;
  for(int i = 0; i < full_frequencies.size(); i++) {
    unsigned long long freq = full_frequencies.at(i);
    if(freq == 0)
      continue;
    long double prob = (long double)(freq) / (long double)(full_bits_counter);
    sum -= prob * std::log2(prob);
  }
  return sum;
}

/**
 * Calculate mean code length.
 *
 * @return Mean code length.
 */
long double Encoder::mean_code_length() {
  return (long double)outputted_bits / (long double)(full_bits_counter);
}

/**
 * Calculate compression factor.
 *
 * @return Compression factor.
 */
long double Encoder::compression_factor() {
  return (long double)outputted_bits / (long double)8 / (long double)(full_bits_counter);
}
