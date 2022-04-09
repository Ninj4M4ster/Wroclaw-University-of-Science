#ifndef CZWOROKAT__HPP
#define CZWOROKAT__HPP

#include <stdlib.h>
#include "figura.hpp"

class Czworokat : public Figura {
    public:
        explicit Czworokat(double bok1, double bok2, 
            double bok3, double bok4, double kat);
        double obwod() override;
        
    protected: 
        double _bok1;
        double _bok2;
        double _bok3;
        double _bok4;
        double _kat;
};

#endif // CZWOROKAT__HPP
