#ifndef AOD_L3_UTILS_GRAPH_PARSER_H_
#define AOD_L3_UTILS_GRAPH_PARSER_H_

#include <vector>
#include <iostream>
#include <fstream>

template<class T, class R, class P>
struct trio {
  T first;
  R second;
  P third;
};

struct trio<unsigned int, unsigned int, unsigned long int> extract_numbers(std::string line) {
  struct trio<unsigned int, unsigned int, unsigned long int> trio_{};
  unsigned int current_number = 0;
  int index = 2;
  while(line[index] != ' ') {
    current_number *= 10;
    current_number += line[index] - '0';
    index++;
  }
  trio_.first = current_number - 1;
  current_number = 0;
  index++;
  while(line[index] != ' ') {
    current_number *= 10;
    current_number += line[index] - '0';
    index++;
  }
  trio_.second = current_number - 1;
  unsigned long int number = 0;
  index++;
  while(index < line.size()) {
    number *= 10;
    number += line[index] - '0';
    index++;
  }
  trio_.third = number;
  return trio_;
}

std::vector<std::vector<std::pair<unsigned int, unsigned long int>>> parse_graph(std::string file_name) {
  std::fstream file;
  file.open(file_name.c_str());
  std::string buffer;
  std::getline(file, buffer);
  while(buffer[0] != 'p') {
    std::getline(file, buffer);
  }
  int index = 5;
  unsigned int nodes_count = 0;
  while(buffer[index] != ' ') {
    nodes_count *= 10;
    nodes_count += buffer[index] - '0';
    index++;
  }

  std::vector<std::vector<std::pair<unsigned int, unsigned long int>>> graph(
      nodes_count, std::vector<std::pair<unsigned int, unsigned long int>>());
  while(buffer[0] != 'a') {
    std::getline(file, buffer);
  }

  struct trio<unsigned int, unsigned int, unsigned long int> trio_ = extract_numbers(buffer);
  graph.at(trio_.first).emplace_back(trio_.second, trio_.third);
  while(std::getline(file, buffer)) {
    if(!buffer.empty()) {
      trio_ = extract_numbers(buffer);
      graph.at(trio_.first).emplace_back(trio_.second, trio_.third);
    }
  }

  file.close();

  return graph;
}

unsigned int extract_number(std::string line) {
  unsigned int number = 0;
  int index = 2;
  while(index < line.size()) {
    number *= 10;
    number += line[index] - '0';
    index++;
  }
  return number - 1;
}

std::vector<unsigned int> parse_sources(std::string file_name) {
  std::fstream file;
  file.open(file_name.c_str());
  std::string buffer;
  std::getline(file, buffer);
  while(buffer[0] != 's') {
    std::getline(file, buffer);
  }
  std::vector<unsigned int> sources = std::vector<unsigned int>();

  sources.emplace_back(extract_number(buffer));
  while(std::getline(file, buffer)) {
    if(!buffer.empty())
      sources.emplace_back(extract_number(buffer));
  }

  file.close();

  return sources;
}

std::pair<unsigned int, unsigned int> extract_pair(std::string line) {
  unsigned int number = 0;
  int index = 2;
  while(line[index] != ' ') {
    number *= 10;
    number += line[index] - '0';
    index++;
  }
  unsigned int sec_number = 0;
  index++;
  while(index < line.size()) {
    sec_number *= 10;
    sec_number += line[index] - '0';
    index++;
  }

  return {number - 1, sec_number - 1};
}

std::unordered_map<unsigned int, std::vector<unsigned int>> parse_pairs(std::string file_name) {
  std::fstream file;
  file.open(file_name.c_str());
  std::string buffer;
  std::getline(file, buffer);
  while(buffer[0] != 'p') {
    std::getline(file, buffer);
  }
  int index = 13;
  unsigned int nodes_count = 0;
  while(buffer[index] != ' ') {
    nodes_count *= 10;
    nodes_count += buffer[index] - '0';
    index++;
  }

  std::unordered_map<unsigned int, std::vector<unsigned int>> map =
      std::unordered_map<unsigned int, std::vector<unsigned int>>(nodes_count);
  while(buffer[0] != 'q') {
    std::getline(file, buffer);
  }

  std::pair<unsigned int, unsigned int> pair = extract_pair(buffer);
  map[pair.first] = std::vector<unsigned int>(1, pair.second);
  while(std::getline(file, buffer)) {
    if(!buffer.empty()) {
      pair = extract_pair(buffer);
      if(map.find(pair.first) == map.end()) {
        map[pair.first] = std::vector<unsigned int>(1, pair.second);
      } else {
        map[pair.first].push_back(pair.second);
      }
    }
  }

  file.close();

  return map;
}

#endif //AOD_L3_UTILS_GRAPH_PARSER_H_
