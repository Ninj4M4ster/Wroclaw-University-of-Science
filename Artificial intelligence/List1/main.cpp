#include <iostream>
#include <vector>

bool convertInputPermutation(std::vector<std::vector<int>> & input_permutation, std::string & input) {
    std::vector<int> filled_indexes(15, 0);
    int current_row = 0;
    int current_column = 0;
    int inputted_characters = 0;
    int current_number = 0;
    for(char i : input) {
        if(i == ' ') {
            if(current_number < 1 || current_number > 15) {
                std::cout << "Wprowadzono nieprawidlowe dane\n";
                return false;
            }
            inputted_characters++;
            input_permutation.at(current_row).at(current_column) = current_number;
            current_column = (current_column + 1) % 4;
            if(current_column == 0)
                current_row++;
            filled_indexes.at(current_number - 1) = 1;
            current_number = 0;
            continue;
        }
        if(current_number != 0) {
            if(i < '0' || i > '9') {
                std::cout << "Wprowadzono nieprawidlowe dane\n";
                return false;
            }
            current_number *= 10;
        } else if(i < '1' || i > '9') {
            std::cout << "Wprowadzono nieprawidlowe dane\n";
            return false;
        }
        current_number += i - '0';
    }
    input_permutation.at(3).at(2) = current_number;
    filled_indexes.at(current_number - 1) = 1;

    for(int val : filled_indexes) {
        if(val == 0) {
            std::cout << "Nie wprowadzono jednego z indeksow\n";
            return false;
        }
    }
    return true;
}

bool isPermutationSolvable(std::vector<std::vector<int>> input_permutation) {
    int number_of_transposition = 0;
    for(int i = 0; i < input_permutation.size(); i++) {
        for(int j = 0; j < input_permutation.at(i).size(); j++) {
            int number = input_permutation.at(i).at(j);
            if((number - 1) % 4 == j && (number - 1) / 4 == i)
                continue;
            if(i == 3 && j == 3)
                continue;
            int new_row = (number - 1) / 4;
            int new_column = (number - 1) % 4;
            int tmp = input_permutation.at(new_row).at(new_column);
            input_permutation.at(i).at(j) = tmp;
            input_permutation.at(new_row).at(new_column) = number;
            j--;
            number_of_transposition++;
        }
    }
    std::cout << number_of_transposition << std::endl;
    return number_of_transposition % 2 == 0;
}

int nodesNotOnPlaceHeuristic(const std::vector<std::vector<int>> & current_state) {
    int cost = 0;
    for(int i=0; i < current_state.size(); i++) {
        for(int j=0; j < current_state.at(i).size(); j++) {
            int number = current_state.at(i).at(j) - 1;
            if(number % 4 != j && number / 4 != i)
                cost++;
        }
    }
    return cost;
}

int nodesDistanceToGoodPositionHeuristic(const std::vector<std::vector<int>> & current_state) {
    int cost = 0;
    for(int i=0; i < current_state.size(); i++) {
        for(int j=0; j < current_state.at(i).size(); j++) {
            int number = current_state.at(i).at(j) - 1;
            int good_row = number / 4;
            int good_column = number % 4;
            cost += std::abs(i - good_row) + std::abs(j - good_column);
        }
    }
    return cost;
}

int main(int argc, char* argv[]) {
    std::string input;
    if(argc == 16) {
        std::cout << "Wprowadzono liczby przy uruchamianiu programu" << std::endl;
        for(int i=1; i < argc; i++) {
            input += argv[i];
            if(i != argc-1)
                input += " ";
        }
    }
    else {
        std::cout << "Wprowadz 15 liczb wyznaczajacych permutacje planszy.\n"
        << "Format - 15 liczb w jednej linii oddzielone spacjami, liczby od 1 do 15\n"
        << "Liczby wprowadzane sa rzedami, czyli co czwarta to kolejny rzad:\n";
        std::getline(std::cin, input, '\n');
    }
    std::vector<std::vector<int>> input_permutation(4, std::vector<int>(4, 0));
    bool status = convertInputPermutation(input_permutation, input);
    if(!status)
        return 1;
    status = isPermutationSolvable(input_permutation);
    if(!status) {
        std::cout << "Podana permutacja nie jest mozliwa do rozwiazania" << std::endl;
        return 1;
    }
    std::cout << "Stan poczatkowy\n";
    for(std::vector<int> & row : input_permutation) {
        for(int i : row) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
}