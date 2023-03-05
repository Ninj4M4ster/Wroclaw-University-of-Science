#include "graph_utils.h"
#include <queue>


/**
 * This function performs breadth-first search with coloring on given graph.
 * If during search two vertices with same color have a connection, then the graph is not bipartite and the return
 * vectors are empty.
 * Otherwise vectors contain parted graph.
 *
 * @param graph Proximity list of a graph.
 * @return Pair of vectors containing parted graph if it is bipartite or empty vectors otherwise.
 */
std::pair<std::vector<unsigned int>, std::vector<unsigned int>> isBipartite(const ProximityList & graph) {
    std::vector<unsigned int> firstGroupVertices;
    std::vector<unsigned int> secondGroupVertices;
    std::queue<std::pair<unsigned int, int>> verticesQueue;  // queue containing pairs of vertex index and color
    std::vector<unsigned int> exploredVerticesWithColor(graph.size(), 0);

    int next_color = 1;
    exploredVerticesWithColor.at(0) = next_color;
    verticesQueue.emplace(0, next_color);
    // perform bfs
    while(!verticesQueue.empty()) {
        std::pair<unsigned int, int> currentVertexWithColor = verticesQueue.front();
        verticesQueue.pop();
        next_color = currentVertexWithColor.second == 1 ? 2 : 1;
        for(unsigned int connection : graph.at(currentVertexWithColor.first)) {
            if(exploredVerticesWithColor.at(connection) == 0) {
                exploredVerticesWithColor.at(connection) = next_color;
                verticesQueue.emplace(connection, next_color);
            } else {
                if(exploredVerticesWithColor.at(connection) == currentVertexWithColor.second)
                    return std::pair<std::vector<unsigned int>, std::vector<unsigned int>>
                            {firstGroupVertices, secondGroupVertices};
            }
        }
    }

    // place vertices in first or second group based on color
    for(unsigned int index = 0; index < exploredVerticesWithColor.size(); index++) {
        if(exploredVerticesWithColor.at(index) == 1)
            firstGroupVertices.push_back(index);
        else
            secondGroupVertices.push_back(index);
    }

    return std::pair<std::vector<unsigned int>, std::vector<unsigned int>>
            {firstGroupVertices, secondGroupVertices};
}

int main() {
    ProximityList graph = readGraphToProximityList();
    std::pair<std::vector<unsigned int>, std::vector<unsigned int>> returnPair = isBipartite(graph);
    if(returnPair.first.empty() && returnPair.second.empty()) {
        std::cout << "Given graph is not bipartite" << std::endl;
        return 0;
    }
    std::cout << "Given graph is bipartite" << std::endl;
    if(graph.size() <= 200) {
        std::cout << std::endl << "First set" << std::endl;
        for(unsigned int vertex : returnPair.first) {
            std::cout << vertex + 1 << std::endl;
        }
        std::cout << std::endl << "Second set" << std::endl;
        for(unsigned int vertex : returnPair.second) {
            std::cout << vertex + 1 << std::endl;
        }
    }
}