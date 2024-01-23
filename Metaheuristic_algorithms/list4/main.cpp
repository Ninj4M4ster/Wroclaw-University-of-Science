#include "graph_handler.cpp"
#include "cycle_creator.cpp"
#include "genetic_algorithm.cpp"

static constexpr int population_size = 2000;
static constexpr double mutation_probability = 0.1;
static constexpr bool island_type = false;
static constexpr long long int number_of_generations = 7000;

size_t findMin(std::vector<long long> & arr) {
  size_t res = std::numeric_limits<size_t>::max();
  for(auto val : arr) {
    if(val < res)
      res = val;
  }
  return res;
}

double arrayMean(std::vector<long long> & arr) {
  size_t sum = 0;
  for(auto val : arr) {
    sum += val;
  }
  return static_cast<double>(sum) / static_cast<double>(arr.size());
}

int main() {
  std::vector<std::string> graph_names{"data/xqf131.tsp", "data/xqg237.tsp",
                                       "data/pma343.tsp", "data/pka379.tsp",
                                       "data/bcl380.tsp", "data/pbl395.tsp",
                                       "data/pbk411.tsp", "data/pbn423.tsp",
                                       "data/pbm436.tsp", "data/xql662.tsp",
                                       "data/xit1083.tsp", "data/icw1483.tsp",
                                       "data/djc1785.tsp", "data/dcb2086.tsp",
                                       "data/pds2566.tsp"};
  for(int i = 0; i < 15; i++) {
    std::cout << graph_names.at(i) << std::endl;
    std::vector<long long> results;
    for(int j = 0; j < 3; j++) {
      GraphHandler gh(graph_names.at(i));
      std::shared_ptr<CycleCreator> cycle_creator =
          std::make_shared<CycleCreator>(gh.getMst(), gh.getGraph());
      std::shared_ptr<GeneticAlgorithm> genetic_algorithm =
          std::make_shared<GeneticAlgorithm>(population_size,
                                             mutation_probability,
                                             island_type,
                                             number_of_generations,
                                             cycle_creator);

      std::pair<std::vector<int>, long long> result = genetic_algorithm->start();
      std::cout << "Result: " << result.second << std::endl;
      results.push_back(result.second);
    }
    std::cout << "Finished\n";
    std::cout << "Best result: " << findMin(results) << std::endl;
    std::cout << "Mean result: " << arrayMean(results) << std::endl;
  }
}