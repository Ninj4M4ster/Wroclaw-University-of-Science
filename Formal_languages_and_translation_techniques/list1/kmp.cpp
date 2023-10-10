#include <iostream>
#include <vector>
#include <fstream>
#include <codecvt>
#include <locale>
#include <sstream>

/**
 * Calculate prefix function.
 * Prefix functions is an array, which returns the next state based on current state in matching
 * if characters in pattern and input text do not match.
 *
 * @param pattern Pattern string.
 * @return Prefix function array pointing to unsigned long long int type value.
 */
std::vector<std::size_t> compute_prefix_function(std::wstring pattern) {
  std::size_t m = pattern.length();
  std::vector<std::size_t> prefix_function(m);
  prefix_function.at(0) = 0;
  std::size_t k = 0;
  for(int q = 1; q < m; q++) {
    while(k > 0 && pattern.at(k) != pattern.at(q))
      k = prefix_function.at(k - 1);
    if(pattern.at(k) == pattern.at(q))
      k++;
    prefix_function.at(q) = k;
  }
  return prefix_function;
}

/**
 * Print all occurs of the given pattern in given input string.
 * Firstly, prefix function is calculated.
 * Then, input string is iterated over and patterns are detected using prefix function.
 *
 * @param pattern Pattern string.
 * @param input Input string.
 */
std::vector<std::size_t> kmp(std::wstring input, std::wstring pattern) {
  std::size_t n = input.length();
  std::size_t m = pattern.length();
  std::vector<std::size_t> prefix_function = compute_prefix_function(pattern);
  std::size_t q = 0;
  std::vector<std::size_t> pattern_indexes;
  for(std::size_t i = 0; i < n; i++) {
    while(q > 0 && pattern.at(q) != input.at(i)) {
      q = prefix_function.at(q - 1);
    }
    if(pattern.at(q) == input.at(i))
      q++;
    if(q == m) {
      pattern_indexes.push_back(i - m + 1);
      q = prefix_function.at(q - 1);
    }
  }
  return pattern_indexes;
}

int wmain(int argc, wchar_t** argv) {
  if(argc != 3) {
    std::cerr << "Bad numer of arguments\n";
    return -1;
  }

  // read pattern
  std::wstring pattern = argv[1];

  // open file
  std::wifstream f;
  f.open(argv[2], std::ifstream::in);
  if(f.bad()) {
    std::cerr << "Could not open file\n";
    f.close();
    return -1;
  }
  f.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
  std::wstringstream wss;
  wss << f.rdbuf();
  f.close();

  std::wstring input = wss.str();

  std::vector<std::size_t> results = kmp(input, pattern);

  std::cout << "[";
  for(std::size_t i = 0; i < results.size(); i++) {
    if(i == results.size() - 1) {
      std::cout << results.at(i);
    } else {
      std::cout << results.at(i) << ", ";
    }
  }
  std::cout << "]\n";
  return 0;
}