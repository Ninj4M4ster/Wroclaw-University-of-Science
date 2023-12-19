#include <iostream>
#include "graph_handler.cpp"
#include "cycle_creator.cpp"
#include "simulated_annealing.cpp"

static constexpr int temperature = 10000;
static constexpr double temperature_scale = 0.8;
static constexpr int epoch_size = 150000;
static constexpr int max_epoch_count = 5000;
static constexpr size_t max_no_result_change_count = 50000;

size_t findMin(std::vector<size_t> & arr) {
  size_t res = std::numeric_limits<size_t>::max();
  for(auto val : arr) {
    if(val < res)
      res = val;
  }
  return res;
}

double arrayMean(std::vector<size_t> & arr) {
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
                                       "data/pbm436.tsp", "data/xql662.tsp"};
  std::vector<std::string> big_graph_names{"data/xit1083.tsp", "data/icw1483.tsp",
                                           "data/djc1785.tsp", "data/dcb2086.tsp",
                                           "data/pds2566.tsp"};
  for(int i = 0; i < 5; i++) {
    std::cout << big_graph_names.at(i) << std::endl;
    std::vector<size_t> results;
    for(int j = 0; j < 100; j++) {
      GraphHandler gh(big_graph_names.at(i));
      std::shared_ptr<CycleCreator> cc =
          std::make_shared<CycleCreator>(gh.getMst(), gh.getGraph());
      SimulatedAnnealing sa(temperature,
                            temperature_scale,
                            epoch_size,
                            max_epoch_count,
                            max_no_result_change_count,
                            gh.getGraph(),
                            cc);
      sa.simulate();
      std::cout << "Result: " << sa.result() << std::endl;
      results.push_back(sa.result());
    }
    std::cout << "Finished\n";
    std::cout << "Best result: " << findMin(results) << std::endl;
    std::cout << "Mean result: " << arrayMean(results) << std::endl;
  }
}
