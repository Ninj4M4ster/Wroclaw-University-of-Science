#include "inc/kontroler_drzewa.hpp"

/**
 * @brief Konstruktor kontrolera drzewa.
 * 
 */
KontrolerDrzewa::KontrolerDrzewa() {
    this->drzewo_binarne = new DrzewoBinarne;
}

/**
 * @brief Destruktor kontrolera drzewa.
 * 
 */
KontrolerDrzewa::~KontrolerDrzewa() {
    delete this->drzewo_binarne;
}

/**
 * @brief Rozpocznij prace nad drzewem binarnym.
 * 
 * Metoda ta odpowiedzialna jest za przyjecie wyboru operacji na drzewie i dokonanie odpowiednich dzialan.
 * @see KontrolerDrzewa::dodajNowyWezel
 * @see KontrolerDrzewa::usunWezel
 * @see KontrolerDrzewa::szukajWezel
 * @see KontrolerDrzewa::wyswietlDrzewo
 */
void KontrolerDrzewa::rozpocznijPraceNadDrzewem() {
    int wybor;
    while(true) {
        std::cout << "Wybierz czynnosc ktora chcesz wykonac:\n"
        "-> 0 - dodaj nowy wezel do drzewa,\n"
        "-> 1 - usun wezel z drzewa,\n"
        "-> 2 - szukaj wartosci w drzewie,\n"
        "-> 3 - wyswietl drzewo,\n"
        "-> 4 - zakoncz dzialanie programu,\n"
        "->: ";
        std::cin >> wybor;
        std::cout << std::endl;
        switch(wybor) {
            case 0: {
                dodajNowyWezel();
                break;
            }
            case 1: {
                usunWezel();
                break;
            }
            case 2: {
                szukajWezel();
                break;
            }
            case 3: {
                wyswietlDrzewo();
                break;
            }
            case 4:
                return;
            default: {
                std::cout << "Dokonano nieprawidlowego wyboru.\n\n";
                break;
            }
        }
    }
}

/**
 * @brief Dodanie nowego wezla do drzewa.
 * 
 * Metoda ta odpowiedzialna jest za przyjecie typu danych i wprowadzenie nowego wezla do drzewa.
 * @see DrzewoBinarne::utworzWezelDrzewaDoPrzekazania
 */
void KontrolerDrzewa::dodajNowyWezel() {
    int wybor;
    while(true) {
        std::cout << "Okresl typ wprowadzanej danej:\n"
        "-> 0 - typ int,\n"
        "-> 1 - typ double,\n"
        "-> 2 - typ string,\n"
        "-> 3 - anuluj,\n"
        "->: ";
        std::cin >> wybor;
        std::cout << std::endl;
        std::string wprowadzana_wartosc;
        switch(wybor) {
            case 0: {
                std::cout << "Wprowadz wartosc: ";
                std::cin >> wprowadzana_wartosc;
                try {
                    int wartosc = std::stoi(wprowadzana_wartosc);
                    drzewo_binarne->utworzWezelDrzewaDoPrzekazania(wartosc, DODAWANIE_WEZLA);
                    std::cout << std::endl;
                    return;
                } catch(const std::invalid_argument &e) {
                    std::cout << "Wprowadzono niepoprawna wartosc.\n\n";
                } catch(const std::out_of_range &e) {
                    std::cout << "Wprowadzono za duza liczbe.\n\n";
                }
                break;
            } case 1: {
                std::cout << "Wprowadz wartosc: ";
                std::cin >> wprowadzana_wartosc;
                try {
                    double wartosc = std::stod(wprowadzana_wartosc);
                    drzewo_binarne->utworzWezelDrzewaDoPrzekazania(wartosc, DODAWANIE_WEZLA);
                    std::cout << std::endl;
                    return;
                } catch(const std::invalid_argument &e) {
                    std::cout << "Wprowadzono niepoprawna wartosc.\n\n";
                } catch(const std::out_of_range &e) {
                    std::cout << "Wprowadzono za duza liczbe.\n\n";
                }
                break;
            } case 2: {
                std::cout << "Wprowadz wartosc: ";
                std::cin >> wprowadzana_wartosc;
                try {
                    drzewo_binarne->utworzWezelDrzewaDoPrzekazania(wprowadzana_wartosc, DODAWANIE_WEZLA);
                    std::cout << std::endl;
                    return;
                } catch(const std::invalid_argument &e) {
                    std::cout << "Wprowadzono niepoprawna wartosc.\n\n";
                } catch(const std::out_of_range &e) {
                    std::cout << "Wprowadzono za duza liczbe.\n\n";
                }
                break;
            } case 3: {
                return;
            } default: {
                std::cout << "Dokonano nieprawidlowego wyboru.\n\n";
                break;
            }
        }
    }
}

