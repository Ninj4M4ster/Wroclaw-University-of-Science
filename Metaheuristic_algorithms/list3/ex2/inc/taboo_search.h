#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST3_EX2_TABOO_SEARCH_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST3_EX2_TABOO_SEARCH_H_

#include "cycle_creator.h"

class TabooSearch {
 public:
  explicit TabooSearch(std::shared_ptr<Graph> graph,
  std::shared_ptr<CycleCreator> cycle_creator);

 private:
  std::shared_ptr<Graph> graph_;
  std::shared_ptr<CycleCreator> cycle_creator_;

  std::unordered_map<std::string, int> taboo_list_;

  size_t calculateNewCycleCost(int start_ind, int end_ind);
  void invertCycle(int start_vert, int end_vert);
  std::string stringifyCycle(std::vector<int> cycle);
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_METAHEURISTIC_ALGORITHMS_LIST3_EX2_TABOO_SEARCH_H_
