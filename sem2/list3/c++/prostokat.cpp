#include "inc/prostokat.hpp"

Prostokat::Prostokat(double bok1, double bok2, double bok3, double bok4, double kat) 
: Czworokat(bok1, bok2, bok3, bok4, kat) {}

double Prostokat::pole() {
    return _bok1 * _bok3;
}