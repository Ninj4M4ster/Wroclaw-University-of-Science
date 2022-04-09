#include "inc/romb.hpp"

Romb::Romb(double bok1, double bok2, double bok3, double bok4, double kat) 
: Czworokat(bok1, bok2, bok3, bok4, kat) {}

double Romb::pole() {
    return sin(_kat * M_PI / 180.0) * _bok1 * _bok1;
}
