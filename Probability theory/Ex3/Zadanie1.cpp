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

    std::string surname = "4ceb9e6424fcec312cbc4387a0164446d38c618c";  // SHA-1 mojego nazwiska
    std::fstream surname_file;
    surname_file.open("sha-1 output.txt", std::fstream::out);
    for(char i : surname) {
        surname_file << std::bitset<8>(i);
    }
    surname_file.close();
}