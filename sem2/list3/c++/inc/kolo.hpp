#ifndef KOLO__HPP
#define KOLO__HPP

#include "figura.hpp"

class Kolo : public Figura {
    public:
        explicit Kolo(double promien);
        double obwod() override;
        double pole() override;
    private:
        double _promien;
};

#endif  // KOLO__HPP