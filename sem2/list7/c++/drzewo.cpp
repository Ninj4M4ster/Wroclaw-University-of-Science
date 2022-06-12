#include "inc/drzewo.hpp"
#include "inc/bledy.hpp"

/**
 * @brief Utworzenie wezla o podanej wartosci i przekazanie go do dalszego przetwarzania.
 * 
 * @param wartosc Liczba calkowita.
 * @param wybor_funkcji Wybrana funkcja do wykonania przez drzewo.
 * @see DrzewoBinarne::wybierzFunkcje
 */
template <typename T>
void DrzewoBinarne<T>::utworzWezelDrzewaDoPrzekazania(T wartosc, int wybor_funkcji) {
    struct wezel_drzewa<T> *nowy_wezel = new wezel_drzewa<T>;
    nowy_wezel->wartosc = wartosc;
    wybierzFunkcje(*nowy_wezel, wybor_funkcji);
}

/**
 * @brief Przekazanie utworzonego wezla do przetworzenia przez wybrana funkcje.
 * 
 * @tparam T Typ danych wezla.
 * @param nowy_wezel Poprzednio utworzony wezel zawierajacy wartosc wprowadzona przez uzytkownika.
 * @param wybor_funkcji Wybrana funkcja do wykonania przez drzewo.
 * @param typ_drzewa Typ danych wprowadzonych przez klienta.
 * @throws NieprawidlowyWyborFunkcji Blad w przypadku gdy wybrano nieprawidlowa funkcje.
 * @see DrzewoBinarne#wstawWezel
 * @see DrzewoBinarne#usunWezel
 * @see DrzewoBinarne#szukajWezel
 */
template <typename T>
void DrzewoBinarne<T>::wybierzFunkcje(struct wezel_drzewa<T> &nowy_wezel, int wybor_funkcji) {
    switch(wybor_funkcji) {
        case 0: {
            wstawWezel(nowy_wezel);
            break;
        } case 1: {
            usunWezel(nowy_wezel);
            break;
        } case 2: {
            struct wezel_drzewa<T> *wezel = szukajWezel(nowy_wezel);
            if(wezel != nullptr)
                std::cout << "Znaleziono szukana wartosc.\n\n";
            else
                std::cout << "Wezel z podana wartoscia nie znajduje sie w drzewie.\n\n";
            break;
        } default: {
            throw NieprawidlowyWyborFunkcji("Wybrano nieprawidlowa funkcje.\n");
        }
    }
}

/**
 * @brief Wstawienie nowego wezla do drzewa binarnego.
 * 
 * Metoda ta odpowiedzialna jest za wstawienie nowego wezla z podana wartoscia do drzewa.
 * Gdy to mozliwe, nowy wezel scalany jest juz z innym istniejacym w drzewie.
 * 
 * @tparam T Typ danych wezla.
 * @param nowy_wezel Poprzednio utworzony wezel zawierajacy wartosc wprowadzona przez uzytkownika.
 * @see DrzewoBinarne::czyWezelMniejszy
 */
template <typename T>
void DrzewoBinarne<T>::wstawWezel(struct wezel_drzewa<T> &nowy_wezel) {
    if(this->korzen == nullptr) {
        this->korzen = &nowy_wezel;
        return;
    }
    struct wezel_drzewa<T> *wezel_tymczasowy = this->korzen;
    // wstawianie wezla
    while(true) {
        if(czyWezelMniejszy(nowy_wezel, wezel_tymczasowy)) {
            if(wezel_tymczasowy->lewy == nullptr) {
                wezel_tymczasowy->lewy = &nowy_wezel;
                nowy_wezel.ojciec = wezel_tymczasowy;
                return;
            } else {
                wezel_tymczasowy = wezel_tymczasowy->lewy;
            }
        } else {
            if(wezel_tymczasowy->prawy == nullptr) {
                wezel_tymczasowy->prawy = &nowy_wezel;
                nowy_wezel.ojciec = wezel_tymczasowy;
                return;
            } else {
                wezel_tymczasowy = wezel_tymczasowy->prawy;
            }
        }
    }
}

