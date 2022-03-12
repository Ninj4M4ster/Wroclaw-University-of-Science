#include "inc/LiczbyPierwsze.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>

bool czyCyfra(char cyfra) {
    if(((int)cyfra < '0' || (int)cyfra > '9') && (int)cyfra != '-' ) {
        return false;
    }
    return true;
}

bool czyLiczba(char* liczba) {
    for (int i=0 ; i < strlen(liczba); i++) {
        if(czyCyfra(liczba[i]) == false)
            return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if(czyLiczba(argv[1])) {
        int zakres = atoi(argv[1]);
        if(zakres > 1) {
            liczbyPierwsze::LiczbyPierwsze tablica = liczbyPierwsze::LiczbyPierwsze(zakres);
            for(int i=2; i < argc; i++) {
                if(czyLiczba(argv[i]) == false)
                    std::cout << argv[i] << " - nieprawidlowa dana" << std::endl;
                else if(atoi(argv[i]) >= tablica.podajIlosc() || atoi(argv[i]) < 0)
                    std::cout << argv[i] << " - liczba spoza zakresu" << std::endl;
                else
                    std::cout << argv[i] << " - " << tablica.liczba(atoi(argv[i])) << std::endl;
            }
        }
        else {
            std::cout << zakres << " - nieprawidlowy zakres" << std::endl;
        }
    }
    else {
        std::cout << argv[1] << " - nieprawidlowa dana jako zakres" << std::endl;
    }
    return 0;
}