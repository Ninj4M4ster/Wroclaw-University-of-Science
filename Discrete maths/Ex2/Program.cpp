#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>

/**
 * @brief Metoda odpowiedzialna za utworzenie n-elementowej listy, sluzacej potem do utworzenia losowej permutacji.
 * 
 * @param n Ilosc elementow w liscie.
 * @return int* Lista postaci [n] - przechowujaca n kolejnych liczb naturalnych, zaczynajac od 1.
 */
int* createPermutationBase(const int n) {
    int* base = new int[n];
    for(int i=0; i < n; i++) {
        base[i] = i+1;
    }
    return base;
}

/**
 * @brief Metoda odpowiedzialna za zamienienie miejscami wartosci listy.
 * 
 * @param i Indeks pierwszej wartosci do zamienienia miejscami.
 * @param j Indeks drugiej wartosci do zamienienia miejscami.
 * @param list Lista, na ktorej wykonywana jest zamiana indeksow dwoch wartosci.
 */
void swapIndexes(int i, int j, int* list) {
    int tmp = list[i];
    list[i] = list[j];
    list[j] = tmp;
}

/**
 * @brief Metoda generujaca losowa permutacje.
 * 
 * @param n Ilosc elementow permutacji.
 * @return int* Tablica przechowujaca losowa permutacje.
 */
int* randomPermutation(const int n) {
    int* result = createPermutationBase(n);
    int j;
    for(int i = n-1; i > 0; i--) {
        j = std::rand() % (i + 1);
        swapIndexes(i, j, result);
    }
    return result;
}

/**
 * @brief Metoda odpowiedzialna za znalezienie indeksu, pod ktorym znajduje sie kolejny cykl w permutacji.
 * 
 * @param checking_base Lista okreslajaca czy dany indeks byl sprawdzany czy nie.
 * @param size Ilosc elementow w permutacji.
 * @return int Indeks, pod ktorym znajduje sie kolejny cykl w permutacji.
 */
int findUncheckedIndex(const int* checking_base, int size) {
    for(int i=0; i < size; i++) {
        if(checking_base[i] != 0)
            return i;
    }
    return -1;
}

/**
 * @brief Procedura rozkladajaca permutacje na cykle.
 * 
 * @param permutation Losowo wygenerowana permutacja.
 * @param size Ilosc elementow permutacji.
 * @return std::vector<std::vector<int>> Dwuwymiarowa tablica przechowujaca cykle permutacji.
 */
std::vector<std::vector<int>> getCycles(const int* permutation, int size) {
    std::vector<std::vector<int>> cycles;
    std::vector<int> cycle;
    if(size == 0)
        return cycles;
    int* checking_base = createPermutationBase(size);
    int first_element;
    int index = 0;
    int count = 0;
    do {
        first_element = index + 1;
        checking_base[index] = 0;
        int next_element = first_element;
        do {
            cycle.push_back(next_element);
            next_element = permutation[next_element - 1];
            checking_base[next_element - 1] = 0;
        } while(next_element != first_element);
        cycles.push_back(cycle);
        cycle.clear();
        index = findUncheckedIndex(checking_base, size);
    } while(index != -1);
    return cycles;
}

/**
 * @brief Test poprawnosci - znalezienie wartosci oczekiwanej liczby cykli permutacji.
 * 
 */
void meanNumberOfCyclesTest() {
    int n = 100;
    int k = 1000;
    for(int i = 1; i <= 100; i++) {
        std::cout << "n = " << i << std::endl;
        double count_cycles = 0;
        for(int j=0; j < k; j++) {
            int* permutation = randomPermutation(i);
            std::vector<std::vector<int>> cycles = getCycles(permutation, i);
            count_cycles += (double)cycles.size();
        }
        double mean_number_of_cycles = count_cycles / (double)k;
        std::cout << "mean number = " << mean_number_of_cycles << std::endl << std::endl;
    }
}

/**
 * @brief Zmienna losowa - metoda ta zwraca dlugosc najdluzszego cycklu w permutacji.
 * 
 * @param permutation Losowo wygenerowana permutacja.
 * @param size Ilosc elementow permutacji.
 * @return int Dlugosc najdluzszego cyklu w permutacji.
 */
int longestCycle(int* permutation, int size) {
    std::vector<std::vector<int>> cycles = getCycles(permutation, size);
    int max = 0;
    for(std::vector<int> cycle : cycles) {
        if(cycle.size() > max)
            max = cycle.size();
    }
    return max;
}

/**
 * @brief Glowne zadanie - znalezienie wartosci oczekiwanej najwiekszej dlugosci cycklu w rozkladzie permutacji na cykle.
 * 
 */
void mainTask() {
    int n = 100;
    int k = 1000;
    for(int i=1; i <= n; i++) {
        std::cout << "n = " << i << std::endl;
        double probability;
        int longest_cycle = 0;
        double sum = 0;
        std::map<int, int> cycle_length_and_count;
        // generujemy k permutacji i na ich podstawie liczymy wartosc oczekiwana dla danej ilosci elementow permutacji
        for(int j=0; j < k; j++) {
            int* permutation = randomPermutation(i);
            if(longestCycle(permutation, i) > longest_cycle) {
                cycle_length_and_count[longest_cycle] = 1;
                longest_cycle = longestCycle(permutation, i);
            } else {
                cycle_length_and_count[longestCycle(permutation, i)] += 1;
            }
        }
        for(auto const & [cycle_length, count] : cycle_length_and_count) {
            probability = (double)count / 1000.0;
            sum += probability * cycle_length;
        }
        std::cout << "expected value = " << sum << std::endl << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    std::srand(std::time(NULL));

    // meanNumberOfCyclesTest();
    mainTask();

    return 0;
}