/**
 * @brief Sprawdzenie czy wartosc w nowym wezle jest mniejsza od wartosci wezla znajdujacego sie w drzewie.
 * 
 * @param nowy_wezel Poprzednio utworzony wezel zawierajacy wartosc wprowadzona przez uzytkownika.
 * @param wezel_w_drzewie Wezel znajdujacy sie w drzewie binarnym.
 * @return true Wartosc nowego wezla jest mniejsza od wartosci wezla w drzewie.
 * @return false Wartosc nowego wezla jest wieksza lub rowna wartosci wezla w drzewie albo wezel nie ma wartosci.
 */
template <>
bool DrzewoBinarne<int>::czyWezelMniejszy(struct wezel_drzewa<int> nowy_wezel, struct wezel_drzewa<int> *wezel_w_drzewie) {
    if(nowy_wezel.wartosc != (int)NULL) {
        return nowy_wezel.wartosc < wezel_w_drzewie->wartosc;
    }
    return false;
}

/**
 * @brief Sprawdzenie czy wartosc w nowym wezle jest mniejsza od wartosci wezla znajdujacego sie w drzewie.
 * 
 * @param nowy_wezel Poprzednio utworzony wezel zawierajacy wartosc wprowadzona przez uzytkownika.
 * @param wezel_w_drzewie Wezel znajdujacy sie w drzewie binarnym.
 * @return true Wartosc nowego wezla jest mniejsza od wartosci wezla w drzewie.
 * @return false Wartosc nowego wezla jest wieksza lub rowna wartosci wezla w drzewie albo wezel nie ma wartosci.
 */
template <>
bool DrzewoBinarne<double>::czyWezelMniejszy(struct wezel_drzewa<double> nowy_wezel, struct wezel_drzewa<double> *wezel_w_drzewie) {
    if(nowy_wezel.wartosc != (double)NULL) {
        return (double)nowy_wezel.wartosc < (double)wezel_w_drzewie->wartosc;
    }
    return false;
}

/**
 * @brief Sprawdzenie czy wartosc w nowym wezle jest mniejsza od wartosci wezla znajdujacego sie w drzewie.
 * 
 * @param nowy_wezel Poprzednio utworzony wezel zawierajacy wartosc wprowadzona przez uzytkownika.
 * @param wezel_w_drzewie Wezel znajdujacy sie w drzewie binarnym.
 * @return true Wartosc nowego wezla jest mniejsza od wartosci wezla w drzewie.
 * @return false Wartosc nowego wezla jest wieksza lub rowna wartosci wezla w drzewie albo wezel nie ma wartosci.
 */
template <>
bool DrzewoBinarne<std::string>::czyWezelMniejszy(struct wezel_drzewa<std::string> nowy_wezel, struct wezel_drzewa<std::string> *wezel_w_drzewie) {
    if(!nowy_wezel.wartosc.empty()) {
        return nowy_wezel.wartosc.compare(wezel_w_drzewie->wartosc) == -1 ? true : false;
    }
    return false;
}

/**
 * @brief Sprawdzenie czy wartosci w nowym wezle jest rowna wartosci wezla znajdujacego sie w drzewie.
 * 
 * @param nowy_wezel Poprzednio utworzony wezel zawierajacy wartosc wprowadzona przez uzytkownika.
 * @param wezel_w_drzewie Wezel znajdujacy sie w drzewie binarnym.
 * @return true Wartosc nowego wezla jest rowna wartosci wezla w drzewie.
 * @return false Wartosc nowego wezla jest rozna od wartosci wezla w drzewie.
 */
template <>
bool DrzewoBinarne<int>::czyWezelRowny(struct wezel_drzewa<int> nowy_wezel, struct wezel_drzewa<int> wezel_w_drzewie) {
    if(nowy_wezel.wartosc !=(int) NULL && wezel_w_drzewie.wartosc != (int)NULL) {
            return (int)nowy_wezel.wartosc == (int)wezel_w_drzewie.wartosc;
    }
    return false;
}

/**
 * @brief Sprawdzenie czy wartosci w nowym wezle jest rowna wartosci wezla znajdujacego sie w drzewie.
 * 
 * @param nowy_wezel Poprzednio utworzony wezel zawierajacy wartosc wprowadzona przez uzytkownika.
 * @param wezel_w_drzewie Wezel znajdujacy sie w drzewie binarnym.
 * @return true Wartosc nowego wezla jest rowna wartosci wezla w drzewie.
 * @return false Wartosc nowego wezla jest rozna od wartosci wezla w drzewie.
 */
