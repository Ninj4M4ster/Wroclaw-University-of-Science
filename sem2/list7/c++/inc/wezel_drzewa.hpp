#ifndef WEZEL_DRZEWA__HPP
#define WEZEL_DRZEWA__HPP

#include <iostream>

/**
 * @brief Struktura wezla drzewa.
 * 
 * @tparam T Typ wprowadzanych danych.
 */
template <typename T>
struct wezel_drzewa {
    public:
    wezel_drzewa* lewy = nullptr;
    wezel_drzewa* prawy = nullptr;
    wezel_drzewa* ojciec = nullptr;
    T wartosc = (T)NULL;
};

/**
 * @brief Struktura wezla drzewa dla parametru T = string
 * 
 */
template <>
struct wezel_drzewa <std::string> {
    public:
    wezel_drzewa* lewy = nullptr;
    wezel_drzewa* prawy = nullptr;
    wezel_drzewa* ojciec = nullptr;
    std::string wartosc = "";
};

template struct wezel_drzewa<int>;
template struct wezel_drzewa<double>;
template struct wezel_drzewa<std::string>;

#endif  // WEZEL_DRZEWA__HPP