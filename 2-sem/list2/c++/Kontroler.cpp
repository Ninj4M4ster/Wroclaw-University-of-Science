#include "inc/Kontroler.hpp"

bool Kontroler::czyCyfra(const char znak) {
    if((int)znak >= '0' && (int)znak <= '9')
        return true;
    return false;
}

bool Kontroler::czyLiczba(std::string ciag_znakow) {
    for(int i=0; i < ciag_znakow.length(); i++) {
        if(i == 0) {
            if(ciag_znakow[i] == '-')
                continue;
        }
        if(Kontroler::czyCyfra(ciag_znakow[i]))
            continue;
        else
            return false;
    }
    return true;
}

int Kontroler::napisNaLiczbe(std::string napis) {
    int wynik = 0;
    int znak = 1;
    int potega = napis.length() - 1;
    for(int i=0; i < napis.length(); i++) {
        if(i == 0) {
            if(napis[i] == '-'){
                znak = -1;
                potega -= 1;
                continue;
            }
        }
        wynik += ((int)napis[i] - '0') * pow(10, potega);
        potega -= 1;
    }
    return wynik * znak;
}