/**
 * @brief Usuniecie poszukiwanej wartosci z drzewa.
 * 
 * Metoda ta odpowiedzialna jest za przyjecie typu danych i wartosci uzytkownika a nastepnie usuniecie podanej wartosci z drzewa.
 * @see DrzewoBinarne::utworzWezelDrzewaDoPrzekazania
 */
void KontrolerDrzewa::usunWezel() {
    int wybor;
    while(true) {
        std::cout << "Okresl typ usuwanej danej:\n"
        "-> 0 - typ int,\n"
        "-> 1 - typ double,\n"
        "-> 2 - typ string,\n"
        "-> 3 - anuluj,\n"
        "->: ";
        std::cin >> wybor;
        std::cout << std::endl;
        std::string wprowadzana_wartosc;
        switch(wybor) {
            case 0: {
                std::cout << "Wprowadz wartosc: ";
                std::cin >> wprowadzana_wartosc;
                try {
                    int wartosc = std::stoi(wprowadzana_wartosc);
                    drzewo_binarne->utworzWezelDrzewaDoPrzekazania(wartosc, USUWANIE_WEZLA);
                    std::cout << std::endl;
                    return;
                } catch(const std::invalid_argument &e) {
                    std::cout << "Wprowadzono niepoprawna wartosc.\n\n";
                } catch(const std::out_of_range &e) {
                    std::cout << "Wprowadzono za duza liczbe.\n\n";
                } catch(const NieprawidlowaWartosc &e) {
                    std::cout << e.what();
                }
                break;
            } case 1: {
                std::cout << "Wprowadz wartosc: ";
                std::cin >> wprowadzana_wartosc;
                try {
                    double wartosc = std::stod(wprowadzana_wartosc);
                    drzewo_binarne->utworzWezelDrzewaDoPrzekazania(wartosc, USUWANIE_WEZLA);
                    std::cout << std::endl;
                    return;
                } catch(const std::invalid_argument &e) {
                    std::cout << "Wprowadzono niepoprawna wartosc.\n\n";
                } catch(const std::out_of_range &e) {
                    std::cout << "Wprowadzono za duza liczbe.\n\n";
                } catch(const NieprawidlowaWartosc &e) {
                    std::cout << e.what();
                }
                break;
            } case 2: {
                std::cout << "Wprowadz wartosc: ";
                std::cin >> wprowadzana_wartosc;
                try {
                    drzewo_binarne->utworzWezelDrzewaDoPrzekazania(wprowadzana_wartosc, USUWANIE_WEZLA);
                    std::cout << std::endl;
                    return;
                } catch(const std::invalid_argument &e) {
                    std::cout << "Wprowadzono niepoprawna wartosc.\n\n";
                } catch(const std::out_of_range &e) {
                    std::cout << "Wprowadzono za duza liczbe.\n\n";
                } catch(const NieprawidlowaWartosc &e) {
                    std::cout << e.what();
                }
                break;
            } case 3: {
                return;
            } default: {
                std::cout << "Dokonano nieprawidlowego wyboru.\n\n";
                break;
            }
        }
    }
}

/**
 * @brief Szukanie wartosci w drzewie.
 * 
 * Metoda ta odpowiedzialna jest za przyjecie typu danych i wartosci uzytkownika i nastepnie znalezienie jej w drzewie.
 * @see DrzewoBinarne::utworzWezelDrzewaDoPrzekazania
 */
