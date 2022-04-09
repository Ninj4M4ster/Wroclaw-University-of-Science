#include "inc/pieciokat.hpp"

Pieciokat::Pieciokat(double bok) : _bok(bok) {}

double Pieciokat::obwod() {
    return 5.0 * _bok;
}

double Pieciokat::pole() {
    return (5.0 / 4.0) * _bok * _bok * (1.0 / tan(36.0 * M_PI / 180.0));
}
