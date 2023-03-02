#include "graph_utils.h"
#include <queue>
#include <stack>
#include <memory>

/**
 * This function performs a breadth-first search on given proximity list of a graph.
 * If return_search_tree flag is given, it will return a proximity list representing search tree of the algorithm.
 * This function also prints vertices indexes in order they were searched.
 *
 * @param graph Proximity list of a graph.
 * @param return_search_tree If true, function returns search tree, nullptr otherwise.
 * @return Shared pointer to search tree or nullptr.
 */
std::shared_ptr<ProximityList> breadthFirstSearch(const ProximityList & graph, bool return_search_tree) {
    std::shared_ptr<ProximityList> searchGraph = std::make_shared<ProximityList>(graph.size());
    std::queue<unsigned int> verticesQueue;
    std::vector<unsigned int> exploredVertices(graph.size(), 0);
    // if vertex v is explored, then exploredVertices.at(v) = 1
    exploredVertices.at(0) = 1;  // start at vertex v=1
    verticesQueue.push(0);
    std::cout << 1 << std::endl;
    while(!verticesQueue.empty()) {
        unsigned int vertex = verticesQueue.front();
        verticesQueue.pop();
        for(unsigned int connectedVertex : graph.at(vertex)) {
            if(exploredVertices.at(connectedVertex) == 0) {
                std::cout << connectedVertex + 1 << std::endl;
                exploredVertices.at(connectedVertex) = 1;
                verticesQueue.push(connectedVertex);
                searchGraph->at(vertex).push_back(connectedVertex);
            }
        }
    }
    if(return_search_tree)
        return searchGraph;
    return nullptr;
}

/**
 * This function performs a depth-first search on given proximity list of a graph. If return_search_tree flag is given,
 * it will return a proximity list representing search tree of the algorithm.
 * This function also prints vertices indexes in order they were searched.
 *
 * @param graph Proximity list of a graph.
 * @param return_search_tree If true, function returns search tree, nullptr otherwise.
 * @return Shared pointer to search tree or nullptr.
 */
std::shared_ptr<ProximityList> depthFirstSearch(const ProximityList & graph, bool return_search_tree) {
    std::shared_ptr<ProximityList> searchGraph = std::make_shared<ProximityList>(graph.size());
    std::stack<unsigned int> verticesStack;
    std::vector<unsigned int> exploredVertices(graph.size(), 0);
    // if vertex v is explored, then exploredVertices.at(v) = 1
    verticesStack.push(0);
    unsigned int previousVertex = 0;
    while(!verticesStack.empty()) {
        unsigned int vertex = verticesStack.top();
        if(vertex != previousVertex)
            searchGraph->at(previousVertex).push_back(vertex);
        verticesStack.pop();
        if(exploredVertices.at(vertex) == 0) {
            exploredVertices.at(vertex) = 1;
            std::cout << vertex + 1 << std::endl;
            for(unsigned int connectedVertex : graph.at(vertex)) {
                verticesStack.push(connectedVertex);
            }
        }
        previousVertex = vertex;
    }
    if(return_search_tree)
        return searchGraph;
    return nullptr;
}

int main(int argc, char* argv[]) {
    bool return_search_tree_flag = false;
    if(argc > 1 && argv[1][0] == '-' && std::string(argv[1]).length() == 2) {
        if(argv[1][1] == 'r')
            return_search_tree_flag = true;
    } else if(argc > 1) {
        std::cout << "Type -r argument to return the search tree after function execution";
        return 0;
    }
    ProximityList graph = readGraphToProximityList();
    std::cout << "Depth-first search\n";
    depthFirstSearch(graph, return_search_tree_flag);
    std::cout << "\nBreadth-first search\n";
    breadthFirstSearch(graph, return_search_tree_flag);
    return 0;
}