template <>
bool DrzewoBinarne<double>::czyWezelRowny(struct wezel_drzewa<double> nowy_wezel, struct wezel_drzewa<double> wezel_w_drzewie) {
    static constexpr double dokladnosc = 0.0000001;
    if(nowy_wezel.wartosc != (double)NULL && wezel_w_drzewie.wartosc != (double)NULL) {
        return (double)nowy_wezel.wartosc < (double)wezel_w_drzewie.wartosc;
    }
    return false;
}

/**
 * @brief Sprawdzenie czy wartosci w nowym wezle jest rowna wartosci wezla znajdujacego sie w drzewie.
 * 
 * @param nowy_wezel Poprzednio utworzony wezel zawierajacy wartosc wprowadzona przez uzytkownika.
 * @param wezel_w_drzewie Wezel znajdujacy sie w drzewie binarnym.
 * @return true Wartosc nowego wezla jest rowna wartosci wezla w drzewie.
 * @return false Wartosc nowego wezla jest rozna od wartosci wezla w drzewie.
 */
template <>
bool DrzewoBinarne<std::string>::czyWezelRowny(struct wezel_drzewa<std::string> nowy_wezel, struct wezel_drzewa<std::string> wezel_w_drzewie) {
    if(!nowy_wezel.wartosc.empty() && !wezel_w_drzewie.wartosc.empty()) {
        return nowy_wezel.wartosc.compare(wezel_w_drzewie.wartosc) == 0 ? true : false;
    }
    return false;
}
            
/**
 * @brief Wyswietlenie wartosci drzewa binarnego o podanym typie.
 * 
 * @tparam T Typ danych wezla.
 * @see DrzewoBinarne::obliczIloscWierszy
 * @see DrzewoBinarne::przejdzDrzewoInOrder
 * @see DrzewoBinarne::wyswietlajWiersze
 * @throws NieprawidlowyWyborFunkcji Blad w przypadku gdy drzewo jest puste lub wybrano nieprawidlowy typ danych drzewa.
 */
template <typename T>
void DrzewoBinarne<T>::wyswietl() {
    if(this->korzen == nullptr)
        throw NieprawidlowyWyborFunkcji("Nie mozna wyswietlic drzewa, gdyz jest ono puste.\n\n");
    int numer_wiersza = 0;
    int ilosc_wierszy;
    
    // wprowadzenie wierszy do listy oraz wyswietlenie jej
    ilosc_wierszy = obliczIloscWierszy(this->korzen, numer_wiersza);
    std::vector<std::vector<T>> liczby_w_wierszach(ilosc_wierszy);
    przejdzDrzewoInOrder(this->korzen, numer_wiersza, liczby_w_wierszach, ilosc_wierszy);
    wyswietlajWiersze(ilosc_wierszy, liczby_w_wierszach);
}

/**
 * @brief Obliczenie ilosci wierszy w drzewie.
 * 
 * Metoda ta oblicza ilosc wierszy w drzewie, uwzgledniajac wszystkie galezie.
 * 
 * @tparam T Typ danych wezla.
 * @param aktualny_wezel Wezel drzewa binarnego.
 * @param numer_wiersza Numer wiersza aktualnego wezla drzewa binarnego.
 * @return int Ilosc wierszy w drzewie.
 */
template <typename T>
int DrzewoBinarne<T>::obliczIloscWierszy(struct wezel_drzewa<T> *aktualny_wezel, int numer_wiersza) {
    if(aktualny_wezel != nullptr) {
        numer_wiersza++;
        // przeszukuj drzewo w lewo i w prawo aby sie upewnic czy w glebi drzewa nie znajduja sie jeszcze wezly
        int ilosc_wierszy_lewo = obliczIloscWierszy(aktualny_wezel->lewy, numer_wiersza);
        int ilosc_wierszy_prawo = obliczIloscWierszy(aktualny_wezel->prawy, numer_wiersza);
        if(ilosc_wierszy_lewo > ilosc_wierszy_prawo)
            numer_wiersza = ilosc_wierszy_lewo;
        else
            numer_wiersza = ilosc_wierszy_prawo;
    }
    return numer_wiersza;
}

