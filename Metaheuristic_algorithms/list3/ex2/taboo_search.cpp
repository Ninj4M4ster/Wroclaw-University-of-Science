#include "inc/taboo_search.h"

TabooSearch::TabooSearch(std::shared_ptr<Graph> graph,
                         std::shared_ptr<CycleCreator> cycle_creator,
                         size_t taboo_list_max_length_multiplier) {
  graph_ = graph;
  cycle_creator_ = cycle_creator;
  taboo_list_max_length_ = taboo_list_max_length_multiplier * graph_->size();

  // create neighbourhood
  for (int i = 0; i < graph_->size() - 1; i++) {
    for (int j = i + 1; j < graph_->size(); j++) {
      if (i == 0 && j == graph_->size() - 1)
        continue;
      neighbourhood_.push_back({i, j});
    }
  }
}

void TabooSearch::simulate() {
  std::uniform_int_distribution<int> vertices_dist{0, static_cast<int>(graph_->size() - 1)};
  cycle_creator_->createCycle(vertices_dist(rand_gen_));
  std::vector<int> current_cycle = cycle_creator_->getCycle();
  size_t current_cost = cycle_creator_->getCycleCost();

  std::vector<int> all_time_best_cycle;
  size_t all_time_best_cost = current_cost;
  while(taboo_list_.size() < taboo_list_max_length_) {
    std::cout << taboo_list_.size() << std::endl;
    size_t best_cost = std::numeric_limits<size_t>::max();
    std::vector<int> best_cycle;
    std::string best_cycle_string;
    for(auto &pair : neighbourhood_) {
      std::vector<int> new_cycle = invertCycle(pair.first, pair.second, current_cycle);
      std::string cycle_string = stringifyCycle(new_cycle);
      size_t new_cost = calculateNewCycleCost(pair.first,
                                              pair.second,
                                              current_cost,
                                              current_cycle);
      if(new_cost < best_cost && taboo_list_.find(cycle_string) == taboo_list_.end()) {
        best_cost = new_cost;
        best_cycle = new_cycle;
        best_cycle_string = cycle_string;
      }
    }
    current_cost = best_cost;
    current_cycle = best_cycle;
    taboo_list_[best_cycle_string] = true;
    if(current_cost < all_time_best_cost) {
      all_time_best_cost = current_cost;
      all_time_best_cycle = current_cycle;
    }
  }
  result_ = all_time_best_cost;
}

size_t TabooSearch::getResult() const {
  return result_;
}

/**
 * This method calculates new cycle cost after inverting all vertices from start_vert to end_vert.
 * After inverting all vertices from start_vert to end_vert, it is needed only to subtract
 * costs of edges (start_vert - 1, start_vert) and (end_vert, end_vert + 1) from current cycle cost.
 * Rest of the costs does not change. Then add (start_vert - 1, end_vert) and (start_vert, end_vert + 1),
 * which gives cost of new cycle.
 * @param start_ind Start index of invert in given cycle
 * @param end_ind End index of invert in given cycle.
 * @param curr_cost Cost of the current cycle.
 * @param curr_cycle Current cycle.
 * @return Cost of new cycle.
 */
size_t TabooSearch::calculateNewCycleCost(int start_ind,
                                          int end_ind,
                                          size_t curr_cost,
                                          std::vector<int> curr_cycle) {
  size_t new_cost = curr_cost;
  int prev_start_ind = start_ind - 1;
  if(prev_start_ind < 0)
    prev_start_ind += graph_->size();
  int next_end_ind = end_ind + 1;
  if(next_end_ind == graph_->size())
    next_end_ind -= graph_->size();
  int start_vertex = curr_cycle.at(start_ind);
  int prev_start_vertex = curr_cycle.at(prev_start_ind);
  int end_vertex = curr_cycle.at(end_ind);
  int next_end_vertex = curr_cycle.at(next_end_ind);
  new_cost -= graph_->at(prev_start_vertex).at(start_vertex);
  new_cost -= graph_->at(end_vertex).at(next_end_vertex);
  new_cost += graph_->at(prev_start_vertex).at(end_vertex);
  new_cost += graph_->at(start_vertex).at(next_end_vertex);
  return new_cost;
}


/**
 * Invert all elements in cycle between given indexes.
 *
 * @param start_vert Start index.
 * @param end_vert End index.
 * @param curr_cycle Current cycle.
 */
std::vector<int> TabooSearch::invertCycle(int start_vert, int end_vert, std::vector<int> curr_cycle) {
  while(start_vert < end_vert) {
    std::swap(curr_cycle.at(start_vert), curr_cycle.at(end_vert));
    start_vert++;
    end_vert--;
  }
  return curr_cycle;
}

std::string TabooSearch::stringifyCycle(std::vector<int> cycle) {
  std::string result;
  for(int i = 0; i < cycle.size(); i++) {
    result += std::to_string(cycle.at(i));
    if(i != cycle.size() - 1) {
      result += ',';
    }
  }
  return result;
}

std::vector<int> TabooSearch::cycleFromString(std::string cycle_string) {
  std::string buff;
  std::stringstream ss(cycle_string);
  std::vector<int> res_cycle;
  while(std::getline(ss, buff, ',')) {
    res_cycle.push_back(std::stoi(buff));
  }
  return res_cycle;
}