#include "inc/simulated_annealing.h"

SimulatedAnnealing::SimulatedAnnealing(int temperature,
                                       double temperature_scale,
                                       int epoch_size,
                                       int max_epoch_count,
                                       size_t max_no_result_change_count,
                                       std::shared_ptr<Graph> graph,
                                       std::shared_ptr<CycleCreator> cycle_creator) {
  temperature_ = temperature;
  temperature_scale_ = temperature_scale;
  epoch_size_ = epoch_size;
  max_epoch_count_ = max_epoch_count;
  max_no_result_change_count_ = max_no_result_change_count;
  graph_ = graph;
  cycle_creator_ = cycle_creator;

  // create neighbourhood
  for (int i = 0; i < graph_->size() - 1; i++) {
    for (int j = i + 1; j < graph_->size(); j++) {
      if (i == 0 && j == graph_->size() - 1)
        continue;
      neighbourhood_.push_back({i, j});
    }
  }
}

void SimulatedAnnealing::simulate() {
  std::uniform_int_distribution<int> vertices_dist{0, static_cast<int>(graph_->size() - 1)};
  std::uniform_real_distribution<double> worse_result_dist{0.0, 1.0};
  std::uniform_int_distribution<int> neighbourhood_dist{0, static_cast<int>(neighbourhood_.size() - 1)};
  size_t prev_result = std::numeric_limits<size_t>::max();
  size_t no_result_change_counter = 0;

  cycle_creator_->createCycle(vertices_dist(rand_gen_));
  std::vector<int> curr_cycle = cycle_creator_->getCycle();
  size_t curr_result = cycle_creator_->getCycleCost();
  std::cout << "start result: " << curr_result << std::endl;
  for(int i = 0; i < max_epoch_count_; i++) {
    for(int j = 0; j < epoch_size_; j++) {
      std::pair<int, int> random_neighbour = neighbourhood_.at(neighbourhood_dist(rand_gen_));
      size_t new_cost = calculateNewCycleCost(random_neighbour.first,
                                              random_neighbour.second,
                                              curr_result,
                                              curr_cycle);
      if(new_cost < curr_result) {
        curr_result = new_cost;
        invertCycle(random_neighbour.first, random_neighbour.second, curr_cycle);
      } else {
        double prob = boltzmannDist(curr_result, new_cost);
        double change = worse_result_dist(rand_gen_);
        if(change < prob) {
          curr_result = new_cost;
          invertCycle(random_neighbour.first, random_neighbour.second, curr_cycle);
        }
      }
    }
    if(curr_result < prev_result) {
      no_result_change_counter = 0;
    } else {
      no_result_change_counter++;
      if(no_result_change_counter > max_no_result_change_count_) {
        break;
      }
    }
    temperature_ *= temperature_scale_;
    prev_result = curr_result;
    if(temperature_ == 0) {
      break;
    }
  }
  best_cycle_ = curr_cycle;
  best_result_ = curr_result;
}

size_t SimulatedAnnealing::result() const {
  return best_result_;
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
size_t SimulatedAnnealing::calculateNewCycleCost(int start_ind,
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
void SimulatedAnnealing::invertCycle(int start_vert, int end_vert, std::vector<int>& curr_cycle) {
  while(start_vert < end_vert) {
    std::swap(curr_cycle.at(start_vert), curr_cycle.at(end_vert));
    start_vert++;
    end_vert--;
  }
}
