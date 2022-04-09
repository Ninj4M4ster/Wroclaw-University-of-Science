#ifndef ROMB__HPP
#define ROMB__HPP

#include "czworokat.hpp"

class Romb : public Czworokat {
    public:
        explicit Romb(double bok1, double bok2, double bok3, double bok4, double kat);
        double pole() override;
};

#endif  // ROMB__HPP