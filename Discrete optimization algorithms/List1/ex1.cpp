#include "graph_utils.h"

int main() {
    std::vector<std::vector<int>> graph = readGraphToProximityMatrix();
    for(auto & i : graph) {
        for(int j : i) {
            std::cout << j << " ";
        }
        std::cout << "\n";
    }
}