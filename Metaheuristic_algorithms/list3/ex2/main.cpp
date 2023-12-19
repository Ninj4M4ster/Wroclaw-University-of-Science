#include <iostream>
#include <future>
#include <thread>
#include "graph_handler.cpp"
#include "cycle_creator.cpp"
#include "taboo_search.cpp"

static constexpr size_t taboo_list_max_length_multiplier = 15;
static constexpr double max_no_better_result_count_multiplier = 0.2;

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
    std::vector<std::future<size_t>> processes;
    std::vector<size_t> results;
    int j = 0;
    while(j < 100) {
      GraphHandler gh(big_graph_names.at(i));
      while(j < 100 && processes.size() < std::thread::hardware_concurrency()) {
        processes.push_back(std::async(std::launch::async, [gh]{
          std::shared_ptr<CycleCreator> cc =
              std::make_shared<CycleCreator>(gh.getMst(), gh.getGraph());
          TabooSearch ts(gh.getGraph(),
                         cc,
                         taboo_list_max_length_multiplier,
                         max_no_better_result_count_multiplier);
          ts.simulate();
          return ts.getResult();
        }));
        j++;
      }
      for(auto & p : processes) {
        p.wait();
        size_t res = p.get();
        std::cout << "Result: " << res << std::endl;
        results.push_back(res);
      }
      processes.clear();
    }
    std::cout << "Finished\n";
    std::cout << "Best result: " << findMin(results) << std::endl;
    std::cout << "Mean result: " << arrayMean(results) << std::endl;
  }
}
