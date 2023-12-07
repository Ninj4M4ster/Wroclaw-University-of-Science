#include <iostream>
#include "graph_handler.cpp"
#include "cycle_creator.cpp"
#include "simulated_annealing.cpp"

static constexpr int temperature = 120;
static constexpr double temperature_scale = 0.9;
static constexpr int epoch_size = 1000;
static constexpr int max_epoch_count = 20;

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
    GraphHandler gh(graph_names.at(i));
    std::shared_ptr<CycleCreator> cc =
        std::make_shared<CycleCreator>(gh.getMst(), gh.getGraph());

    SimulatedAnnealing sa(temperature,
                          temperature_scale,
                          epoch_size,
                          max_epoch_count,
                          gh.getGraph(),
                          cc);
  }
}