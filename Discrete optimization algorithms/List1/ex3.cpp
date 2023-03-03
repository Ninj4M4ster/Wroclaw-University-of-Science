#include "graph_utils.h"
#include <stack>
#include <queue>

/**
 * This function performs a breadth-first search on given proximity list of a graph.
 *
 * @param graph Proximity list of a graph.
 * @param startingVertex Vertex from which algorithm finds paths.
 * @return Vector of explored vertices (value at index i equals 1 if vertex was explored, 0 otherwise).
 */
std::vector<unsigned int> breadthFirstSearch(const ProximityList & graph, unsigned int startingVertex) {
    std::queue<unsigned int> verticesQueue;
    std::vector<unsigned int> exploredVertices(graph.size(), 0);
    // if vertex v is explored, then exploredVertices.at(v) = 1
    exploredVertices.at(startingVertex) = 1;  // start at vertex v=1
    verticesQueue.push(startingVertex);
    while(!verticesQueue.empty()) {
        unsigned int vertex = verticesQueue.front();
        verticesQueue.pop();
        for(unsigned int connectedVertex : graph.at(vertex)) {
            if(exploredVertices.at(connectedVertex) == 0) {
                exploredVertices.at(connectedVertex) = 1;
                verticesQueue.push(connectedVertex);
            }
        }
    }
    return exploredVertices;
}

/**
 * This function inverts proximity list - for each index i, list.at(i) returns a vector of vertices
 * that have edges ending at vertex i.
 *
 * @param graph Proximity list of graph to be inverted.
 * @return Inverted proximity list.
 */
ProximityList invertProximityList(const ProximityList & graph) {
    ProximityList invertedProximityList(graph.size());
    for(unsigned int vertex = 0; vertex < graph.size(); vertex++) {
        for(unsigned int connection : graph.at(vertex)) {
            invertedProximityList.at(connection).push_back(vertex);
        }
    }
    return invertedProximityList;
}

/**
 * This function performs a reverse search on given proximity list of a graph.
 * It works the same way as breadth-first search or depth-first search, but it uses
 * reverted proximity list to find next vertices to explore.
 *
 * @param graph Proximity list of a graph.
 * @param startingVertex Vertex to which algorithm finds paths.
 * @return Vector of explored vertices (value at index i equals 1 if vertex was explored, 0 otherwise).
 */
std::vector<unsigned int> reverseSearch(const ProximityList & graph, unsigned int startingVertex) {
    std::queue<unsigned int>verticesQueue;
    std::vector<unsigned int> exploredVertices(graph.size(), 0);
    ProximityList invertedProximityList = invertProximityList(graph);  // get inverted proximity list of a graph
    exploredVertices.at(startingVertex) = 1;
    verticesQueue.push(startingVertex);
    while(!verticesQueue.empty()) {
        unsigned int vertex = verticesQueue.front();
        verticesQueue.pop();
        for(unsigned int connectedVertex : invertedProximityList.at(vertex)) {
            if(exploredVertices.at(connectedVertex) == 0) {
                exploredVertices.at(connectedVertex) = 1;
                verticesQueue.push(connectedVertex);
            }
        }
    }
    return exploredVertices;
}

/**
 * This function returns a sub-graph containing strongly connected vertices.
 *
 * @param exploredVertices Vertices explored during searches.
 * @param graph Proximity list of the original graph.
 * @return Sub-graph containing strongly connected component.
 */
std::vector<unsigned int> getSubGraph(std::vector<unsigned int> & bfsExploredVertices,
                          std::vector<unsigned int> & rsExploredVertices,
                          std::vector<unsigned int> & allRsExploredVertices) {
    std::vector<unsigned int> subGraph;
    for(unsigned int index = 0; index < bfsExploredVertices.size(); index++) {
        if(bfsExploredVertices.at(index) == 1 && rsExploredVertices.at(index) == 1 && allRsExploredVertices.at(index) == 0) {
            subGraph.push_back(index);
        }
    }
    return subGraph;
}

/**
 * This function decomposes given graph to strongly connected components.
 * It performs depth-first search and then does a reverse search until
 * all vertices were visited during reverse searches.
 *
 * @param graph Graph to decomposes.
 * @return Vector containing vectors with vertices belonging to a single component.
 */
std::vector<std::vector<unsigned int>> decomposeStronglyConnectedComponents(const ProximityList & graph) {
    // vector for decomposed sub-graphs
    std::vector<std::vector<unsigned int>> decomposedStronglyConnectedComponents;
    std::vector<unsigned int> bfsExploredVertices = breadthFirstSearch(graph, 0);  // starting at vertex 0
    std::vector<unsigned int> rsExploredVertices(graph.size(), 0);
    for(unsigned int index = 0; index < bfsExploredVertices.size(); index++) {
        if(bfsExploredVertices.at(index) == 1) {
            if(rsExploredVertices.at(index) == 1)  // vertex is a part of already found sub-graph
                continue;
            std::vector<unsigned int> currentlyRsExploredVertices = reverseSearch(graph, index);
            // add sub-graph found during reverse search
            decomposedStronglyConnectedComponents.push_back(
                    getSubGraph(bfsExploredVertices, currentlyRsExploredVertices, rsExploredVertices));
            // add vertices explored during reverse search to vertices explored after all previous reverse searches
            for(unsigned int rsExploredIndex = 0;
                    rsExploredIndex < currentlyRsExploredVertices.size();
                    rsExploredIndex++) {
                if(currentlyRsExploredVertices.at(rsExploredIndex) == 1)
                    rsExploredVertices.at(rsExploredIndex) = 1;
            }
        }
    }
    return decomposedStronglyConnectedComponents;
}

int main() {
    ProximityList graph = readGraphToProximityList();
    std::vector<std::vector<unsigned int>> decomposedStronglyConnectedComponents = decomposeStronglyConnectedComponents(graph);
    std::cout << "Number of strongly connected components: "
    << decomposedStronglyConnectedComponents.size() << std::endl << std::endl;
    for(const auto & component : decomposedStronglyConnectedComponents) {
        std::cout << "Number of vertices: " <<  component.size() << std::endl;
        if(component.size() <= 200) {
            std::cout << "List of vertices in component: " << std::endl;
            for(unsigned int index : component) {
                std::cout << index + 1 << std::endl;
            }
            std::cout << std::endl;
        }
    }
    return 0;
}
