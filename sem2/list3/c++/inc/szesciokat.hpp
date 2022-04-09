#ifndef SZESCIOKAT__HPP
#define SZESCIOKAT__HPP

#include "figura.hpp"

class Szesciokat : public Figura {
    public: 
        explicit Szesciokat(double bok);
        double obwod() override;
        double pole() override;

    private:
        double _bok;
};

#endif  // SZESCIOKAT__HPP