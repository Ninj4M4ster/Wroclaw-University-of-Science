#ifndef PROSTOKAT__HPP
#define PROSTOKAT__HPP

#include "czworokat.hpp"

class Prostokat : public Czworokat {
    public:
        explicit Prostokat(double bok1, double bok2, double bok3, double bok4, double kat);
        double pole() override;
};

#endif  // PROSTOKAT__HPP