#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <codecvt>
#include <locale>
#include <sstream>
#include <filesystem>

/**
 * Filter out signs that occur more than once in given input.
 *
 * @param input Input string.
 * @param alphabet Unordered map for storing single characters as keys.
 */
void create_alphabet(std::wstring input, std::unordered_map<wchar_t, bool>& alphabet) {
  for(wchar_t c : input) {
    alphabet[c] = true;
  }
}

/**
 * Check if given pattern is a suffix of given string.
 *
 * @param pattern Pattern to check if it is a suffix.
 * @param pattern_last_index Last index of pattern string.
 * @param checked_string String to check if pattern is it's suffix.
 * @return True, if given pattern is a suffix of given string.
 */
bool isSuffix(std::wstring pattern, long long int pattern_last_index, std::wstring checked_string) {
  long long int checked_string_len = (long long int)checked_string.length() - 1;
  while(pattern_last_index >= 0 && checked_string_len >= 0) {
    if(pattern.at(pattern_last_index) != checked_string.at(checked_string_len))
      return false;
    pattern_last_index--;
    checked_string_len--;
  }
  return true;
}

/**
 * Create transition function.
 * This function finds all distinct signs in given input.
 * Based on that it calculates transition function,
 * which returns a higher value if given character at given state matches pattern,
 * and lower value depending on if the sequence of characters still match a part of the pattern or not.
 *
 * @param pattern Pattern string.
 * @param input Given input string.
 * @param transition_function Vector of unordered maps pointing from char to int,
 *                            representing empty transition function.
 */
void calculate_transition_function(std::wstring pattern,
                                   std::wstring input,
                                   std::vector<std::unordered_map<wchar_t, int>> & transition_function) {
  auto m = (long long int)pattern.length();
  std::unordered_map<wchar_t, bool> alphabet;
  create_alphabet(input, alphabet);

  std::wstring current_pattern_slice;
  for(long long int q = 0; q <= m; q++) {
    if(q > 0) {  // strings indexed from 0, but we need an empty pattern at start
      current_pattern_slice += pattern[q - 1];
    }
    for(auto & iter : alphabet) {
      long long int k = std::min(m + 1, q + 2);
      do {
        k--;
      } while(k > 0 && !isSuffix(pattern, k - 1, current_pattern_slice + iter.first));
      transition_function.at(q)[iter.first] = k;
    }
  }
}

/**
 * Finite automaton matcher.
 * It outputs first index at which pattern starts matching the given input string.
 * Firstly, transition function is calculated.
 * Then input string is checked using this transition function.
 *
 * @param input_text Input string.
 * @param pattern Pattern string.
 * @return First index at which pattern starts matching given input string, or -1 if no matches were found.
 */
std::vector<std::size_t> fa(std::wstring input_text, std::wstring pattern) {
  std::size_t n = input_text.length();
  std::size_t pattern_len = pattern.length();
  std::vector<std::unordered_map<wchar_t, int>> transition_function(
      pattern_len + 1,
      std::unordered_map<wchar_t, int>()
          );
  calculate_transition_function(pattern, input_text, transition_function);
  std::vector<std::size_t> pattern_indexes;
  int current_state = 0;
  for(std::size_t i = 0; i < n; i++) {
    current_state = transition_function.at(current_state)[input_text.at(i)];
    if(current_state == pattern_len) {
      pattern_indexes.push_back(i - pattern_len + 1);
    }
  }
  return pattern_indexes;
}

int wmain(int argc, wchar_t** argv) {
  if(argc != 3) {
    std::cerr << "Bad numer of arguments\n";
    return -1;
  }

  // read pattern;
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

  std::vector<std::size_t> results = fa(input, pattern);

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