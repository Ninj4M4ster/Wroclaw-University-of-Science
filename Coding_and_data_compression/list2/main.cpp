#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <cmath>
#include <bitset>

/**
 * Calculate probability of the characters in given file.
 *
 * @param file_name File to open.
 * @return Map of probabilities of finding given chars in the given file.
 */
std::unordered_map<int, long double> calculate_probability(std::string & file_name,
                                                           size_t & signs_count) {
  std::unordered_map<int, std::size_t> incidence;

  std::fstream f;
  f.open(file_name.c_str(), std::ios::binary | std::ios::in);
  if(!f.is_open()) {
    std::cerr << "Nie udalo sie otworzyc pliku\n";
    throw std::exception();
  }
  char c;
  f.read(&c, 1);
  while(!f.eof()) {
    if(incidence.find((int)c + 128) != incidence.end()) {  // char found in map
      incidence[(int)c + 128] += 1;
    } else {
      incidence[(int)c + 128] = 1;
    }
    signs_count++;
    f.read(&c, 1);
  }
  f.close();

  std::unordered_map<int, long double> probability;

  for(auto pair : incidence) {
    probability[(int)pair.first] = (long double)pair.second / (long double)signs_count;
  }

  return probability;
}

void encode_sign(unsigned int sign,
                 unsigned int & L,
                 unsigned int & R,
                 std::vector<size_t> & cdf,
                 size_t & counter,
                 std::vector<bool> & buffer) {
  size_t Range = (size_t)R - (size_t)L  + 1;
  R = L + (Range * cdf.at(sign - 1)) / cdf.at(0) - 1;
  L = L + (Range * cdf.at(sign)) / cdf.at(0);
  for(;;) {
    if(R < 0x80000000U) {
      buffer.push_back(false);
      while(counter > 0) {
        buffer.push_back(true);
        counter--;
      }
    } else if(0x80000000U <= L) {
      buffer.push_back(true);
      while(counter > 0) {
        buffer.push_back(false);
        counter--;
      }
      L = L - 0x80000000U;
      R = R - 0x80000000U;
    } else if(L >= 0x40000000U && R < 0xC0000000U) {
      counter++;
      L = L - 0x40000000U;
      R = R - 0x40000000U;
    } else {
      break;
    }
    L <<= 1;
    R <<= 1;
    R += 1;
  }
}

void update_cdf(std::vector<size_t> & cdf,
                std::vector<unsigned int> & symbols_indexes,
                unsigned int c,
                std::vector<size_t> & frequencies,
                std::vector<int> & index_to_char) {
  unsigned int i;
  for(i = c; frequencies.at(i) == frequencies.at(i-1); i--) {}
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

unsigned int compress_data(std::string & file_name,
                     std::vector<size_t> & cdf,
                     std::vector<bool> & buffer,
                     std::vector<unsigned int> & symbols_indexes,
                     std::vector<size_t> & frequencies,
                     std::vector<int> & index_to_char) {
  unsigned int L = 0, R = 0xFFFFFFFFU;
  size_t counter = 0;
  std::fstream f;
  f.open(file_name, std::ios::binary | std::ios::in);
  if(!f.is_open()) {
    std::cerr << "Nie udalo sie otworzyc pliku\n";
    throw std::exception();
  }
  char c;
  f.read(&c, 1);
  while(!f.eof()) {
    unsigned int sym_index = symbols_indexes.at((int)c + 128);
    encode_sign(sym_index, L, R, cdf, counter, buffer);
    update_cdf(cdf, symbols_indexes, sym_index, frequencies, index_to_char);
    f.read(&c, 1);
  }
  f.close();

//  for(auto val : buffer) {
//    std::cout << val << " ";
//  }
//  std::cout << "\n";
  return L;
}

void save_compressed_data(std::string file_name,
                          std::vector<bool> & buffer,
                          unsigned int L) {
  std::bitset<32> x(L);
  std::bitset<8> buf;
  int index = 0;
  std::fstream f;
  f.open(file_name, std::ios::out);
  for(auto val : buffer) {
    buf.set(index, val);
    index = (index + 1) % 8;
    if(index == 0) {
      char c = buf.to_ulong();
      f.write(&c, 1);
    }
  }

  for(int i = 0; i < 32; i++) {

  }

  f.close();
}

/**
 * Calculate entropy for given probabilities of occurrences of characters.
 *
 * @param probability Probabilities of occurrences of characters in a file.
 * @return Entropy value.
 */
long double calculate_entropy(std::unordered_map<int, long double> & probability) {
  long double sum = 0.0;
  for(auto pair : probability) {
    sum -= pair.second * std::log2(pair.second);
  }
  return sum;
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cerr << "Wrong number of arguments\n";
    return -1;
  }
  std::string file_name = argv[1];
  size_t signs_count = 0;
  std::unordered_map<int, long double> probability = calculate_probability(file_name, signs_count);
  std::vector<unsigned int> symbols_indexes(256);
  std::vector<int> index_to_char(257);
for(int i = 0; i < 256; i++) {
    symbols_indexes.at(i) = i+1;
    index_to_char.at(i+1) = i;
  }
  std::vector<size_t> cdf(258, 0);
  for(int i = 0; i <= 257; i++) {
    cdf.at(i) = 257 - i;
  }
  std::vector<size_t> frequencies(257, 1);
  frequencies.at(0) = 0;

  std::vector<bool> buffer;
  unsigned int L = compress_data(file_name, cdf, buffer, symbols_indexes, frequencies, index_to_char);
  std::cout << signs_count << std::endl;
  std::cout << buffer.size() / 8 << std::endl;

  save_compressed_data("compressed.txt", buffer, L);


  long double entropy = calculate_entropy(probability);
  std::cout << "Entropia: " << entropy << std::endl;

  return 0;
}