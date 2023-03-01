#include <iostream>
#include <vector>

/**
 * Function for reading graph direction argument from standard input.
 *
 * @return Is the graph directed?
 */
bool readGraphDirection() {
    std::string direction_char;
    std::getline(std::cin, direction_char);
    if(direction_char.length() == 1) {
        if(direction_char[0] == 'D')
            return true;
        else if(direction_char[0] == 'U')
            return false;
    }
    throw std::runtime_error("Bad direction argument");
}

/**
 * Function for reading a single unsigned decimal number from standard input.
 *
 * @return Unsigned decimal number.
 */
unsigned int readSingleNumber() {
    std::string input_string;
    std::getline(std::cin, input_string);
    if(input_string.length() > 0) {
        return std::stoul(input_string);
    }
    throw std::runtime_error("No argument given as single number");
}

/**
 * Function for reading a pair of unsigned decimal numbers.
 *
 * @return Pair of unsigned decimal numbers.
 */
std::pair<unsigned int, unsigned int> readEdge() {
    std::string input_string;
    std::getline(std::cin, input_string);
    unsigned int first_number = 0;
    unsigned int second_number = 0;
    if(input_string.length() > 0) {
        int index = 0;
        do {
            first_number *= 10;
            first_number += input_string[index] - '0';
            index++;
            if(index > input_string.length())
                throw std::runtime_error("One number given for edge");
        } while(input_string[index] != ' ');
        index++;
        do {
            second_number *= 10;
            second_number += input_string[index] - '0';
            index++;
        } while(index < input_string.length());
        return std::pair<unsigned int, unsigned int>{first_number, second_number};
    }
    throw std::runtime_error("No arguments given for edge");
}

typedef std::vector<std::vector<int>> ProximityMatrix;

/**
 * This function reads information about graph from standard input and returns a matrix of proximity
 * of this graph.
 * If we take a pair (i, j) of indexes, then matrix.at(i).at(j) would return 1 if there is a connection
 * from vertex i to vertex j or 0 otherwise.
 *
 * matrix.size() and matrix.at(i).size() for every i returns number of vertices in graph.
 *
 * @return Matrix of proximity of a graph.
 */
ProximityMatrix readGraphToProximityMatrix() {
    bool isDirected = readGraphDirection();
    unsigned int n = readSingleNumber();
    unsigned int m = readSingleNumber();
    ProximityMatrix matrix(n, std::vector<int>(n, 0));
    for(unsigned int i = 0; i < m; i++) {
        std::pair<unsigned int, unsigned int> edge = readEdge();
        if(isDirected) {
            matrix.at(edge.first - 1).at(edge.second - 1) = 1;
        } else {
            matrix.at(edge.first - 1).at(edge.second - 1) = 1;
            matrix.at(edge.second - 1).at(edge.first - 1) = 1;
        }
    }
    return matrix;
}

typedef std::vector<std::vector<int>> IncidenceMatrix;

/**
 * This function reads information about graph from standard input and returns a matrix of incidence
 * of this graph.
 * For given indexes (i, j), matrix.at(i).at(j) returns 1 if vertex i is a start of edge j,
 * -1 if vertex is an end of edge j or 0 if there is no connection between vertex i and edge j.
 *
 * matrix.size() returns number of vertices and matrix.at(i).size() returns number of edges (it is same for every i).
 *
 * @return Matrix of incidence of a graph.
 */
IncidenceMatrix readGraphToIncidenceMatrix() {
    bool isDirected = readGraphDirection();
    unsigned int n = readSingleNumber();
    unsigned int m = readSingleNumber();
    IncidenceMatrix matrix(n, std::vector<int>(m, 0));
    for(unsigned int i = 0; i < m; i++) {
        std::pair<unsigned int, unsigned int> edge = readEdge();
        if(isDirected) {
            matrix.at(edge.first - 1).at(i) = 1;
            matrix.at(edge.second - 1).at(i) = -1;
        } else {
            matrix.at(edge.first - 1).at(i) = 1;
            matrix.at(edge.second - 1).at(i) = 1;
        }
    }
    return matrix;
}

typedef std::vector<std::vector<unsigned int>> ProximityList;
/**
 * This function reads information about graph from standard input and returns a list of proximity
 * of this graph.
 * For given index i, matrix.at(i) returns a list of vertices that vertex i is connected to.
 *
 * @return List of proximity of a graph.
 */
ProximityList readGraphToProximityList() {
    bool isDirected = readGraphDirection();
    unsigned int n = readSingleNumber();
    unsigned int m = readSingleNumber();
    ProximityList matrix(n);
    for(unsigned int i = 0; i < m; i++) {
        std::pair<unsigned int, unsigned int> edge = readEdge();
        if(isDirected) {
            matrix.at(edge.first - 1).push_back(edge.second - 1);
        } else {
            matrix.at(edge.first - 1).push_back(edge.second - 1);
            matrix.at(edge.second - 1).push_back(edge.first - 1);
        }
    }
    return matrix;
}