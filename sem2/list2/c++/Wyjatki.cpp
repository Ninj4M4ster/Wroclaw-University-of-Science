#include "inc/Wyjatki.hpp"


NieLiczba::NieLiczba(const std::string &wiadomosc) noexcept : 
_wiadomosc(wiadomosc) {
}

const char *NieLiczba::what() const noexcept
{
	return this->_wiadomosc.c_str();
}

ZaDuzyWierszTrojkataPascala::ZaDuzyWierszTrojkataPascala(const std::string &wiadomosc) noexcept : 
_wiadomosc(wiadomosc) {
}

const char *ZaDuzyWierszTrojkataPascala::what() const noexcept
{
	return this->_wiadomosc.c_str();
}

ArgumentWiekszyOdArgumentuKonstruktora::ArgumentWiekszyOdArgumentuKonstruktora(const std::string &wiadomosc) noexcept : 
_wiadomosc(wiadomosc) {
}

const char *ArgumentWiekszyOdArgumentuKonstruktora::what() const noexcept
{
	return this->_wiadomosc.c_str();
}

ArgumentMniejszyOdZera::ArgumentMniejszyOdZera(const std::string &wiadomosc) noexcept : 
_wiadomosc(wiadomosc) {
}

const char *ArgumentMniejszyOdZera::what() const noexcept
{
	return this->_wiadomosc.c_str();
}