#ifndef WYJATKI__HPP
#define WYJATKI__HPP

#include <iostream>
#include <exception>

class NieLiczba : public std::exception {
    public: 
        NieLiczba(const std::string &wiadomosc) noexcept;
        virtual ~NieLiczba() = default;
        virtual const char* what() const noexcept override;

    private:
        std::string _wiadomosc;
    };

class ZaDuzyWierszTrojkataPascala : public std::exception {
    public: 
        ZaDuzyWierszTrojkataPascala(const std::string &wiadomosc) noexcept;
        virtual ~ZaDuzyWierszTrojkataPascala() = default;
        virtual const char* what() const noexcept override;

    private:
        std::string _wiadomosc;
    };

class ArgumentWiekszyOdArgumentuKonstruktora : public std::exception {
    public: 
        ArgumentWiekszyOdArgumentuKonstruktora(const std::string &wiadomosc) noexcept;
        virtual ~ArgumentWiekszyOdArgumentuKonstruktora() = default;
        virtual const char* what() const noexcept override;

    private:
        std::string _wiadomosc;
    };

class ArgumentMniejszyOdZera : public std::exception {
    public: 
        ArgumentMniejszyOdZera(const std::string &wiadomosc) noexcept;
        virtual ~ArgumentMniejszyOdZera() = default;
        virtual const char* what() const noexcept override;

    private:
        std::string _wiadomosc;
    };

#endif  //WYJATKI__HPP