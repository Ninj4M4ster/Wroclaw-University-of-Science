#include <iostream>
#include "graph_handler.cpp"
#include "cycle_creator.cpp"
#include "simulated_annealing.cpp"

static constexpr int temperature = 10000;
static constexpr double temperature_scale = 0.8;
static constexpr int epoch_size = 100000;
static constexpr int max_epoch_count = 10000;
static constexpr size_t max_no_result_change_count = 50000;

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
    std::cout << graph_names.at(i) << std::endl;
    GraphHandler gh(graph_names.at(i));
    std::cout << "Graph read\n";
    std::shared_ptr<CycleCreator> cc =
        std::make_shared<CycleCreator>(gh.getMst(), gh.getGraph());

    SimulatedAnnealing sa(temperature,
                          temperature_scale,
                          epoch_size,
                          max_epoch_count,
                          max_no_result_change_count,
                          gh.getGraph(),
                          cc);
    std::cout << "Starting sim\n";
    sa.simulate();
    std::cout << "Mst cost: " << gh.getMstCost() << std::endl;
    std::cout << "Result: " << sa.result() << std::endl;
  }
}