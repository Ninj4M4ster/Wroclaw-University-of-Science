#ifndef WYJATKI__HPP
#define WYJATKI__HPP

#include <exception>
#include <string>

class NieprawidloweArgumenty : public std::exception {
    public: 
        NieprawidloweArgumenty(const std::string &wiadomosc) noexcept;
        virtual ~NieprawidloweArgumenty() = default;
        virtual const char* what() const noexcept override;

    private:
        std::string _wiadomosc;
};

class ZaMaloArgumentow : public std::exception {
    public: 
        ZaMaloArgumentow(const std::string &wiadomosc) noexcept;
        virtual ~ZaMaloArgumentow() = default;
        virtual const char* what() const noexcept override;

    private:
        std::string _wiadomosc;
};

#endif  // WYJATKI__HPP