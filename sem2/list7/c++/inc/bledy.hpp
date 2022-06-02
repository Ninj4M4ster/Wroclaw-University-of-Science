#ifndef BLEDY__HPP
#define BLEDY__HPP

#include <iostream>
#include <exception>

/**
 * @brief Blad wybrania nieprawidlowej funkcji do wykonania przez drzewo.
 * 
 */
class NieprawidlowyWyborFunkcji : public std::exception {
    public: 
        NieprawidlowyWyborFunkcji(const std::string &wiadomosc) noexcept;
        virtual ~NieprawidlowyWyborFunkcji() = default;
        virtual const char* what() const noexcept override;

    private:
        std::string _wiadomosc;
};

/**
 * @brief Blad wprowadzenia nieprawidlowej wartosci dla okreslonej funkcji.
 * 
 */
class NieprawidlowaWartosc : public std::exception {
    public: 
        NieprawidlowaWartosc(const std::string &wiadomosc) noexcept;
        virtual ~NieprawidlowaWartosc() = default;
        virtual const char* what() const noexcept override;

    private:
        std::string _wiadomosc;
};

#endif  // BLEDY__HPP