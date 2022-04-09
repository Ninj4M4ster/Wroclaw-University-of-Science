#ifndef KWADRAT__HPP
#define KWADRAT__HPP

#include <stdlib.h>
#include "czworokat.hpp"

class Kwadrat : public Czworokat {
    public:
        explicit Kwadrat(double bok1, double bok2, double bok3, double bok4, double kat);
        double pole() override;
};

#endif  // KWADRAT__HPP