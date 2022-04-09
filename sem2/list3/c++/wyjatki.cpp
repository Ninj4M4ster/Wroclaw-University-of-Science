#include "inc/wyjatki.hpp"

ZaMaloArgumentow::ZaMaloArgumentow(const std::string &wiadomosc) noexcept
: _wiadomosc(wiadomosc) {}

const char *ZaMaloArgumentow::what() const noexcept {
    return this -> _wiadomosc.c_str();
}

NieprawidloweArgumenty::NieprawidloweArgumenty(const std::string &wiadomosc) noexcept
: _wiadomosc(wiadomosc) {}

const char *NieprawidloweArgumenty::what() const noexcept {
    return this -> _wiadomosc.c_str();
}