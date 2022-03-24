#ifndef WIERSZ_TROJKATA_PASCALA__HPP
#define WIERSZ_TROJKATA_PASCALA__HPP

#include <vector>
#include <iostream>

class WierszTrojkataPascala {
    public:
        WierszTrojkataPascala(std::string n);
        static int wartoscDwumianu(int n, int k);
        int wspolczynnik(int m);
    private:
        std::vector<int> tablica;
        int ilosc_elementow;
};

#endif  //WIERSZ_TROJKATA_PASCALA_HPP