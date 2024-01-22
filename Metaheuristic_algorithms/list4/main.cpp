#include "graph_handler.cpp"
#include "cycle_creator.cpp"
#include "genetic_algorithm.cpp"

static constexpr int population_size = 100;
static constexpr double mutation_probability = 0.2;
static constexpr bool island_type = false;
static constexpr long long int max_iterations_count = 10000;
static constexpr long long int number_of_generations = 1000;

int main() {
  std::string graph_path = "data/bcl380.tsp";
  std::shared_ptr<GraphHandler> graph_handler =
      std::make_shared<GraphHandler>(graph_path);
  std::shared_ptr<CycleCreator> cycle_creator =
      std::make_shared<CycleCreator>(graph_handler->getGraph());
  std::shared_ptr<GeneticAlgorithm> genetic_algorithm =
      std::make_shared<GeneticAlgorithm>(population_size,
                                         mutation_probability,
                                         island_type,
                                         max_iterations_count,
                                         number_of_generations,
                                         cycle_creator);
  genetic_algorithm->start();
}