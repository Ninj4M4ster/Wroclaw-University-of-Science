#include <filesystem>
#include <thread>
#include "graph_handler.cpp"
#include "cycle_creator.cpp"
#include "local_search_solver.cpp"
#include "modified_local_search_solver.cpp"

/**
 * Strip "data/" and ".tsp" from graph file name.
 *
 * @param graph_file_path Path of graph file.
 * @return Name of the graph.
 */
std::string strip(std::string graph_file_path) {
  std::string graph_name;
  for(int i = 5; i < graph_file_path.length() - 4; i++) {
    graph_name += graph_file_path[i];
  }
  return graph_name;
}

/**
 * Calculate mean of given array of values.
 *
 * @param array Array of values.
 * @return Mean of given array.
 */
double calculateMean(std::vector<size_t>& array) {
  double result = 0.0;
  for(auto val : array) {
    result += static_cast<double>(val);
  }
  return result / static_cast<double>(array.size());
}

/**
 * Find min value in given array.
 *
 * @param array Array of values.
 * @return Min value in array.
 */
size_t findMin(std::vector<size_t>& array) {
  size_t min_val = std::numeric_limits<size_t>::max();
  for(auto val : array) {
    if(val < min_val)
      min_val = val;
  }
  return min_val;
}

/**
 * Run all experiments for given graph name, file name and using given random generator.
 */
