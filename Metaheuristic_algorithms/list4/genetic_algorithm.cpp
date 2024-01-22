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
}

/**
 * Selection function. It implements rank method of selection.
 *
 * @return
 */
std::vector<std::pair<std::vector<int>, long long int>> GeneticAlgorithm::selectIndividuals() {
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
  return selection;
}

std::vector<std::pair<std::vector<int>, long long>> GeneticAlgorithm::crossIndividuals(
    std::vector<std::pair<std::vector<int>, long long>> individuals) {

}