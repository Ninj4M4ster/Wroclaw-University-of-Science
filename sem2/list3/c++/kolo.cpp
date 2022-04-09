#include "inc/kolo.hpp"

Kolo::Kolo(double promien) : _promien(promien) {}

double Kolo::obwod() {
    return M_PI * 2.0 * _promien;
}

double Kolo::pole() {
    return M_PI * _promien * _promien;
}