void runExperiments(std::string graph_name, std::mt19937_64& rand_gen, std::string file_name) {
  std::fstream out_f;
  std::cout << graph_name << std::endl;

  // create mst and calculate it's cost using GraphHandler
  GraphHandler graph_handler(file_name);

  std::shared_ptr<Graph> mst = graph_handler.getMst();
  std::shared_ptr<Graph> graph = graph_handler.getGraph();
  int max_iter = graph->size() > 1000 ? 100 : graph->size();

  // prepare distribution and cycle creator
  std::uniform_int_distribution<int> dist{0, static_cast<int>(graph_handler.getGraph()->size()) - 1};
  CycleCreator cycle_creator(mst, graph);

  // pipeline for local search, exercise 1
  std::vector<size_t> cycle_costs_;
  std::vector<size_t> steps_array_;
  size_t best_cost = std::numeric_limits<size_t>::max();
  std::vector<int> best_cycle;
  std::cout << "Ex1" << std::endl;
  int max_iter_sqrt = graph->size() > 1000 ? 100 : static_cast<int>(std::sqrt(static_cast<double>(graph->size())));
  // create cycle starting from random vertex and apply local search using LocalSearchSolver
  for (int i = 0; i < max_iter_sqrt; i++) {
    std::cout << i << "/" << max_iter_sqrt << std::endl;
    int rand_vertex = dist(rand_gen);
    cycle_creator.createCycle(rand_vertex);

    LocalSearchSolver local_search_solver(graph,
                                          cycle_creator.getCycle(),
                                          cycle_creator.getCycleCost());
    local_search_solver.localSearch();
    auto cost = local_search_solver.getCycleCost();
    cycle_costs_.push_back(cost);
    steps_array_.push_back(local_search_solver.getStepsCounter());
    if (cost < best_cost) {
      best_cost = cost;
      best_cycle = local_search_solver.getCycle();
    }
  }
  // print results
  std::cout << "Results for mst cycle" << std::endl;
  std::cout << "Mst cost: " << graph_handler.getMstCost() << std::endl;
  std::cout << "Mean result cost: " << calculateMean(cycle_costs_) << std::endl;
  std::cout << "Mean steps: " << calculateMean(steps_array_) << std::endl;
  std::cout << "Best result cost: " << findMin(cycle_costs_) << std::endl;
  // pass results to file
  // filename: graph_name
  // results to pass: mst cost, mean result cost, mean steps, best result cost, best cycle
  out_f.open(graph_name + "_ex1.txt", std::ios::out);
  out_f << graph_handler.getMstCost() << ";"
        << calculateMean(cycle_costs_) << ";"
        << calculateMean(steps_array_) << ";"
        << findMin(cycle_costs_) << "\n";
  for (auto val : best_cycle) {
    out_f << val << ", ";
  }
  out_f.close();

  // pipeline for local search for random cycles, exercise 2
  cycle_costs_.clear();
  steps_array_.clear();
  best_cost = std::numeric_limits<size_t>::max();
  best_cycle.clear();
  std::cout << "ex2" << std::endl;
  for (int i = 0; i < max_iter; i++) {
    std::cout << i << "/" << max_iter << std::endl;
    std::vector<int> random_cycle = CycleCreator::createRandomCycle(graph->size(), rand_gen);
    auto cycle_cost = CycleCreator::calculateCycleCost(random_cycle, graph);

    LocalSearchSolver local_search_solver(graph,
                                          random_cycle,
                                          cycle_cost);
    local_search_solver.localSearch();
    auto result_cost = local_search_solver.getCycleCost();
    cycle_costs_.push_back(result_cost);
    steps_array_.push_back(local_search_solver.getStepsCounter());
    if (result_cost < best_cost) {
      best_cost = result_cost;
      best_cycle = local_search_solver.getCycle();
    }
  }
  // print results
  std::cout << "Results for random cycles" << std::endl;
  std::cout << "Mst cost: " << graph_handler.getMstCost() << std::endl;
  std::cout << "Mean result cost: " << calculateMean(cycle_costs_) << std::endl;
  std::cout << "Mean steps: " << calculateMean(steps_array_) << std::endl;
  std::cout << "Best result cost: " << findMin(cycle_costs_) << std::endl;
  // pass results to file
  // filename: graph_name
  // results to pass: mst cost, mean result cost, mean steps, best result cost, best cycle
  out_f.open(graph_name + "_ex2.txt", std::ios::out);
  out_f << graph_handler.getMstCost() << ";"
        << calculateMean(cycle_costs_) << ";"
        << calculateMean(steps_array_) << ";"
        << findMin(cycle_costs_) << "\n";
  for (auto val : best_cycle) {
    out_f << val << ", ";
  }
  out_f.close();

  // pipeline for modified local search for random cycles, exercise 3
  cycle_costs_.clear();
  steps_array_.clear();
  best_cost = std::numeric_limits<size_t>::max();
  best_cycle.clear();
  std::cout << "Ex3" << std::endl;
  for (int i = 0; i < max_iter; i++) {
    std::cout << i << "/" << max_iter << std::endl;
    std::vector<int> random_cycle = CycleCreator::createRandomCycle(graph->size(), rand_gen);
    auto cycle_cost = CycleCreator::calculateCycleCost(random_cycle, graph);

    ModifiedLocalSearchSolver modified_local_search_solver(graph,
                                                           random_cycle,
                                                           cycle_cost,
                                                           rand_gen);
    modified_local_search_solver.localSearch();
    auto result_cost = modified_local_search_solver.getCycleCost();
    cycle_costs_.push_back(result_cost);
    steps_array_.push_back(modified_local_search_solver.getStepsCounter());
    if (result_cost < best_cost) {
      best_cost = result_cost;
      best_cycle = modified_local_search_solver.getCycle();
    }
  }
  // print results
  std::cout << "Results for modified local search for random cycles" << std::endl;
  std::cout << "Mst cost: " << graph_handler.getMstCost() << std::endl;
  std::cout << "Mean result cost: " << calculateMean(cycle_costs_) << std::endl;
  std::cout << "Mean steps: " << calculateMean(steps_array_) << std::endl;
  std::cout << "Best result cost: " << findMin(cycle_costs_) << std::endl;
  // pass results to file
  // filename: graph_name
  // results to pass: mst cost, mean result cost, mean steps, best result cost, best cycle
  out_f.open(graph_name + "_ex3.txt", std::ios::out);
  out_f << graph_handler.getMstCost() << ";"
        << calculateMean(cycle_costs_) << ";"
        << calculateMean(steps_array_) << ";"
        << findMin(cycle_costs_) << "\n";
  for (auto val : best_cycle) {
    out_f << val << ", ";
  }
  out_f.close();
}

int main() {
  // random generator used later
  std::mt19937_64 rand_gen{std::random_device{}()};

  std::string data_dir_path = "data/";
  std::vector<std::thread> threads;
  for(const auto & entry : std::filesystem::directory_iterator(data_dir_path)) {
    std::string file_name = entry.path().string();
    std::string graph_name = strip(file_name);
    threads.emplace_back([graph_name, file_name, &rand_gen]() {
      runExperiments(graph_name, rand_gen, file_name);
    });
  }
  for(auto & t : threads) {
    t.join();
  }
}
