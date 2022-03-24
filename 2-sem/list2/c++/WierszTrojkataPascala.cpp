#include "inc/WierszTrojkataPascala.hpp"
#include "inc/Wyjatki.hpp"
#include "inc/Kontroler.hpp"

WierszTrojkataPascala::WierszTrojkataPascala(std::string n) {
    if(!Kontroler::czyLiczba(n))
        throw new NieLiczba("Nieprawidlowa dana jako numer wiersza");
    else {
        int dlugosc = Kontroler::napisNaLiczbe(n);
        ilosc_elementow = dlugosc + 1;
        if(dlugosc < 0)
            throw new ArgumentMniejszyOdZera("Nieprawidlowy numer wiersza");
        tablica = std::vector<int>(dlugosc + 1);
        for(int i=0; i <= dlugosc; i++) {
            tablica.at(i) = WierszTrojkataPascala::wartoscDwumianu(dlugosc, i);
            if(tablica.at(i) < 0)
                throw new ZaDuzyWierszTrojkataPascala("Wartosc wiersza przekraczaja maksymalna wartosc typu liczb calkowitych");
        }
    }
}

int WierszTrojkataPascala::wartoscDwumianu(int n, int k) {
    if(k == 0)
        return 1;
    int wynik = n;
    for(int i=1; i<k; i++) {
        wynik *= n-i;
        wynik /= i+1;
    }
    return wynik;
}

int WierszTrojkataPascala::wspolczynnik(int m) {
    if(m < 0)
        throw new ArgumentMniejszyOdZera("liczba spoza zakresu");
    else if(m >= ilosc_elementow) 
        throw new ArgumentWiekszyOdArgumentuKonstruktora("liczba spoza zakresu");
    else
        return tablica.at(m);
}