/**
 * @brief Przejscie przez drzewo i wprowadzenie do list o odpowiednich indeksach wartosci drzewa.
 * 
 * Metoda ta przeszukuje drzewo, dodajac do tablic na odpowiednim indeksie wartosc wezla na ktorym aktualnie odbywa sie przeszukiwanie.
 * Uwzglednione sa pola puste, aby pozniej z pozniej wyswietlonego drzewa mozna bylo okreslic relacje kolejnych wezlow.
 * 
 * @tparam T Typ danych wezla.
 * @param aktualny_wezel Wezel drzewa binarnego.
 * @param numer_wiersza Numer wiersza aktualnego wezla drzewa binarnego.
 * @param liczby_w_wierszach Tablica przechowujaca wartosci wezlow drzewa.
 * @param ilosc_wierszy Ilosc wierszy w drzewie binarnym.
 */
template <typename T>
void DrzewoBinarne<T>::przejdzDrzewoInOrder(struct wezel_drzewa<T> *aktualny_wezel, 
                                        int numer_wiersza, 
                                        std::vector<std::vector<T>> &liczby_w_wierszach, 
                                        int ilosc_wierszy) {
    if(aktualny_wezel == nullptr) {
        // jesli wezel nie istnieje, do list wprowadzane sa wartosci NULL tak dlugo az funkcja nie znajduje sie w ostatnim wierszu drzewa
        if(numer_wiersza < ilosc_wierszy) {
            liczby_w_wierszach[numer_wiersza].push_back((T)NULL);
            numer_wiersza++;
            przejdzDrzewoInOrder(nullptr, numer_wiersza, liczby_w_wierszach, ilosc_wierszy);
            przejdzDrzewoInOrder(nullptr, numer_wiersza, liczby_w_wierszach, ilosc_wierszy);
        } else
            return;
    } else {
        liczby_w_wierszach[numer_wiersza].push_back(aktualny_wezel->wartosc);
        numer_wiersza++;
        przejdzDrzewoInOrder(aktualny_wezel->lewy, numer_wiersza, liczby_w_wierszach, ilosc_wierszy);
        przejdzDrzewoInOrder(aktualny_wezel->prawy, numer_wiersza, liczby_w_wierszach, ilosc_wierszy);
    }
}

/**
 * @brief Przejscie przez drzewo i wprowadzenie do list o odpowiednich indeksach wartosci drzewa.
 * 
 * Metoda ta przeszukuje drzewo, dodajac do tablic na odpowiednim indeksie wartosc wezla na ktorym aktualnie odbywa sie przeszukiwanie.
 * Uwzglednione sa pola puste, aby pozniej z pozniej wyswietlonego drzewa mozna bylo okreslic relacje kolejnych wezlow.
 * 
 * @param aktualny_wezel Wezel drzewa binarnego.
 * @param numer_wiersza Numer wiersza aktualnego wezla drzewa binarnego.
 * @param liczby_w_wierszach Tablica przechowujaca wartosci wezlow drzewa.
 * @param ilosc_wierszy Ilosc wierszy w drzewie binarnym.
 */
template <>
void DrzewoBinarne<std::string>::przejdzDrzewoInOrder(struct wezel_drzewa<std::string> *aktualny_wezel, 
                                        int numer_wiersza, 
                                        std::vector<std::vector<std::string>> &liczby_w_wierszach, 
                                        int ilosc_wierszy) {
    if(aktualny_wezel == nullptr) {
        // jesli wezel nie istnieje, do list wprowadzane sa wartosci NULL tak dlugo az funkcja nie znajduje sie w ostatnim wierszu drzewa
        if(numer_wiersza < ilosc_wierszy) {
            liczby_w_wierszach[numer_wiersza].push_back("");
            numer_wiersza++;
            przejdzDrzewoInOrder(nullptr, numer_wiersza, liczby_w_wierszach, ilosc_wierszy);
            przejdzDrzewoInOrder(nullptr, numer_wiersza, liczby_w_wierszach, ilosc_wierszy);
        } else
            return;
    } else {
        liczby_w_wierszach[numer_wiersza].push_back(aktualny_wezel->wartosc);
        numer_wiersza++;
        przejdzDrzewoInOrder(aktualny_wezel->lewy, numer_wiersza, liczby_w_wierszach, ilosc_wierszy);
        przejdzDrzewoInOrder(aktualny_wezel->prawy, numer_wiersza, liczby_w_wierszach, ilosc_wierszy);
    }
}

/**
 * @brief Wyswietlenie wartosci wierszy drzewa binarnego w terminalu.
 * 
 * @tparam T typ danych wezla.
 * @param liczba_wierszy Ilosc wierszy w drzewie binarnym.
 * @param liczby_w_wierszach Tablica przechowujaca wartosci wezlow drzewa.
 */
