#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

int* createPermutationBase(const int n) {
    int* base = new int[n];
    for(int i=0; i < n; i++) {
        base[i] = i+1;
    }
    return base;
}

void swapIndexes(int i, int j, int* list) {
    int tmp = list[i];
    list[i] = list[j];
    list[j] = tmp;
}

int* randomPermutation(const int n) {
    int* result = createPermutationBase(n);
    int j;
    for(int i = n-1; i > 0; i--) {
        j = std::rand() % (i + 1);
        swapIndexes(i, j, result);
    }
    return result;
}

int findUncheckedIndex(const int* checking_base, int size) {
    for(int i=0; i < size; i++) {
        if(checking_base[i] != 0)
            return i;
    }
    return -1;
}

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

int main(int argc, char const *argv[])
{
    std::srand(std::time(NULL));

    int n = 8;
    int* lista = createPermutationBase(n);
    for(int i=0; i<n; i++) {
        std::cout << *(lista + i) << ", ";
    }
    std::cout << std::endl;
    int* permutacja = randomPermutation(n);
    for(int i=0; i < n; i++) {
        std::cout << i[permutacja] << ", ";
    }
    std::cout << std:: endl;
    std::vector<std::vector<int>> cycles = getCycles(permutacja, n);

    int i=1;
    for(std::vector<int> cycle : cycles) {
        std::cout << "Cykl " << i << std::endl;
        for(int value : cycle) {
            std::cout<< value << " ";
        }
        i ++;
        std::cout << std::endl;
    }

    delete lista;
    delete permutacja;

    return 0;
}
