#include <iostream>
#include <random>
#include "../body/gf_child.hpp"
#include <vector>

template<typename T>
class DHSetup {
    public:
        explicit DHSetup();
        T getGenerator();
        T power(T a, unsigned long b);
    
    private:
        T body_generator_;

        std::mt19937_64 rand_gen{std::random_device{}()};

        bool isNumberPrimary(size_t number);
        bool isGeneratorLegal(T possible_generator, std::vector<size_t> dividers);
};

template<typename T>
bool DHSetup<T>::isNumberPrimary(size_t number) {
    if(number <= 2) {
        return true;
    }
    for(size_t i = 2; i < number; i++) {
        if(number % i == 0) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool DHSetup<T>::isGeneratorLegal(T possible_generator, std::vector<size_t> dividers) {
    size_t characteristic = T::Characteristic() - 1;
    for(auto val : dividers) {
        if(possible_generator * T(characteristic / val) == T(1))
            return false;
    }
    return true;
}

template<typename T>
DHSetup<T>::DHSetup() {
    size_t characteristic = T::Characteristic() - 1;
    std::uniform_int_distribution<size_t> distribution(1, characteristic);
    std::vector<size_t> dividers;
    for(size_t i = 1; i <= std::sqrt(characteristic); i++) {
        if(isNumberPrimary(i) && characteristic % i == 0) {
            dividers.push_back(i);
        }   
    }
    body_generator_ = distribution(rand_gen);
    while(!isGeneratorLegal(body_generator_, dividers)) {
        body_generator_ = distribution(rand_gen);
    }
}

template<typename T>
T DHSetup<T>::getGenerator() {
    return body_generator_;
}

template<typename T>
T DHSetup<T>::power(T a, unsigned long b) {
    T result = 1;
    while(b > 0) {
        if(b % 2 == 0) {
            b /= 2;
            a *= a;
        } else {
            b --;
            result *= a;

            b /= 2;
            a *= a;
        }
    }
    return result;
}
