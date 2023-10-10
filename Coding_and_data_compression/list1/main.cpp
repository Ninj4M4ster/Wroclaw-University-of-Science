#include <iostream>
#include <fstream>
#include <unordered_map>
#include <math.h>

long int sumAllValues(std::unordered_map<unsigned char, long int> & map) {
  long int result = 0;
  auto iter = map.begin();
  while(iter != map.end()) {
    result += iter->second;
    iter++;
  }
  return result;
}

int main(int argc, char* argv[]) {
  if(argc == 1) {
    std::cerr << "Nie podano pliku wejsciowego.\n";
    return -1;
  }
  if(argc > 2) {
    std::cerr << "Podano za dżo argumentów.\n";
    return -1;
  }
  std::fstream f;
  f.open(argv[1], std::fstream::in);
  if(!f.is_open()) {
    std::cerr << "Nie udalo sie otworzyc podanego pliku.\n";
    return -1;
  }

  std::unordered_map<unsigned char, long int> sign_count;
  std::unordered_map<unsigned char, std::unordered_map<unsigned char, long int>> prev_sign_count;
  unsigned char curr_char = f.get();
  unsigned char prev_char = '0';
  while(!f.eof()) {
    // fill normal count
    if(sign_count.find(curr_char) != sign_count.end()) {
      sign_count.at(curr_char) += 1;
    }
    else {
      sign_count[curr_char] = 1;
    }
    // fill count with knowledge of previous sign
    if(prev_sign_count.find(curr_char) != prev_sign_count.end()) {
      if(prev_sign_count.at(curr_char).find(prev_char) != prev_sign_count.at(curr_char).end()) {
        prev_sign_count.at(curr_char).at(prev_char) += 1;
      } else {
        prev_sign_count.at(curr_char)[prev_char] = 1;
      }
    } else {
      prev_sign_count[curr_char] = std::unordered_map<unsigned char, long int>{};
      prev_sign_count.at(curr_char)[prev_char] = 1;
    }
    prev_char = curr_char;
    curr_char = f.get();
  }

  // calculate simple entropy
  auto iter = sign_count.begin();
  long double first_entropy = 0.0;
  long int all_signs_sum = sumAllValues(sign_count);
  while(iter != sign_count.end()) {
    double probability = (double)iter->second / (double) all_signs_sum;
    first_entropy += probability * std::log2(probability);
    iter++;
  }
  first_entropy *= -1.0;

  std::cout << first_entropy << std::endl;

  // calculate conditional entropy
  long double conditional_entropy = 0.0;
  for(auto & set : prev_sign_count) {
    double prev_sign_probability = (double)sign_count.at(set.first) / (double) all_signs_sum;
    long double inner_sum = 0.0;
    for(auto & prev_sign_set : set.second) {
      long double conditional_probability = (double)prev_sign_set.second / (double)sign_count.at(set.first);
      inner_sum += conditional_probability * std::log2(conditional_probability);
    }
    inner_sum *= -1.0;
    conditional_entropy += prev_sign_probability * inner_sum;
  }

  std::cout << conditional_entropy << std::endl;

  f.close();
}