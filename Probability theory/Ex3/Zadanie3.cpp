#include <iostream>
#include <fstream>
#include <random>
#include <unordered_map>

int random_variable(std::mt19937_64 &generator, std::bernoulli_distribution &distribution) {
    if(distribution(generator))
        return 1;
    return -1;
}

int find_bin(double value) {
    double current_max_bin = 1.0 / 20.0;
    int current_bin = 0;
    while(true) {
        current_bin++;
        if(current_bin == 20 || value <= current_max_bin)
            break;
        current_max_bin += 1.0 / 20.0;
    }
    return current_bin;
}

int main() {
    std::random_device rd{};
    std::mt19937_64 generator{rd()};
    std::bernoulli_distribution distribution(0.5);

    std::unordered_map<int, std::unordered_map<int, int>> result_bins;

    // generate experiments and save results
    for(int n=100; n <= 10000; n *= 10) {
        for (int i = 0; i < 5000; i++) {
            int current_height = 0;
            double L = 0.0;
            for(int j=0; j < n; j++) {
                current_height += random_variable(generator, distribution);
                if(current_height >= 0)
                    L++;
            }
            double P = L / n;
            int index = find_bin(P);
            result_bins[n][index]++;
        }
    }

    std::unordered_map<int, std::unordered_map<int, double>> normalized_bins;

    // normalize results
    for(int n=100; n <= 10000; n *= 10) {
        int sum = 0;
        for (int i = 1; i <= 20; i++) {
            sum += result_bins[n][i];
        }
        for(int i=1; i <= 20; i++) {
            double current_value = result_bins[n][i];
            normalized_bins[n][i] = current_value / (sum * 1.0 / 20.0);
        }
    }

    // write results to file
    std::fstream output_file;
    output_file.open("zadanie3.txt", std::fstream::out);
    output_file << "100;1000;10000\n";
    for(int i=1; i <= 20; i++) {
        output_file << normalized_bins[100][i] << ";";
        output_file << normalized_bins[1000][i] << ";";
        output_file << normalized_bins[10000][i] << "\n";
    }
    output_file.close();
}