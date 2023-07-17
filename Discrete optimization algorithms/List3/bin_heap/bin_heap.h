#ifndef AOD_L3_BIN_HEAP_BIN_HEAP_H_
#define AOD_L3_BIN_HEAP_BIN_HEAP_H_

#include <vector>
#include <unordered_map>
#include <iostream>

class BinHeap {
 public:
  void push(std::pair<unsigned int, unsigned long int> key);
  std::pair<unsigned int, unsigned long int> pop();
  void decreaseKey(std::pair<unsigned int, unsigned long int> key, unsigned long int new_key_val);
  bool empty();
  void print();
 private:
  std::vector<std::pair<unsigned int, unsigned long int>> heap_;
  std::unordered_map<unsigned int, std::size_t> indexes_map_;

  void heapify(std::size_t index);
};

void BinHeap::push(std::pair<unsigned int, unsigned long int> key) {
  std::size_t index = heap_.size();
  heap_.push_back(key);
  indexes_map_[key.first] = index;
  while(index > 0) {
    std::size_t parent_index = (index - 1) / 2;
    if(heap_.at(parent_index).second < heap_.at(index).second) {
      break;
    } else {
      std::swap(indexes_map_[heap_.at(parent_index).first], indexes_map_[key.first]);
      std::swap(heap_.at(parent_index), heap_.at(index));
      index = parent_index;
    }
  }
}

std::pair<unsigned int, unsigned long int> BinHeap::pop() {
  std::size_t heap_size = heap_.size();
  if(heap_size == 0)
    return {};

  auto return_val = heap_.at(0);
  std::swap(indexes_map_[heap_.at(0).first], indexes_map_[heap_.at(heap_size - 1).first]);
  std::swap(heap_.at(0), heap_.at(heap_size - 1));
  heap_.pop_back();
  indexes_map_.erase(indexes_map_.find(return_val.first));
  std::size_t index = 0;

  heapify(index);
  return return_val;
}

void BinHeap::heapify(std::size_t index) {
  std::size_t heap_size = heap_.size();

  std::size_t smallest = index;
  std::size_t left_index = (index * 2) + 1;
  std::size_t right_index = (index * 2) + 2;

  if(right_index < heap_size && heap_.at(right_index).second < heap_.at(smallest).second)
    smallest = right_index;
  if(left_index < heap_size && heap_.at(left_index).second < heap_.at(smallest).second)
    smallest = left_index;

  if(smallest != index) {
    std::swap(indexes_map_[heap_.at(smallest).first], indexes_map_[heap_.at(index).first]);
    std::swap(heap_.at(smallest), heap_.at(index));
    heapify(smallest);
  }

}

void BinHeap::decreaseKey(std::pair<unsigned int, unsigned long int> key, unsigned long int new_key_val) {
  std::size_t index = indexes_map_[key.first];
  heap_.at(index).second = new_key_val;
  while(index > 0) {
    std::size_t parent_index = (index - 1) / 2;
    if(heap_.at(parent_index).second < heap_.at(index).second)
      break;
    else {
      std::swap(indexes_map_[heap_.at(parent_index).first], indexes_map_[heap_.at(index).first]);
      std::swap(heap_.at(parent_index), heap_.at(index));
      index = parent_index;
    }
  }
}

inline bool BinHeap::empty() {
  return heap_.empty();
}

void BinHeap::print() {
  std::cout << "Lista\n";
  for(auto key : heap_) {
    std::cout << key.first << " -> " << key.second << ", ";
  }
  std::cout << std::endl;

  std::cout << "Mapa\n";
  auto it = indexes_map_.begin();
  while(it != indexes_map_.end()) {
    std::cout << it->first << " -> " << it->second << ", ";
    it++;
  }
  std::cout << std::endl << std::endl;
}

#endif //AOD_L3_BIN_HEAP_BIN_HEAP_H_