template <typename T>
void DrzewoBinarne<T>::wyswietlajWiersze(int liczba_wierszy, std::vector<std::vector<T>> liczby_w_wierszach) {
    for(int i = 0; i < liczba_wierszy; i++) {
        std::stringstream ss;
        // wprowadzenie wartosci do strumienia z i-tego wiersza lub '_' gdy wartosc przekazana z wezla to NULL
        for(int j = 0; j < liczby_w_wierszach[i].size(); j++) {
            if(liczby_w_wierszach[i].at(j) == (T)NULL)
                ss << "_ ";
            else
                ss << liczby_w_wierszach[i].at(j) << " ";
        }
        std::cout << ss.str() << std::endl;
    }
}

/**
 * @brief Wyswietlenie wartosci wierszy drzewa binarnego w terminalu.
 * 
 * @param liczba_wierszy Ilosc wierszy w drzewie binarnym.
 * @param liczby_w_wierszach Tablica przechowujaca wartosci wezlow drzewa.
 */ 
template <>
void DrzewoBinarne<std::string>::wyswietlajWiersze(int liczba_wierszy, std::vector<std::vector<std::string>> liczby_w_wierszach) {
    for(int i = 0; i < liczba_wierszy; i++) {
        std::stringstream ss;
        // wprowadzenie wartosci do strumienia z i-tego wiersza lub '_' gdy wartosc przekazana z wezla to NULL
        for(int j = 0; j < liczby_w_wierszach[i].size(); j++) {
            if(liczby_w_wierszach[i].at(j).empty())
                ss << "_ ";
            else
                ss << liczby_w_wierszach[i].at(j) << " ";
        }
        std::cout << ss.str() << std::endl;
    }
}

/**
 * @brief Szukanie wezla w drzewie binarnym posiadajacego wskazana wartosc.
 * 
 * @tparam T Typ danych wezla.
 * @param szukany_wezel Wezel z wartoscia poszukiwana w drzewie.
 * @return struct wezel_drzewa* Wezel z poszukiwana wartoscia lub nullptr.
 * @see DrzewoBinarne::szukajRightOrder
 */
template <typename T>
struct wezel_drzewa<T>* DrzewoBinarne<T>::szukajWezel(struct wezel_drzewa<T> szukany_wezel) {
    if(this->korzen == nullptr)
        return nullptr;

    struct wezel_drzewa<T> *szukany_wezel_w_drzewie = szukajRightOrder(this->korzen, szukany_wezel, nullptr);
    return szukany_wezel_w_drzewie;

}

/**
 * @brief Przeszukiwanie drzewa w celu znalezienia wezla z wskazana wartoscia.
 * 
 * Metoda ta przeszukuje drzewo w kolejnosci Post-Order, lecz zaczynajac od prawej galezi. 
 * Przeszukiwanie odbywa sie tak dlugo az nie zostanie znaleziony pierwszy wezel z wskazana wartoscia.
 * 
 * @tparam T Typ danych drzewa.
 * @param aktualny_wezel Wezel drzewa binarnego, od ktorego odbywac sie bedzie kolejne przeszukiwanie.
 * @param szukany_wezel Wezel zawierajacy poszukiwana wartosc.
 * @param znaleziony_wezel Wskaznik na wezel poszukiwany w drzewie binarnym.
 * @return struct wezel_drzewa* Wezel drzewa binarnego z poszukiwana wartoscia lub nullptr.
 * @see DrzewoBinarne::czyWezelRowny
 */
template <typename T>
struct wezel_drzewa<T>* DrzewoBinarne<T>::szukajRightOrder(struct wezel_drzewa<T> *aktualny_wezel, struct wezel_drzewa<T> szukany_wezel, struct wezel_drzewa<T> *znaleziony_wezel) {
    if(znaleziony_wezel != nullptr)
        return znaleziony_wezel;
    if(aktualny_wezel != nullptr) {
        znaleziony_wezel = szukajRightOrder(aktualny_wezel->prawy, szukany_wezel, znaleziony_wezel);
        if(znaleziony_wezel == nullptr)
            znaleziony_wezel = szukajRightOrder(aktualny_wezel->lewy, szukany_wezel, znaleziony_wezel);
        if(znaleziony_wezel == nullptr && czyWezelRowny(szukany_wezel, *aktualny_wezel))
            znaleziony_wezel = aktualny_wezel;
    } 
    return znaleziony_wezel;
}

