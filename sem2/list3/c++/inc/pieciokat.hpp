#ifndef PIECIOKAT__HPP
#define PIECIOKAT__HPP

#include "figura.hpp"

class Pieciokat : public Figura {
    public:
        explicit Pieciokat(double bok);
        double obwod() override;
        double pole() override;
    
    private:
        double _bok;
};

#endif  // PIECIOKA__HPP