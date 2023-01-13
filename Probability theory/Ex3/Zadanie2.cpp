#include <iostream>
#include <random>
#include <fstream>
#include <unordered_map>
#include <vector>

int random_variable(std::mt19937_64 &generator, std::bernoulli_distribution &distribution) {
    if(distribution(generator))
        return 1;
    return -1;
}

int main() {
    std::random_device rd{};
    std::mt19937_64 generator{rd()};
    std::bernoulli_distribution distribution(0.5);
    std::unordered_map<int, std::vector<int>> results;

    int accuracy = 10000;

    // generate experiments for N = {5, 10, 15, 20, 25, 30}
    for(int N=5; N <= 30; N+=5) {
        for (int i = 0; i < accuracy; i++) {
            int wynik = 0;
            for (int j = 0; j < N; j++) {
                wynik += random_variable(generator, distribution);
            }
            results[N].push_back(wynik);
        }
    }

    // generate experiment for N = 100
    for(int i=0; i < accuracy; i++) {
        int wynik=0;
        for(int j=0; j < 100; j++) {
            wynik += random_variable(generator, distribution);
        }
        results[100].push_back(wynik);
    }

    // save results in file
    std::fstream output_file;
    output_file.open("zadanie2.txt", std::fstream::out);
    output_file << "5;10;15;20;25;30;100\n";
    for(int i=0; i<accuracy; i++) {
        for(int n=5; n<=30; n+=5) {
            output_file << results[n].at(i);
            output_file << ";";
        }
        output_file << results[100].at(i) << "\n";
    }
    output_file.close();
}