/**
 * @brief Usuniecie wezla z drzewa.
 * 
 * Metoda odpowiedzialna za usuniecie wartosci z drzewa, lub gdy jest to ostatnia wartosc - usuniecie wezla.
 * 
 * @tparam T Typ danych wezla.
 * @param wezel Wezel z poszukiwana wartoscia.
 * @param typ_drzewa Typ danych wprowadzonych przez klienta.
 * @see DrzewoBinarne::szukajWezel
 * @see DrzewoBinarne::zamienKorzen
 * @see DrzewoBinarne::znajdzMaxGalezi
 * @see DrzewoBinarne::znajdzMinGalezi
 * @see DrzewoBinarne::oderwijNastepce
 * @throws NieprawidlowaWartosc Blad wywolywany gdy wezel ze wskazana wartoscia nie znajduje sie w drzewie.
 */
template <typename T>
void DrzewoBinarne<T>::usunWezel(struct wezel_drzewa<T> &wezel) {
    struct wezel_drzewa<T> *szukany_wezel = szukajWezel(wezel);
    struct wezel_drzewa<T> *nastepca = nullptr;
    // nie znaleziono wezla z podana wartoscia
    if(szukany_wezel == nullptr) {
        throw NieprawidlowaWartosc("Nie znaleziono wezla podanego do usuniecia.\n\n");
    }
    // szukamy w prawej galezi min, a jesli jej nie ma to w lewej max
    if(szukany_wezel->prawy != nullptr)
        nastepca = znajdzMinGalezi(szukany_wezel->prawy);
    else if(szukany_wezel->lewy != nullptr) 
        nastepca = znajdzMaxGalezi(szukany_wezel->lewy);
    // nie ma prawej ani lewej galezi, sprawdzamy czy to nie korzen i usuwamy
    else {
        if(szukany_wezel->ojciec == nullptr) {
            // jest to korzen, wiec go zamieniamy na null
            zamienKorzen(nastepca);
        } else {
            if(szukany_wezel->ojciec->lewy == szukany_wezel) {
                szukany_wezel->ojciec->lewy = nullptr;
                szukany_wezel->ojciec = nullptr;
            } else {
                szukany_wezel->ojciec->prawy = nullptr;
                szukany_wezel->ojciec = nullptr;
            }
            delete szukany_wezel;
            return;
        }
    }
    if(nastepca != nullptr) {
        std::cout <<"dupa" << std::endl;
        std::cout << nastepca->wartosc << std::endl;
        // laczymy ojca i lisc nastepcy
        oderwijNastepce(nastepca);

        // zamieniamy wybrany do usuniecia wezel na nastepce
        nastepca->lewy = szukany_wezel->lewy;
        nastepca->prawy = szukany_wezel->prawy;
        nastepca->ojciec = szukany_wezel->ojciec;
            
            if(szukany_wezel->lewy != nullptr) {
                szukany_wezel->lewy->ojciec = nastepca;
            }
            if(szukany_wezel->prawy != nullptr) {
                szukany_wezel->prawy->ojciec = nastepca;
            }
            if(szukany_wezel->ojciec != nullptr) {
                if(szukany_wezel->ojciec->prawy == szukany_wezel)
                    szukany_wezel->ojciec->prawy = nastepca;
                else
                    szukany_wezel->ojciec->lewy = nastepca;
            } else {
                // jesli ojciec jest null to trzeba zamienic korzen
                zamienKorzen(nastepca);
            }

            // usuwamy wybrany wezel
            szukany_wezel->ojciec = nullptr;
            szukany_wezel->prawy = nullptr;
            szukany_wezel->lewy = nullptr;

            delete szukany_wezel;

            return;
    }
}

/**
 * @brief Metoda odpowiedzialna za znalezienie najmniejszej wartosci w galezi drzewa.
 * 
 * @tparam T Typ danych wezla.
 * @param aktualny_wezel Wezel drzewa binarnego
 * @return struct wezel_drzewa<T>* Wezel drzewa binarnego o najmniejszej wartosci.
 * @see DrzewoBinarne::czyWezelMniejszy
 */
