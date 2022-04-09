#ifndef KONTROLER__HPP
#define KONTROLER__HPP

#include <iostream>
#include <math.h>
#include <string>

class Kontroler {

    public:
        static bool czyLiczba(std::string ciag_znakow);
        static bool czyCyfra(const char znak);
        static int napisNaLiczbe(std::string napis);
        
};

#endif  //KONTROLER__HPP