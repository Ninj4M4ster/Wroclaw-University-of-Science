#include <iostream>
#include <random>
#include <bitset>
#include <fstream>

int main() {
    std::random_device rd{};
    std::minstd_rand0 generator{rd()};
    std::fstream lng_file;
    lng_file.open("linear congruential generator output.txt", std::fstream::out);
    for(int i=0; i < 5000; i++) {
        uint_fast32_t x = generator();
        std::bitset<32> bitset(x);
        lng_file << bitset;
    }
    lng_file.close();

    std::random_device rd2{};
    std::mt19937_64 generator2{rd2()};
    std::fstream mt_file;
    mt_file.open("mersenne twister output.txt", std::fstream::out);
    for(int i=0; i < 5000; i++) {
        uint_fast64_t x = generator2();
        std::bitset<64> bitset(x);
        mt_file << bitset;
    }
    mt_file.close();
}