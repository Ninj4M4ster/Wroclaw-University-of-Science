#include "inc/LiczbyPierwsze.hpp"
#include <math.h>

namespace liczbyPierwsze {

    LiczbyPierwsze::LiczbyPierwsze (int n) {
        tablica = new int[n];
        ilosc = 0;
        for(int i=2; i <= n; i++) {
            if(czyPierwsza(i)) {
                tablica[ilosc] = i;
                ilosc++;
            }
        }
    }

    LiczbyPierwsze::~LiczbyPierwsze() {
        delete[] tablica;
    }

    bool LiczbyPierwsze::czyPierwsza(int n) {
        if(n < 2) {
            return false;
        }
        for(int i = 2; i <= sqrt(n); i++) {
            if(n%i == 0){
                return false;
            }
        }
        return true;
    }

    int LiczbyPierwsze::liczba(int m) {
        return tablica[m];
    }

    int LiczbyPierwsze::podajIlosc() {
        return ilosc;
    }


} // namespace liczbyPierwsze