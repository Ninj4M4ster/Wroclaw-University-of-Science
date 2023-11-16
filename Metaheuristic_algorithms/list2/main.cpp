#include <filesystem>
#include <random>
#include "graph_handler.cpp"
#include "cycle_creator.cpp"
#include "local_search_solver.cpp"

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

double calculateMean(std::vector<size_t>& array) {
  double result = 0.0;
  for(auto val : array) {
    result += static_cast<double>(val);
  }
  return result / static_cast<double>(array.size());
}

int main() {
  // random generator used later
  std::mt19937_64 rand_gen_{std::random_device{}()};

  std::string data_dir_path = "data/";
  for(const auto & entry : std::filesystem::directory_iterator(data_dir_path)) {
    std::string file_name = entry.path().string();
    std::string graph_name = strip(file_name);
    std::cout << graph_name << std::endl;

    // create mst and calculate it's cost using GraphHandler
    GraphHandler graph_handler(file_name);

    std::shared_ptr<Graph> mst = graph_handler.getMst();
    std::shared_ptr<Graph> graph = graph_handler.getGraph();

    // prepare distribution and cycle creator
    std::uniform_int_distribution<int> dist{0, static_cast<int>(graph_handler.getGraph()->size())};
    CycleCreator cycle_creator(mst, graph);

    std::vector<size_t> cycle_costs_;
    std::vector<size_t> steps_array_;
    // create cycle starting from random vertex and apply local search using LocalSearchSolver
    for(int i = 0; i < std::sqrt(static_cast<double>(graph->size())); i++) {
      int rand_vertex = dist(rand_gen_);
      cycle_creator.createCycle(rand_vertex);

      LocalSearchSolver local_search_solver(graph,
                                            cycle_creator.getCycle(),
                                            cycle_creator.getCycleCost());
      cycle_costs_.push_back(local_search_solver.getCycleCost());
      steps_array_.push_back(local_search_solver.getStepsCounter());
    }

    // print results
    std::cout << "Mst cost: " << graph_handler.getMstCost() << std::endl;
    std::cout << "Mean result cost: " << calculateMean(cycle_costs_) << std::endl;
    std::cout << "Mean steps: " << calculateMean(steps_array_) << std::endl;
    // pass results to file
  }
}