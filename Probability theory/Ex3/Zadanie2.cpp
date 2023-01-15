#include <iostream>
#include <random>
#include <fstream>
#include <unordered_map>
#include <vector>

/**
 * Zmienna losowa o rozkładzie Bernouliego.
 *
 * @param generator Generator liczb losowych.
 * @param distribution Dystrybuanta zmiennej losowej.
 * @return 1 jeśli wylosowano prawdę, lub -1 w przeciwnym wypadku.
 */
int random_variable(std::mt19937_64 &generator, std::bernoulli_distribution &distribution) {
    if(distribution(generator))
        return 1;
    return -1;
}

/**
 * Znajdź ilość liczb w mapie, która jest mniejsza od podanej wartości.
 *
 * @param N Indeks mapy.
 * @param results Mapa z wynikami symulacji.
 * @param accuracy Ilosc wygenerowanych wartości.
 * @param value Porównywana wartość.
 * @return Ilość liczb mniejszych od podanej.
 */
int count_smaller_equal(int N, std::unordered_map<int, std::vector<int>> &results, int accuracy, int value) {
    int sum = 0;
    for(int i=0; i < accuracy; i++) {
        if(results[N].at(i) <= value)
            sum++;
    }
    return sum;
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

    // calculate distributions
    std::unordered_map<int, std::vector<double>> distributions;
    for(int N=5; N <= 30; N+=5) {
        for(int i=-N; i <= N; i++) {
            double sum = count_smaller_equal(N, results, accuracy, i);
            distributions[N].push_back(sum / (double)accuracy);
        }
    }

    // calculate distribution for N = 100
    for(int i=-100; i <= 100; i++) {
        double sum = count_smaller_equal(100, results, accuracy, i);
        distributions[100].push_back(sum / (double)accuracy);
    }

    // save results in file
    std::fstream output_file;
    output_file.open("zadanie2.txt", std::fstream::out);
    for(int N=5; N <= 30; N+=5) {
        output_file << N << "\n";
        for(int i = 0; i < distributions[N].size(); i++) {
            output_file << i - N << ";" << distributions[N].at(i) << "\n";
        }
    }
    output_file << "100" << "\n";
    for(int i = 0; i < distributions[100].size(); i++) {
        output_file << i - 100 << ";" << distributions[100].at(i) << "\n";
    }
    output_file.close();
}