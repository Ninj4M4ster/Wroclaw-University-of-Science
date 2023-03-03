#include "graph_utils.h"
#include <stack>

void topologicalSort(const ProximityList & graph) {
    // create list of indegree of vertices
    std::vector<int> verticesIndegree(graph.size(), 0);
    for(const auto & vertex : graph) {
        for(unsigned int connection : vertex) {
            verticesIndegree.at(connection)++;
        }
    }
    // place starting nodes on stack
    std::vector<unsigned int> outputList;
    std::stack<unsigned int> verticesStack;
    for(int index = 0; index < verticesIndegree.size(); index++) {
        if(verticesIndegree.at(index) == 0) {
            outputList.push_back(index);
            verticesStack.push(index);
        }
    }
    // loop over stack and update indegree list
    unsigned int next = 0;
    while(!verticesStack.empty()) {
        unsigned int current_vertex = verticesStack.top();
        verticesStack.pop();
        next++;
        for(unsigned int connection : graph.at(current_vertex)) {
            verticesIndegree.at(connection)--;
            if(verticesIndegree.at(connection) == 0) {
                outputList.push_back(connection);
                verticesStack.push(connection);
            }
        }
    }
    if(next < graph.size()) {
        std::cout << "Graph contains a directed cycle" << std::endl;
        return;
    }
    if(graph.size() <= 200) {
        std::cout << "Ordering\n";
        for(unsigned int vertex : outputList) {
            std::cout << vertex + 1 << std::endl;
        }
    }
}

int main() {
    ProximityList graph = readGraphToProximityList();
    topologicalSort(graph);
}
