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
 *
 * @param file_name Name of the file to be compressed.
 */
void Encoder::compress_data(std::string & file_name) {
  unsigned int L = 0, R = 0xFFFFFFFFU;
  std::fstream f;
  f.open(file_name, std::ios::binary | std::ios::in);
  if(!f.is_open()) {
    std::cerr << "Nie udalo sie otworzyc pliku\n";
    throw std::exception();
  }
  char c;
  f.read(&c, 1);
  while(!f.eof()) {
    unsigned int sym_index = symbols_indexes.at((int)c + kCharToIntOffset);
    encode_sign(sym_index, L, R);
    update_cdf(sym_index);
    f.read(&c, 1);
  }
  f.close();

  // write L to buffer
  std::cout << buffer.size() / 8 << std::endl;
  std::cout << cdf.at(0) << std::endl;
}

/**
 * Encode one sign and update L and R values.
 *
 * @param sign Sign to be encoded.
 * @param L Left end of the current range.
 * @param R Right end of the current range.
 */
void Encoder::encode_sign(unsigned int sign,
                 unsigned int & L,
                 unsigned int & R) {
  size_t Range = (size_t)R - (size_t)L  + 1;
  R = L + (Range * cdf.at(sign - 1)) / cdf.at(0) - 1;
  L = L + (Range * cdf.at(sign)) / cdf.at(0);
  for(;;) {
    if(R < kHalf) {
      buffer.push_back(false);
      while(counter > 0) {
        buffer.push_back(true);
        counter--;
      }
    } else if(kHalf <= L) {
      buffer.push_back(true);
      while(counter > 0) {
        buffer.push_back(false);
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
    L <<= 1;
    R <<= 1;
    R += 1;
  }
}

/**
 * Update cumulative distribution function.
 * This method also updates frequencies and moves index of the given char backwards
 * so that cumulative distribution function stays non-descending.
 * @param c
 */
void Encoder::update_cdf(unsigned int c) {
  // find new index for given char
  unsigned int i;
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

/**
 * Calculate entropy for previously encoded file.
 *
 * @return Entropy value.
 */
long double Encoder::calculate_entropy() {
  long double sum = 0.0;
  for(auto val : frequencies) {
    long double prob = (long double)(val) / (long double)(cdf.at(0) - 257);
    if(prob == 0.0)
      continue;
//    std::cout << prob << std::endl;
    sum -= prob * std::log2(prob);
  }
  return sum;
}

/**
 * Save compressed data to given file name.
 * Firstly frequency table is written and then the compressed data.
 *
 * @param file_name Name of the output file.
 */
void Encoder::save_compressed_data(std::string file_name) {
  std::bitset<8> bit_buf;
  int index = 0;
  std::fstream f;
  f.open(file_name, std::ios::out);
  for(auto val : buffer) {
    bit_buf.set(index, val);
    index = (index + 1) % 8;
    if(index == 0) {
      char c = bit_buf.to_ulong();
      f.write(&c, 1);
    }
  }

  for(int i = 0; i < 32; i++) {

  }

  f.close();
}