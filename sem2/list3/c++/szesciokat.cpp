#include "inc/szesciokat.hpp"

Szesciokat::Szesciokat(double bok) : _bok(bok) {}

double Szesciokat::obwod() {
    return _bok * 6.0;
}

double Szesciokat::pole() {
    return 3.0 * _bok * _bok * sqrt(3) / 4.0;
}
