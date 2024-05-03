#include <iostream>
#include <random>

template<typename T>
class DHSetup {
    public:
        explicit DHSetup();
        T getGenerator();
        T power(T a, unsigned long b);
    
    private:
        T body_generator_;

        std::mt19937_64 rand_gen{std::random_device{}()};
};