template <typename T>
struct wezel_drzewa<T>* DrzewoBinarne<T>::znajdzMinGalezi(struct wezel_drzewa<T> *aktualny_wezel) {
    if(aktualny_wezel != nullptr) {
            if(aktualny_wezel->lewy == nullptr && aktualny_wezel->prawy == nullptr)
                return aktualny_wezel;
            struct wezel_drzewa<T> *min_lewo = znajdzMinGalezi(aktualny_wezel->lewy);
            struct wezel_drzewa<T> *min_prawo = znajdzMinGalezi(aktualny_wezel->prawy);
            if(min_lewo == nullptr) {
                if(czyWezelMniejszy(*aktualny_wezel, min_prawo))
                    return aktualny_wezel;
                else
                    return min_prawo;
            } else if(min_prawo == nullptr) {
                return min_lewo;
            } else {
                if(!czyWezelMniejszy(*min_lewo, min_prawo))
                    min_lewo = min_prawo;
                return min_lewo;
            }
        }
        return aktualny_wezel;
}

/**
 * @brief Metoda odpowiedzialna za znalezienie najwiekszej wartosci w galezi drzewa.
 * 
 * @tparam T Typ danych wezla.
 * @param aktualny_wezel Wezel drzewa binarnego.
 * @return struct wezel_drzewa<T>* Wezel drzewa binarnego o najwiekszej wartosci.
 * @see DrzewoBinarne::czyWezelMniejszy
 * @see DrzewoBinarne::czyWezelRowny
 */
template <typename T>
struct wezel_drzewa<T>* DrzewoBinarne<T>::znajdzMaxGalezi(struct wezel_drzewa<T> *aktualny_wezel) {
    if(aktualny_wezel != nullptr) {
            if(aktualny_wezel->lewy == nullptr && aktualny_wezel->prawy == nullptr)
                return aktualny_wezel;
            struct wezel_drzewa<T> *max_lewo = znajdzMaxGalezi(aktualny_wezel->lewy);
            struct wezel_drzewa<T> *max_prawo = znajdzMaxGalezi(aktualny_wezel->prawy);
            if(max_prawo == nullptr) {
                if(!czyWezelMniejszy(*aktualny_wezel, max_lewo)) 
                    return aktualny_wezel;
                else
                    return max_lewo;
            } else if(max_lewo == nullptr)
                return max_prawo;
            else {
                if(czyWezelMniejszy(*max_prawo, max_lewo) || czyWezelRowny(*max_lewo, *max_prawo))
                    max_prawo = max_lewo;
                return max_prawo;
            }
        }
        return aktualny_wezel;
}

/**
 * @brief Metoda odpowiedzialna za usuniecie powiazan wezla oraz zlaczenie wezlow znajdujacych sie pod nim.
 * 
 * @tparam T Typ danych wezla.
 * @param wezel Wezel, ktory ma zostac oddzielony od drzewa.
 */
template <typename T>
void DrzewoBinarne<T>::oderwijNastepce(struct wezel_drzewa<T> *wezel) {
    if(wezel->lewy == nullptr && wezel->prawy == nullptr) {
            if(wezel->ojciec->lewy == wezel) {
                wezel->ojciec->lewy = nullptr;
            } else {
                wezel->ojciec->prawy = nullptr;
            }
        } else if(wezel->lewy != nullptr) {
            wezel->lewy->ojciec = wezel->ojciec;
            if(wezel->ojciec->lewy == wezel)
                wezel->ojciec->lewy = wezel->lewy;
            else 
                wezel->ojciec->prawy = wezel->lewy;
        } else {
            wezel->prawy->ojciec = wezel->ojciec;
            if(wezel->ojciec->lewy == wezel)
                wezel->ojciec->lewy = wezel->prawy;
            else
                wezel->ojciec->prawy = wezel->prawy;
        }
}

/**
 * @brief Metoda odpowiedzialna za zmiane korzenia na wybrany wezel.
 * 
 * @tparam T Typ danych wezla.
 * @param nowy_korzen Wezel, ktory ma zostac korzeniem.
 */
template <typename T>
void DrzewoBinarne<T>::zamienKorzen(struct wezel_drzewa<T> *nowy_korzen) {
    if(nowy_korzen == nullptr)
        delete this->korzen;
    this->korzen = nowy_korzen;
}


template class DrzewoBinarne<int>;
template class DrzewoBinarne<double>;
template class DrzewoBinarne<std::string>;