#include "inc/WierszTrojkataPascala.hpp"
#include "inc/Kontroler.hpp"
#include "inc/Wyjatki.hpp"
#include <cstdlib>

int main(int argc, char* argv[]) {
    try {
        if(argc > 1) {
            WierszTrojkataPascala tablica = WierszTrojkataPascala(argv[1]);
            for(int i=2; i < argc; i++) {
                try {
                    if(Kontroler::czyLiczba(argv[i]))
                        std::cout << argv[i] << " - " << tablica.wspolczynnik(Kontroler::napisNaLiczbe(argv[i])) << std::endl;
                    else
                        std::cout << argv[i] << " - nieprawidlowa dana" << std::endl;
                }
                catch(const ArgumentWiekszyOdArgumentuKonstruktora* e) {
                    std::cout << argv[i] << " - " << e->what() << std::endl;
                }
                catch(const ArgumentMniejszyOdZera* e) {
                    std::cout << argv[i] << " - " << e->what() << std::endl;
                }
            }
        }
        else
            std::cout << "Nie podano argumentow" << std::endl;
    }
    catch(const NieLiczba* e) {
        std::cout << argv[1] << " - " << e->what() << std::endl;
    }
    catch(const ArgumentMniejszyOdZera* e) {
        std::cout << argv[1] << " - " << e->what() << std::endl;
    }
    catch(const ZaDuzyWierszTrojkataPascala* e) {
        std::cout <<e->what() << std::endl;
    }
}