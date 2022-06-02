#include "inc/bledy.hpp"

/**
 * @brief Konstruktor bledu NieprawidlowyWyborFunkcji.
 * 
 * @param wiadomosc Wiadomosc podana przy tworzeniu obiektu.
 */
NieprawidlowyWyborFunkcji::NieprawidlowyWyborFunkcji(const std::string &wiadomosc) noexcept : 
_wiadomosc(wiadomosc) {}

/**
 * @brief Przekazanie wiadomosci podanej przy tworzeniu obiektu.
 * 
 * @return const char* Wiadomosc podana przy tworzeniu obiektu.
 */
const char *NieprawidlowyWyborFunkcji::what() const noexcept
{
	return this->_wiadomosc.c_str();
}

/**
 * @brief Konstruktor bledu NieprawidlowaWartosc.
 * 
 * @param wiadomosc Wiadomosc podana przy tworzeniu obiektu.
 */
NieprawidlowaWartosc::NieprawidlowaWartosc(const std::string &wiadomosc) noexcept : 
_wiadomosc(wiadomosc) {}

/**
 * @brief Przekazanie wiadomosci podanej przy tworzeniu obiektu.
 * 
 * @return const char* Wiadomosc podana przy tworzeniu obiektu.
 */
const char *NieprawidlowaWartosc::what() const noexcept
{
	return this->_wiadomosc.c_str();
}
