#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST4_INC_GENETIC_ALGORITHM_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST4_INC_GENETIC_ALGORITHM_H_

#include <queue>
#include "cycle_creator.h"

enum class HybridizationType {
  PMX,
  OX1
};

class GeneticAlgorithm {
 public:
  GeneticAlgorithm(int population_size,
                   double mutation_probability,
                   bool island_type_population,
                   long long int number_of_generations,
                   std::shared_ptr<CycleCreator> cycle_creator);
  std::pair<std::vector<int>, long long> start();
 private:
  int population_size_;
  double mutation_probability_;
  bool island_type_population_;
  long long int max_iterations_count_;
  long long int number_of_generations_;
  std::shared_ptr<CycleCreator> cycle_creator_;
  HybridizationType curr_hybridization_type_ = HybridizationType::PMX;

  int selection_size_;

  std::mt19937_64 random_gen_{std::random_device{}()};

  std::vector<std::pair<std::vector<int>, long long int>> population_;
  std::vector<std::vector<std::pair<std::vector<int>, long long int>>> islands_;

  void selectIndividuals();
  void crossIndividuals();
  void mutateIndividuals();

  std::pair<std::vector<int>, long long int> pmx(
      std::pair<std::vector<int>, long long int> first_parent,
      std::pair<std::vector<int>, long long int> second_parent);

  std::pair<std::vector<int>, long long int> inverse(std::vector<int> permutation);

  std::pair<std::vector<int>, long long int> findBestGene();
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST4_INC_GENETIC_ALGORITHM_H_
