#include <iostream>
#include <fstream>
#include <unordered_map>
#include <math.h>

long long int sumAllValues(std::unordered_map<char, long long int> & map) {
  long long int result = 0;
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
  std::ifstream f;
  f.open(argv[1], std::ios::binary);
  if(!f.is_open()) {
    std::cerr << "Nie udalo sie otworzyc podanego pliku.\n";
    return -1;
  }

  std::unordered_map<char , long long int> sign_count;
  std::unordered_map<char , std::unordered_map<char, long long int>> prev_sign_count;
  char curr_char;
  f.read(&curr_char, 1);
  char prev_char = '\x00';
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
      prev_sign_count[curr_char] = std::unordered_map<char, long long int>{};
      prev_sign_count[curr_char][prev_char] = 1;
    }
    prev_char = curr_char;
    f.read(&curr_char, 1);
  }

  // calculate simple entropy
  auto iter = sign_count.begin();
  long double first_entropy = 0.0;
  long long int all_signs_sum = sumAllValues(sign_count);
  while(iter != sign_count.end()) {
    long double probability = (long double)iter->second / (long double) all_signs_sum;
    first_entropy -= probability * std::log2(probability);
    iter++;
  }

  std::cout << "Zwykla entropia: " << first_entropy << std::endl;

  // calculate conditional entropy
  long double conditional_entropy = 0.0;
  for(auto & set : prev_sign_count) {
    long double prev_sign_probability = (long double)sign_count.at(set.first) / (long double) all_signs_sum;
    long double inner_sum = 0.0;
    for(auto & prev_sign_set : set.second) {
      long double conditional_probability = (long double)prev_sign_set.second / (long double)sign_count.at(set.first);
      inner_sum -= conditional_probability * std::log2(conditional_probability);
    }
    conditional_entropy += prev_sign_probability * inner_sum;
  }

  std::cout << "Entropia warunkowa: " << conditional_entropy << std::endl;

  if(first_entropy > conditional_entropy) {
    std::cout << "Roznica: " << first_entropy - conditional_entropy << std::endl;
  } else {
    std::cout << "Roznica: " << conditional_entropy - first_entropy << std::endl;
  }

  f.close();
}