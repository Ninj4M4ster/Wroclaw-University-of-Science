#ifndef WEZEL_DRZEWA__HPP
#define WEZEL_DRZEWA__HPP

#include <iostream>

/**
 * @brief Struktura wezla drzewa.
 * 
 */
template <typename T>
class wezel_drzewa {
    public:
    wezel_drzewa* lewy = nullptr;
    wezel_drzewa* prawy = nullptr;
    wezel_drzewa* ojciec = nullptr;
    T wartosc = (T)NULL;
};

template <>
class wezel_drzewa <std::string> {
    public:
    wezel_drzewa* lewy = nullptr;
    wezel_drzewa* prawy = nullptr;
    wezel_drzewa* ojciec = nullptr;
    std::string wartosc = "";
};

template class wezel_drzewa<int>;
template class wezel_drzewa<double>;
template class wezel_drzewa<std::string>;

#endif  // WEZEL_DRZEWA__HPP