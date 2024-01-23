#include "inc/genetic_algorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int population_size,
                                   double mutation_probability,
                                   bool island_type_population,
                                   long long int max_iterations_count,
                                   long long int number_of_generations,
                                   std::shared_ptr<CycleCreator> cycle_creator) {
  population_size_ = population_size;
  mutation_probability_ = mutation_probability;
  island_type_population_ = island_type_population;
  max_iterations_count_ = max_iterations_count;
  number_of_generations_ = number_of_generations;
  cycle_creator_ = cycle_creator;

  // TODO(Jakub Drzewiecki): Consider checking if permutation has been already added.
  for(int i = 0; i < population_size; i++) {
    std::vector<int> new_individual = cycle_creator->createRandomCycle();
    population_.push_back({new_individual, cycle_creator_->calculateCycleCost(new_individual)});
  }
  islands_.push_back(population_);

  selection_size_ = population_size_ / 10;
}

void GeneticAlgorithm::start() {
  selectIndividuals();
  crossIndividuals();
}

/**
 * Selection function. It implements rank method of selection.
 *
 * @return
 */
void GeneticAlgorithm::selectIndividuals() {
  static auto compare =
      [](const std::pair<std::vector<int>, long long int> & left,
          const std::pair<std::vector<int>, long long int> & right) {
    return left.second > right.second;
  };
  std::priority_queue<std::pair<std::vector<int>, long long int>,
      std::vector<std::pair<std::vector<int>, long long int>>,
      decltype(compare)> pq(compare);
  std::vector<std::pair<std::vector<int>, long long int>> selection;
  for(auto p : population_) {
    pq.push(p);
  }
  while(!pq.empty() && selection.size() < selection_size_) {
    auto val = pq.top();
    pq.pop();
    selection.push_back(val);
  }
  population_ = selection;
}

void GeneticAlgorithm::crossIndividuals() {
  while(population_.size() < population_size_) {
    std::uniform_int_distribution<int> distribution{0, static_cast<int>(population_.size() - 1)};
    int first_index = distribution(random_gen_);
    int second_index = first_index;
    while(second_index == first_index) {
      second_index = distribution(random_gen_);
    }
    std::pair<std::vector<int>, long long> child;
    switch(curr_hybridization_type_) {
      case HybridizationType::PMX:
        child = pmx(population_.at(first_index), population_.at(second_index));
        break;
      case HybridizationType::OX1:
        break;
    }
    population_.push_back(child);
  }
}

std::pair<std::vector<int>, long long> GeneticAlgorithm::pmx(
    std::pair<std::vector<int>, long long> first_parent,
    std::pair<std::vector<int>, long long> second_parent) {
  std::uniform_int_distribution<int> distribution{0, static_cast<int>(first_parent.first.size() - 1)};
  int first_index = distribution(random_gen_);
  int second_index = first_index;
  while(second_index == first_index) {
    second_index = distribution(random_gen_);
  }
  if(first_index > second_index) {
    std::swap(first_index, second_index);
  }
  if(first_index == 0 && second_index == first_parent.first.size() - 1) {
    while(first_index == 0) {
      first_index = distribution(random_gen_);
    }
  }
  std::vector<bool> taken_positions(first_parent.first.size(), false);
  std::vector<bool> copied_values(first_parent.first.size(), false);
  std::pair<std::vector<int>, long long> child = {std::vector<int>(first_parent.first.size(), -1), 0};
  for(int i = first_index; i <= second_index; i++) {
    child.first.at(i) = first_parent.first.at(i);
    taken_positions.at(i) = true;
    copied_values.at(child.first.at(i)) = true;
  }
  for(int i = first_index; i <= second_index; i++) {
    if(copied_values.at(second_parent.first.at(i)))
      continue;
    int to_copy = second_parent.first.at(i);
    int already_copied = first_parent.first.at(i);
    int index = 0;
    for(; index < second_parent.first.size(); index++) {
      if(second_parent.first.at(index) == already_copied)
        break;
    }
    while(taken_positions.at(index)) {
      already_copied = first_parent.first.at(index);
      index = 0;
      for(; index < second_parent.first.size(); index++) {
        if(second_parent.first.at(index) == already_copied)
          break;
      }
    }
    child.first.at(index) = to_copy;
    taken_positions.at(index) = true;
    copied_values.at(to_copy) = true;
  }
  for(int i = 0; i < child.first.size(); i++) {
    if(!copied_values.at(second_parent.first.at(i))) {
      child.first.at(i) = second_parent.first.at(i);
    }
  }
  child.second = cycle_creator_->calculateCycleCost(child.first);
  return child;
}