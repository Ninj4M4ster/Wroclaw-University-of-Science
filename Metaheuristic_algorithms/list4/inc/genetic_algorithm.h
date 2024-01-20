#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST4_INC_GENETIC_ALGORITHM_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST4_INC_GENETIC_ALGORITHM_H_

#include "cycle_creator.h"

enum class HybridizationType {

};

class GeneticAlgorithm {
 public:
  GeneticAlgorithm(int population_size,
                   double mutation_probability,
                   std::shared_ptr<CycleCreator> cycle_creator,
                   bool island_type_population,
                   long long int max_iterations_count,
                   long long int number_of_generations);
 private:
  int population_size_;
  double mutation_probability_;
  bool island_type_population_;
  long long int max_iterations_count_;
  long long int number_of_generations_;
  std::shared_ptr<CycleCreator> cycle_creator_;
  HybridizationType curr_hybridization_type_;

  std::vector<std::vector<int>> population_;
  std::vector<std::vector<std::vector<int>>> islands_;

  bool isIndividualAlreadyInPopulation(std::vector<int> individual);
  std::vector<std::vector<int>> selectIndividuals();
  std::vector<std::vector<int>> crossIndividuals(std::vector<std::vector<int>> individuals);
  std::vector<std::vector<int>> mutateIndividuals(std::vector<std::vector<int>> individuals);
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST4_INC_GENETIC_ALGORITHM_H_
