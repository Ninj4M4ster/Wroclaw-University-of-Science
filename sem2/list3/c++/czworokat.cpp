#include "inc/czworokat.hpp"

Czworokat::Czworokat(double bok1, double bok2, double bok3, double bok4, double kat) 
: _bok1(bok1), _bok2(bok2), _bok3(bok3), _bok4(bok4), _kat(kat) {};

double Czworokat::obwod() {
    return _bok1 + _bok2 + _bok3 + _bok4;
}
