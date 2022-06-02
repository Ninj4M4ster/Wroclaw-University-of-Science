#ifndef WEZEL_DRZEWA__HPP
#define WEZEL_DRZEWA__HPP

#include <iostream>

/**
 * @brief Struktura wezla drzewa.
 * 
 */
struct wezel_drzewa {
    wezel_drzewa* lewy = nullptr;
    wezel_drzewa* prawy = nullptr;
    wezel_drzewa* ojciec = nullptr;
    int wartosc_int = (int)NULL;
    double wartosc_double = (double)NULL;
    std::string wartosc_string;

};

#endif  // WEZEL_DRZEWA__HPP