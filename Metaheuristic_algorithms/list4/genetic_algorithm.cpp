#include "inc/genetic_algorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int population_size,
                                   double mutation_probability,
                                   std::shared_ptr<CycleCreator> cycle_creator,
                                   bool island_type_population,
                                   long long int max_iterations_count,
                                   long long int number_of_generations) {
  population_size_ = population_size;
  mutation_probability_ = mutation_probability;
  island_type_population_ = island_type_population;
  max_iterations_count_ = max_iterations_count;
  number_of_generations_ = number_of_generations;
  cycle_creator_ = cycle_creator;

  for(int i = 0; i < population_size; i++) {
    std::vector<int> new_individual = cycle_creator->createRandomCycle();
    if(isIndividualAlreadyInPopulation(new_individual)) {
      i--;
      continue;
    }
    population_.push_back(new_individual);
  }
}