void KontrolerDrzewa::szukajWezel() {
    int wybor;
    while(true) {
        std::cout << "Okresl typ szukanej danej:\n"
        "-> 0 - typ int,\n"
        "-> 1 - typ double,\n"
        "-> 2 - typ stringn\n"
        "-> 3 - anuluj,\n"
        "->: ";
        std::cin >> wybor;
        std::cout << std::endl;
        std::string wprowadzana_wartosc;
        switch(wybor) {
            case 0: {
                std::cout << "Wprowadz wartosc: ";
                std::cin >> wprowadzana_wartosc;
                try {
                    int wartosc = std::stoi(wprowadzana_wartosc);
                    drzewo_binarne->utworzWezelDrzewaDoPrzekazania(wartosc, SZUKANIE_WEZLA);
                    std::cout << std::endl;
                    return;
                } catch(const std::invalid_argument &e) {
                    std::cout << "Wprowadzono niepoprawna wartosc.\n\n";
                } catch(const std::out_of_range &e) {
                    std::cout << "Wprowadzono za duza liczbe.\n\n";
                }
                break;
            } case 1: {
                std::cout << "Wprowadz wartosc: ";
                std::cin >> wprowadzana_wartosc;
                try {
                    double wartosc = std::stod(wprowadzana_wartosc);
                    drzewo_binarne->utworzWezelDrzewaDoPrzekazania(wartosc, SZUKANIE_WEZLA);
                    std::cout << std::endl;
                    return;
                } catch(const std::invalid_argument &e) {
                    std::cout << "Wprowadzono niepoprawna wartosc.\n\n";
                } catch(const std::out_of_range &e) {
                    std::cout << "Wprowadzono za duza liczbe.\n\n";
                }
                break;
            } case 2: {
                std::cout << "Wprowadz wartosc: ";
                std::cin >> wprowadzana_wartosc;
                try {
                    drzewo_binarne->utworzWezelDrzewaDoPrzekazania(wprowadzana_wartosc, SZUKANIE_WEZLA);
                    std::cout << std::endl;
                    return;
                } catch(const std::invalid_argument &e) {
                    std::cout << "Wprowadzono niepoprawna wartosc.\n\n";
                } catch(const std::out_of_range &e) {
                    std::cout << "Wprowadzono za duza liczbe.\n\n";
                }
                break;
            } case 3: {
                return;
            } default: {
                std::cout << "Dokonano nieprawidlowego wyboru.\n\n";
                break;
            }
        }
    }
}

/**
 * @brief Wyswietlenie drzewa binarnego.
 * 
 * Metoda odpowiedzialna za wyswietlenie wszystkich wartosci podanego typu w drzewie.
 * @see DrzewoBinarne::wyswietl
 */
void KontrolerDrzewa::wyswietlDrzewo() {
    int wybor;
    while(true) {
        std::cout << "Okresl typ szukanej danej:\n"
        "-> 0 - typ int,\n"
        "-> 1 - typ double,\n"
        "-> 2 - typ string,\n"
        "-> 3 - anuluj,\n"
        "->: ";
        std::cin >> wybor;
        std::cout << std::endl;
        switch(wybor) {
            case 0: {
                try {
                    drzewo_binarne->wyswietl(DRZEWO_INT);
                    std::cout << std::endl;
                    return;
                } catch(const std::invalid_argument &e) {
                    std::cout << "Wprowadzono niepoprawna wartosc.\n\n";
                } catch(const std::out_of_range &e) {
                    std::cout << "Wprowadzono za duza liczbe.\n\n";
                } catch(const NieprawidlowyWyborFunkcji &e) {
                    std::cout << e.what();
                    return;
                }
                break;
            } case 1: {
                try {
                    drzewo_binarne->wyswietl(DRZEWO_DOUBLE);
                    std::cout << std::endl;
                    return;
                } catch(const std::invalid_argument &e) {
                    std::cout << "Wprowadzono niepoprawna wartosc.\n\n";
                } catch(const std::out_of_range &e) {
                    std::cout << "Wprowadzono za duza liczbe.\n\n";
                } catch(const NieprawidlowyWyborFunkcji &e) {
                    std::cout << e.what();
                    return;
                }
                break;
            } case 2: {
                try {
                    drzewo_binarne->wyswietl(DRZEWO_STRING);
                    std::cout << std::endl;
                    return;
                } catch(const std::invalid_argument &e) {
                    std::cout << "Wprowadzono niepoprawna wartosc.\n\n";
                } catch(const std::out_of_range &e) {
                    std::cout << "Wprowadzono za duza liczbe.\n\n";
                } catch(const NieprawidlowyWyborFunkcji &e) {
                    std::cout << e.what();
                    return;
                }
                break;
            } case 3: {
                return;
            } default: {
                std::cout << "Dokonano nieprawidlowego wyboru.\n\n";
                break;
            }
        }
    }
}
