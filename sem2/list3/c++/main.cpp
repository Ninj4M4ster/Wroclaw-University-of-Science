#include "inc/kwadrat.hpp"
#include "inc/prostokat.hpp"
#include "inc/pieciokat.hpp"
#include "inc/szesciokat.hpp"
#include "inc/kolo.hpp"
#include "inc/romb.hpp"
#include "inc/wyjatki.hpp"
#include <iostream>
#include <sstream>
#include <string>

bool czyCyfra(const char znak);
bool czyLiczba(const std::string napis);

int main(int argc, char* argv[]) {
    if(argc > 1) {
        try {
            std::string figury = argv[1];
            if(czyLiczba(figury)) {
                std::cout << figury << " - wprowadzono nieprawidlowe dane" << std::endl;
            }
            else {
                int potrzebnaIloscArgumentow = 0;
                for(int i=0; i < figury.length(); i++) {
                    switch(figury[i]) {
                        case 'o':
                            potrzebnaIloscArgumentow += 1;
                            break;
                        case 'p':
                            potrzebnaIloscArgumentow += 1;
                            break;
                        case 's':
                            potrzebnaIloscArgumentow += 1;
                            break;
                        case 'c':
                            potrzebnaIloscArgumentow += 5;
                            break;
                        default:
                            std::cout << figury[i] << " - nieprawidlowa figura" << std::endl;
                            break;
                    }
                }
                if(potrzebnaIloscArgumentow + 2 != argc)
                    throw ZaMaloArgumentow("Wprowadzono niepoprawna ilosc argumentow");
                int j=2;
                for(int i = 0; i < figury.length(); i++) {
                    try {
                        if(figury[i] == 'c') {
                            if(!czyLiczba(argv[j]) || !czyLiczba(argv[j+1]) || !czyLiczba(argv[j+2]) 
                                || !czyLiczba(argv[j+3]) || !czyLiczba(argv[j+4])) {
                                    j += 5;
                                    std::stringstream wiadomosc_bledu;
                                    wiadomosc_bledu << argv[j-5] << ", " << argv[j-4] << ", "<< argv[j+3] 
                                        << ", " << argv[j-2] << ", " << argv[j-1] << " - nieprawidlowe dane";
                                    throw NieprawidloweArgumenty(wiadomosc_bledu.str());
                                } 
                                double bok1 = std::atof(argv[j]);
                                double bok2 = std::atof(argv[j+1]);
                                double bok3 = std::atof(argv[j+2]);
                                double bok4 = std::atof(argv[j+3]);
                                double kat = std::atof(argv[j+4]);
                                j += 5;
                                if(bok1 <= 0 || bok2 <= 0 || bok3 <= 0 || bok4 <= 0) {
                                    std::stringstream wiadomosc_bledu;
                                    wiadomosc_bledu << bok1 << ", " << bok2 << ", " << bok3 << 
                                        ", " << bok4 << " - boki czworokatow musza miec wartosci wieksze od zera";
                                    throw NieprawidloweArgumenty(wiadomosc_bledu.str());
                                }
                                if(kat == 90.0) {
                                    if(bok1 == bok2 && bok2 == bok3 && bok3 == bok4) {
                                        Kwadrat *kwadrat = new Kwadrat(bok1, bok2, bok3, bok4, kat);
                                        std::cout << "Obwod kwadratu: " << kwadrat->obwod() << std::endl;
                                        std::cout << "Pole kwadratu: " << kwadrat->pole() << std::endl << std::endl;
                                    } else if(bok1 == bok2 && bok3 == bok4) {
                                        Prostokat *prostokat = new Prostokat(bok1, bok2, bok3, bok4, kat);
                                        std::cout << "Obwod prostokota: " << prostokat->obwod() << std::endl;
                                        std::cout << "Pole prostokata: " << prostokat->pole() << std::endl << std::endl;
                                    } else {
                                        std::stringstream wiadomosc_bledu;
                                        wiadomosc_bledu << bok1 << ", " << bok2 << ", " << bok3 << ", " << bok4 
                                            << " - boki nie pasuja do kwadratu i prostokata";
                                        throw NieprawidloweArgumenty(wiadomosc_bledu.str());
                                    }
                                } else if(kat > 0.0 && kat < 180.0 && (bok1 == bok2 && bok2 == bok3 && bok3 == bok4)) {
                                    Romb *romb = new Romb(bok1, bok2, bok3, bok4, kat);
                                    std::cout << "Obwod rombu: " << romb->obwod() << std::endl;
                                    std::cout << "Pole rombu: " << romb->pole() << std::endl << std::endl;
                                } else {
                                    std::stringstream wiadomosc_bledu;
                                    wiadomosc_bledu << bok1 << ", " << bok2 << ", " << bok3 << ", " << bok4 << ", " << kat 
                                        << " - argumenty nie pasuja do zadnego czworokatu";
                                    throw NieprawidloweArgumenty(wiadomosc_bledu.str());
                                }
                        } else if(figury[i] == 'o') {
                            if(!czyLiczba(argv[j])) {
                                j += 1;
                                std::stringstream wiadomosc_bledu;
                                wiadomosc_bledu << argv[j-1] << " - nieprawidlowa dana";
                                throw NieprawidloweArgumenty(wiadomosc_bledu.str());
                            }
                            double bok = std::atof(argv[j]);
                            j += 1;
                            if(bok <= 0) {
                                std::stringstream wiadomosc_bledu;
                                wiadomosc_bledu << bok << " - promien kola musi miec wartosc wieksza od zera";
                                throw NieprawidloweArgumenty(wiadomosc_bledu.str());
                            }
                            Kolo *kolo = new Kolo(bok);
                            std::cout << "Obwod kola: " << kolo->obwod() << std::endl;
                            std::cout << "Pole kola: " << kolo->pole() << std::endl << std::endl;
                        } else if(figury[i] == 'p') {
                            if(!czyLiczba(argv[j])) {
                                j += 1;
                                std::stringstream wiadomosc_bledu;
                                wiadomosc_bledu << argv[j-1] << " - nieprawidlowa dana";
                                throw NieprawidloweArgumenty(wiadomosc_bledu.str());
                            }
                            double bok = std::atof(argv[j]);
                            j += 1;
                            if(bok <= 0) {
                                std::stringstream wiadomosc_bledu;
                                wiadomosc_bledu << bok << " - bok pieciokata musi miec wartosc wieksza od zera";
                                throw NieprawidloweArgumenty(wiadomosc_bledu.str());
                            }
                            Pieciokat *pieciokat = new Pieciokat(bok);
                            std::cout << "Obwod pieciokata: " << pieciokat->obwod() << std::endl;
                            std::cout << "Pole pieciokata: " << pieciokat->pole() << std::endl << std::endl;
                        } else if(figury[i] == 's') {
                            if(!czyLiczba(argv[j])) {
                                j += 1;
                                std::stringstream wiadomosc_bledu;
                                wiadomosc_bledu << argv[j-1] << " - nieprawidlowa dana";
                                throw NieprawidloweArgumenty(wiadomosc_bledu.str());
                            }
                            double bok = std::atof(argv[j]);
                            j += 1;
                            if(bok <= 0) {
                                std::stringstream wiadomosc_bledu;
                                wiadomosc_bledu << bok << " - bok szesciokata musi miec wartosc wieksza od zera";
                                throw NieprawidloweArgumenty(wiadomosc_bledu.str());
                            }
                            Szesciokat *szesciokat = new Szesciokat(bok);
                            std::cout << "Obwod szesciokata: " << szesciokat->obwod() << std::endl;
                            std::cout << "Pole szesciokata: " << szesciokat->pole() << std::endl << std::endl;
                            } 
                    } catch(NieprawidloweArgumenty &e) {
                    std::cout << e.what() << std::endl;
                    }
                }
            }
        } catch(ZaMaloArgumentow &e) {
            std::cout << e.what() << std::endl;
        }
    }
    else {
        std::cout << "Nie wprowadzono argumentow" << std::endl;
    }
}

bool czyCyfra(const char znak) {
    if((int)znak >= '0' && (int)znak <= '9')
        return true;
    return false;
}

bool czyLiczba(const std::string napis) {
    int licz_przecinki = 0;
    for(int i=0; i < napis.length(); i++) {
        if(i == 0) {
            if(napis[i] == '-')
                continue;
        }
        if(napis[i] == '.' && licz_przecinki == 0) {
                licz_przecinki += 1;
                continue;
        }
        if(czyCyfra(napis[i]))
            continue;
        else
            return false;
    }
    return true;
}