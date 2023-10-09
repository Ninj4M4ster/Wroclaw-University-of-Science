#include <iostream>
#include <vector>

/**
 * Calculate prefix function.
 * Prefix functions is an array, which returns the next state based on current state in matching
 * if characters in pattern and input text do not match.
 *
 * @param pattern Pattern string.
 * @return Prefix function array pointing to unsigned long long int type value.
 */
std::vector<std::size_t> compute_prefix_function(std::u32string pattern) {
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
void kmp(std::u32string input, std::u32string pattern) {
  std::size_t n = input.length();
  std::size_t m = pattern.length();
  std::vector<std::size_t> prefix_function = compute_prefix_function(pattern);
  std::size_t q = 0;
  for(std::size_t i = 0; i < n; i++) {
    while(q > 0 && pattern.at(q) != input.at(i)) {
      q = prefix_function.at(q - 1);
    }
    if(pattern.at(q) == input.at(i))
      q++;
    if(q == m) {
      std::cout << "Wzorzec wystepuje z przesunieciem " << i - m + 1 << std::endl;
      q = prefix_function.at(q - 1);
    }
  }
}

int main(int argc, char* argv[]) {
  std::u32string input = U"aasłdaabbdfbdfaabbaaaasłdaab";
  std::u32string pattern = U"aasłd";
  kmp(input, pattern);
}