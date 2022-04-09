#include "inc/kwadrat.hpp"

Kwadrat::Kwadrat(double bok1, double bok2, double bok3, double bok4, double kat) 
: Czworokat(bok1, bok2, bok3, bok4, kat) {};

double Kwadrat::pole() {
    return _bok1 * _bok1;
}