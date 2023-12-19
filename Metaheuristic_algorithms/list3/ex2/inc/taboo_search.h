#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST3_EX2_TABOO_SEARCH_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST3_EX2_TABOO_SEARCH_H_

#include "cycle_creator.h"

class TabooSearch {
 public:
  explicit TabooSearch(std::shared_ptr<Graph> graph,
                       std::shared_ptr<CycleCreator> cycle_creator,
                       size_t taboo_list_max_length_multiplier);
  void simulate();
  size_t getResult() const;
 private:
  std::shared_ptr<Graph> graph_;
  std::shared_ptr<CycleCreator> cycle_creator_;
  std::vector<std::pair<int, int>> neighbourhood_;

  std::unordered_map<size_t, int> taboo_list_;
  size_t taboo_list_max_length_;

  size_t result_;

  std::mt19937_64 rand_gen_{std::random_device{}()};

  size_t calculateNewCycleCost(int start_ind, int end_ind, size_t curr_cost, std::vector<int> curr_cycle);
  std::vector<int> invertCycle(int start_vert, int end_vert, std::vector<int> curr_cycle);
  std::string stringifyCycle(std::vector<int> cycle);
  std::vector<int> cycleFromString(std::string cycle_string);
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST3_EX2_TABOO_SEARCH_H_
