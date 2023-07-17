#ifndef AOD_L3_RADIX_HEAP_RADIX_BUCKETS_H_
#define AOD_L3_RADIX_HEAP_RADIX_BUCKETS_H_

#include <vector>
#include <unordered_map>
#include <iostream>
#include <limits>

class RadixBuckets {
 public:
  void push(std::pair<unsigned int, unsigned long int> key);
  std::pair<unsigned int, unsigned long int> pop();
  bool empty() const;
  void print();

 private:
  std::vector<std::vector<std::pair<unsigned int, unsigned long int>>> buckets_ =
      std::vector<std::vector<std::pair<unsigned int, unsigned long int>>>
          (65, std::vector<std::pair<unsigned int, unsigned long int>>()) ;
  std::vector<std::pair<unsigned int, unsigned long int>> buckets_min_ =
      std::vector<std::pair<unsigned int, unsigned long int>>(65,
          {0, std::numeric_limits<unsigned long int>::max()});

  unsigned long int last_deleted_ = 0;
  std::size_t size_ = 0;

  unsigned int bucket_number(unsigned long int key) const;
  void redistribute();
};

void RadixBuckets::push(std::pair<unsigned int, unsigned long int> key) {
  unsigned int index = bucket_number(key.second);
  buckets_.at(index).push_back(key);
  if(key.second < buckets_min_.at(index).second) {
    buckets_min_.at(index) = key;
  }
  size_++;
}

std::pair<unsigned int, unsigned long> RadixBuckets::pop() {
  if(!buckets_.at(0).empty()) {
    auto return_val = buckets_.at(0).at(buckets_.at(0).size() - 1);
    buckets_.at(0).pop_back();
    size_--;
    return return_val;
  } else {
    redistribute();
    auto return_val = buckets_.at(0).at(buckets_.at(0).size() - 1);
    buckets_.at(0).pop_back();
    size_--;
    return return_val;
  }
}

void RadixBuckets::redistribute() {
  size_t index = 1;
  for (; buckets_.at(index).empty(); index++);
  last_deleted_ = buckets_min_.at(index).second;

  for (auto & pair : buckets_.at(index)) {
    unsigned int new_index = bucket_number(pair.second);
    buckets_.at(new_index).emplace_back(pair);
    if(pair.second < buckets_min_.at(new_index).second)
      buckets_min_.at(new_index) = pair;
  }

  buckets_.at(index).clear();
  buckets_min_.at(index) = {0, std::numeric_limits<unsigned long>::max()};
}

bool RadixBuckets::empty() const {
  return size_ == 0;
}

void RadixBuckets::print() {
  std::size_t index = 0;
  for(auto & bucket : buckets_) {
    if(!bucket.empty()) {
      std::cout << "Index " << index << "\n";
      for(auto & pair : bucket) {
        std::cout << pair.first << " -> " << pair.second << " ";
      }
      std::cout << "\n";
    }
    index++;

  }
}

unsigned int RadixBuckets::bucket_number(unsigned long int key) const {
  return key == last_deleted_ ? 0 : 64 - __builtin_clzll(key ^ last_deleted_);
}

#endif //AOD_L3_RADIX_HEAP_RADIX_BUCKETS_H_
