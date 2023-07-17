#ifndef AOD_L3_BIN_HEAP_BIN_HEAP_H_
#define AOD_L3_BIN_HEAP_BIN_HEAP_H_

#include <vector>
#include <unordered_map>
#include <iostream>

class BinHeap {
 public:
  void push(unsigned long int key);
  unsigned long int pop();
  bool empty();
  void print();
 private:
  std::vector<unsigned long int> heap_;

  void heapify(std::size_t index);
};

void BinHeap::push(unsigned long int key) {
  std::size_t index = heap_.size();
  heap_.push_back(key);
  while(index > 0) {
    std::size_t parent_index = (index - 1) / 2;
    if(heap_.at(parent_index) < heap_.at(index)) {
      break;
    } else {
      std::swap(heap_.at(parent_index), heap_.at(index));
      index = parent_index;
    }
  }
}

unsigned long int BinHeap::pop() {
  std::size_t heap_size = heap_.size();
  if(heap_size == 0)
    return {};

  auto return_val = heap_.at(0);
  std::swap(heap_.at(0), heap_.at(heap_size - 1));
  heap_.pop_back();
  std::size_t index = 0;

  heapify(index);
  return return_val;
}

void BinHeap::heapify(std::size_t index) {
  std::size_t heap_size = heap_.size();

  std::size_t smallest = index;
  std::size_t left_index = (index * 2) + 1;
  std::size_t right_index = (index * 2) + 2;

  if(right_index < heap_size && heap_.at(right_index) < heap_.at(smallest))
    smallest = right_index;
  if(left_index < heap_size && heap_.at(left_index) < heap_.at(smallest))
    smallest = left_index;

  if(smallest != index) {
    std::swap(heap_.at(smallest), heap_.at(index));
    heapify(smallest);
  }

}

inline bool BinHeap::empty() {
  return heap_.empty();
}

void BinHeap::print() {
  std::cout << "Lista\n";
  for(auto key : heap_) {
    std::cout << key << ", ";
  }
  std::cout << std::endl;

}

#endif //AOD_L3_BIN_HEAP_BIN_HEAP_H_
