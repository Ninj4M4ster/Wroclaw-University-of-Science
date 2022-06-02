#include "inc/drzewo.hpp"
#include "inc/bledy.hpp"

/**
 * @brief Utworzenie wezla o podanej wartosci i przekazanie go do dalszego przetwarzania.
 * 
 * @param wartosc Liczba calkowita.
 * @param wybor_funkcji Wybrana funkcja do wykonania przez drzewo.
 * @see DrzewoBinarne::wybierzFunkcje
 */
void DrzewoBinarne::utworzWezelDrzewaDoPrzekazania(int wartosc, int wybor_funkcji) {
    struct wezel_drzewa *nowy_wezel = new wezel_drzewa;
    nowy_wezel->wartosc_int = wartosc;
    wybierzFunkcje(*nowy_wezel, wybor_funkcji);
}

/**
 * @brief Utworzenie wezla o podanej wartosci i przekazanie go do dalszego przetwarzania.
 * 
 * @param wartosc Liczba zmiennoprzecinkowa typu double.
 * @param wybor_funkcji Wybrana funkcja do wykonania przez drzewo.
 * @see DrzewoBinarne::wybierzFunkcje
 */
void DrzewoBinarne::utworzWezelDrzewaDoPrzekazania(double wartosc, int wybor_funkcji) {
    struct wezel_drzewa *nowy_wezel = new wezel_drzewa;
    nowy_wezel->wartosc_double = wartosc;
    wybierzFunkcje(*nowy_wezel, wybor_funkcji);
}

/**
 * @brief Utworzenie wezla o podanej wartosci i przekazanie go do dalszego przetwarzania.
 * 
 * @param wartosc Lancuch znakowy.
 * @param wybor_funkcji Wybrana funkcja do wykonania przez drzewo.
 * @see DrzewoBinarne::wybierzFunkcje
 */
void DrzewoBinarne::utworzWezelDrzewaDoPrzekazania(std::string wartosc, int wybor_funkcji) {
    struct wezel_drzewa *nowy_wezel = new wezel_drzewa;
    nowy_wezel->wartosc_string = wartosc;
    wybierzFunkcje(*nowy_wezel, wybor_funkcji);
}

/**
 * @brief Przekazanie utworzonego wezla do przetworzenia przez wybrana funkcje.
 * 
 * @param nowy_wezel Poprzednio utworzony wezel zawierajacy wartosc wprowadzona przez uzytkownika.
 * @param wybor_funkcji Wybrana funkcja do wykonania przez drzewo.
 * @throws NieprawidlowyWyborFunkcji Blad w przypadku gdy wybrano nieprawidlowa funkcje.
 * @see DrzewoBinarne#wstawWezel
 * @see DrzewoBinarne#usunWezel
 * @see DrzewoBinarne#szukajWezel
 */
void DrzewoBinarne::wybierzFunkcje(struct wezel_drzewa &nowy_wezel, int wybor_funkcji) {
    switch(wybor_funkcji) {
        case 0: {
            wstawWezel(nowy_wezel);
            break;
        } case 1: {
            usunWezel(nowy_wezel);
            break;
        } case 2: {
            struct wezel_drzewa *wezel = szukajWezel(nowy_wezel);
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
 * @param nowy_wezel Poprzednio utworzony wezel zawierajacy wartosc wprowadzona przez uzytkownika.
 * @see DrzewoBinarne::czyScalic
 * @see DrzewoBinarne::scalWezly
 * @see DrzewoBinarne::czyWezelMniejszy
 */
void DrzewoBinarne::wstawWezel(struct wezel_drzewa &nowy_wezel) {
    if(this->korzen == nullptr) {
        this->korzen = &nowy_wezel;
        return;
    }    
    struct wezel_drzewa *wezel_tymczasowy = this->korzen;
    while(true) {
        // jesli pod polem wezla binarnego z wybranym typem nie znajduje sie wartosc, wezly nalezy scalic
        if(czyScalic(wezel_tymczasowy, nowy_wezel)) {
            scalWezly(wezel_tymczasowy, nowy_wezel);
            return;
        }
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
 * @brief Okreslenie czy nowy wezel nalezy scalic z innym w drzewie.
 * 
 * @param wezel_w_drzewie Wezel znajdujacy sie w drzewie binarnym.
 * @param nowy_wezel Poprzednio utworzony wezel zawierajacy wartosc wprowadzona przez uzytkownika.
 * @return true Wezel nalezy scalic z innym w drzewie.
 * @return false Wezla nie nalezy scalac z innym w drzewie.
 */
bool DrzewoBinarne::czyScalic(struct wezel_drzewa *wezel_w_drzewie, struct wezel_drzewa nowy_wezel) {
    if(nowy_wezel.wartosc_int && !wezel_w_drzewie->wartosc_int)
        return true;
    if(nowy_wezel.wartosc_double && !wezel_w_drzewie->wartosc_double)
        return true;
    if(nowy_wezel.wartosc_string.empty() == false && wezel_w_drzewie->wartosc_string.empty())
        return true;
    return false;
}

/**
 * @brief Scalenie nowego wezla z innym w drzewie.
 * 
 * @param wezel_w_drzewie Wezel znajdujacy sie w drzewie binarnym.
 * @param nowy_wezel Poprzednio utworzony wezel zawierajacy wartosc wprowadzona przez uzytkownika.
 */
void DrzewoBinarne::scalWezly(struct wezel_drzewa *wezel_w_drzewie, struct wezel_drzewa &nowy_wezel) {
    if(nowy_wezel.wartosc_int && !wezel_w_drzewie->wartosc_int) {
        wezel_w_drzewie->wartosc_int = nowy_wezel.wartosc_int;
        return;
    }
    if(nowy_wezel.wartosc_double && !wezel_w_drzewie->wartosc_double) {
        wezel_w_drzewie->wartosc_double = nowy_wezel.wartosc_double;
        return;
    }
    if(nowy_wezel.wartosc_string.empty() == false && wezel_w_drzewie->wartosc_string.empty()) {
        std::swap(wezel_w_drzewie->wartosc_string, nowy_wezel.wartosc_string);
        return;
    }
}

/**
 * @brief Sprawdzenie czy wartosc w nowym wezle jest mniejsza od wartosci wezla znajdujacego sie w drzewie.
 * 
 * @param nowy_wezel Poprzednio utworzony wezel zawierajacy wartosc wprowadzona przez uzytkownika.
 * @param wezel_w_drzewie Wezel znajdujacy sie w drzewie binarnym.
 * @return true Wartosc nowego wezla jest mniejsza od wartosci wezla w drzewie.
 * @return false Watosc nowego wezla jest wieksza lub rowna wartosci wezla w drzewie.
 */
bool DrzewoBinarne::czyWezelMniejszy(struct wezel_drzewa nowy_wezel, struct wezel_drzewa *wezel_w_drzewie) {
    if(nowy_wezel.wartosc_int)
        return nowy_wezel.wartosc_int < wezel_w_drzewie->wartosc_int;
    if(nowy_wezel.wartosc_double)
        return nowy_wezel.wartosc_double < wezel_w_drzewie->wartosc_double;
    if(nowy_wezel.wartosc_string.empty() == false)
        return nowy_wezel.wartosc_string.compare(wezel_w_drzewie->wartosc_string) == -1 ? true : false;
    return true;
}

/**
 * @brief Sprawdzenie czy wartosci w nowym wezle jest rowna wartosci wezla znajdujacego sie w drzewie.
 * 
 * @param nowy_wezel Poprzednio utworzony wezel zawierajacy wartosc wprowadzona przez uzytkownika.
 * @param wezel_w_drzewie Wezel znajdujacy sie w drzewie binarnym.
 * @return true Wartosc nowego wezla jest rowna wartosci wezla w drzewie.
 * @return false Wartosc nowego wezla jest rozna od wartosci wezla w drzewie.
 */
bool DrzewoBinarne::czyWezelRowny(struct wezel_drzewa nowy_wezel, struct wezel_drzewa wezel_w_drzewie) {
    if(nowy_wezel.wartosc_int)
        return nowy_wezel.wartosc_int == wezel_w_drzewie.wartosc_int;
    if(nowy_wezel.wartosc_double)
        return nowy_wezel.wartosc_double == wezel_w_drzewie.wartosc_double;
    if(nowy_wezel.wartosc_string.empty() == false)
        return nowy_wezel.wartosc_string.compare(wezel_w_drzewie.wartosc_string) == 0 ? true : false;
    return true;
}

/**
 * @brief Wyswietlenie wartosci drzewa binarnego o podanym typie.
 * 
 * @param typ_drzewa Typ wartosci do wyswietlenia.
 * @see DrzewoBinarne::obliczIloscWierszy
 * @see DrzewoBinarne::przejdzDrzewoInOrder
 * @see DrzewoBinarne::wyswietlajWiersze
 * @throws NieprawidlowyWyborFunkcji Blad w przypadku gdy drzewo jest puste lub wybrano nieprawidlowy typ danych drzewa.
 */
void DrzewoBinarne::wyswietl(int typ_drzewa) {
    if(this->korzen == nullptr)
        throw NieprawidlowyWyborFunkcji("Nie mozna wyswietlic drzewa, gdyz jest ono puste.\n\n");
    int numer_wiersza = 0;
    int ilosc_wierszy = obliczIloscWierszy(this->korzen, numer_wiersza);
    
    std::vector<std::vector<int>> liczby_w_wierszach_int(ilosc_wierszy);
    std::vector<std::vector<double>> liczby_w_wierszach_double(ilosc_wierszy);
    std::vector<std::vector<std::string>> liczby_w_wierszach_string(ilosc_wierszy);
    // wprowadzenie wierszy do listy oraz wyswietlenie jej jest zalezne od wybranego typu drzewa
    switch(typ_drzewa) {
        case 0:
            przejdzDrzewoInOrder(this->korzen, numer_wiersza, liczby_w_wierszach_int, ilosc_wierszy);
            wyswietlajWiersze(ilosc_wierszy, liczby_w_wierszach_int);
            break;
        case 1:
            przejdzDrzewoInOrder(this->korzen, numer_wiersza, liczby_w_wierszach_double, ilosc_wierszy);
            wyswietlajWiersze(ilosc_wierszy, liczby_w_wierszach_double);
            break;
        case 2:
            przejdzDrzewoInOrder(this->korzen, numer_wiersza, liczby_w_wierszach_string, ilosc_wierszy);
            wyswietlajWiersze(ilosc_wierszy, liczby_w_wierszach_string);
            break;
        default:
            throw NieprawidlowyWyborFunkcji("Wybrano nieprawidlowy typ drzewa.\n");
            break;
    }
}

/**
 * @brief Obliczenie ilosci wierszy w drzewie.
 * 
 * Metoda ta oblicza ilosc wierszy w drzewie, uwzgledniajac wszystkie galezie.
 * 
 * @param aktualny_wezel Wezel drzewa binarnego.
 * @param numer_wiersza Numer wiersza aktualnego wezla drzewa binarnego.
 * @return int Ilosc wierszy w drzewie.
 */
int DrzewoBinarne::obliczIloscWierszy(struct wezel_drzewa *aktualny_wezel, int numer_wiersza) {
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
 * @param aktualny_wezel Wezel drzewa binarnego.
 * @param numer_wiersza Numer wiersza aktualnego wezla drzewa binarnego.
 * @param liczby_w_wierszach Tablica przechowujaca wartosci typu int - wartosci wezlow drzewa binarnego.
 * @param ilosc_wierszy Ilosc wierszy w drzewie binarnym.
 */
void DrzewoBinarne::przejdzDrzewoInOrder(struct wezel_drzewa *aktualny_wezel, 
                                        int numer_wiersza, 
                                        std::vector<std::vector<int>> &liczby_w_wierszach, 
                                        int ilosc_wierszy) {
    if(aktualny_wezel == nullptr) {
        // jesli wezel nie istnieje, do list wprowadzane sa wartosci NULL tak dlugo az funkcja nie znajduje sie w ostatnim wierszu drzewa
        if(numer_wiersza < ilosc_wierszy) {
            liczby_w_wierszach[numer_wiersza].push_back((int)NULL);
            numer_wiersza++;
            przejdzDrzewoInOrder(nullptr, numer_wiersza, liczby_w_wierszach, ilosc_wierszy);
            przejdzDrzewoInOrder(nullptr, numer_wiersza, liczby_w_wierszach, ilosc_wierszy);
        } else
            return;
    } else {
        liczby_w_wierszach[numer_wiersza].push_back(aktualny_wezel->wartosc_int);
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
 * @param liczby_w_wierszach Tablica przechowujaca wartosci typu double - wartosci wezlow drzewa binarnego.
 * @param ilosc_wierszy Ilosc wierszy w drzewie binarnym.
 */
void DrzewoBinarne::przejdzDrzewoInOrder(struct wezel_drzewa *aktualny_wezel, 
                                        int numer_wiersza, 
                                        std::vector<std::vector<double>> &liczby_w_wierszach, 
                                        int ilosc_wierszy) {
    if(aktualny_wezel == nullptr){
        // jesli wezel nie istnieje, do list wprowadzane sa wartosci NULL tak dlugo az funkcja nie znajduje sie w ostatnim wierszu drzewa
        if(numer_wiersza < ilosc_wierszy) {
            liczby_w_wierszach[numer_wiersza].push_back((double)NULL);
            numer_wiersza++;
            przejdzDrzewoInOrder(nullptr, numer_wiersza, liczby_w_wierszach, ilosc_wierszy);
            przejdzDrzewoInOrder(nullptr, numer_wiersza, liczby_w_wierszach, ilosc_wierszy);
        } else
            return;
    } else {
        liczby_w_wierszach[numer_wiersza].push_back(aktualny_wezel->wartosc_double);
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
 * @param liczby_w_wierszach Tablica przechowujaca wartosci typu string - wartosci wezlow drzewa binarnego.
 * @param ilosc_wierszy Ilosc wierszy w drzewie binarnym.
 */
void DrzewoBinarne::przejdzDrzewoInOrder(struct wezel_drzewa *aktualny_wezel, 
                                        int numer_wiersza, 
                                        std::vector<std::vector<std::string>> &liczby_w_wierszach, 
                                        int ilosc_wierszy) {
    if(aktualny_wezel == nullptr){
        // jesli wezel nie istnieje, do list wprowadzane sa wartosci NULL tak dlugo az funkcja nie znajduje sie w ostatnim wierszu drzewa
        if(numer_wiersza < ilosc_wierszy) {
            std::string pusty_napis;
            liczby_w_wierszach[numer_wiersza].push_back(pusty_napis);
            numer_wiersza++;
            przejdzDrzewoInOrder(nullptr, numer_wiersza, liczby_w_wierszach, ilosc_wierszy);
            przejdzDrzewoInOrder(nullptr, numer_wiersza, liczby_w_wierszach, ilosc_wierszy);
        } else
            return;
    } else {
        liczby_w_wierszach[numer_wiersza].push_back(aktualny_wezel->wartosc_string);
        numer_wiersza++;
        przejdzDrzewoInOrder(aktualny_wezel->lewy, numer_wiersza, liczby_w_wierszach, ilosc_wierszy);
        przejdzDrzewoInOrder(aktualny_wezel->prawy, numer_wiersza, liczby_w_wierszach, ilosc_wierszy);
    }
}

/**
 * @brief Wyswietlenie wartosci wierszy drzewa binarnego w terminalu.
 * 
 * @param liczba_wierszy Ilosc wierszy w drzewie binarnym.
 * @param liczby_w_wierszach Tablica przechowujaca wartosci typu int - wartosci wezlow drzewa binarnego.
 */
void DrzewoBinarne::wyswietlajWiersze(int liczba_wierszy, std::vector<std::vector<int>> liczby_w_wierszach) {
    for(int i = 0; i < liczba_wierszy; i++) {
        std::stringstream ss;
        // wprowadzenie wartosci do strumienia z i-tego wiersza lub '_' gdy wartosc przekazana z wezla to NULL
        for(int j = 0; j < liczby_w_wierszach[i].size(); j++) {
            if(liczby_w_wierszach[i].at(j) == (int)NULL)
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
 * @param liczby_w_wierszach Tablica przechowujaca wartosci typu double - wartosci wezlow drzewa binarnego.
 */
void DrzewoBinarne::wyswietlajWiersze(int liczba_wierszy, std::vector<std::vector<double>> liczby_w_wierszach) {
    for(int i = 0; i < liczba_wierszy; i++) {
        std::stringstream ss;
        // wprowadzenie wartosci do strumienia z i-tego wiersza lub '_' gdy wartosc przekazana z wezla to NULL
        for(int j = 0; j < liczby_w_wierszach[i].size(); j++)
            if(liczby_w_wierszach[i].at(j) == (double)NULL)
                ss << "_ ";
            else
                ss << liczby_w_wierszach[i].at(j) << " ";
        std::cout << ss.str() << std::endl;
    }
}

/**
 * @brief Wyswietlenie wartosci wierszy drzewa binarnego w terminalu.
 * 
 * @param liczba_wierszy Ilosc wierszy w drzewie binarnym.
 * @param liczby_w_wierszach Tablica przechowujaca wartosci typu string - wartosci wezlow drzewa binarnego.
 */
void DrzewoBinarne::wyswietlajWiersze(int liczba_wierszy, std::vector<std::vector<std::string>> liczby_w_wierszach) {
    for(int i = 0; i < liczba_wierszy; i++) {
        std::stringstream ss;
        // wprowadzenie wartosci do strumienia z i-tego wiersza lub '_' gdy wartosc przekazana z wezla to NULL
        for(int j = 0; j < liczby_w_wierszach[i].size(); j++)
            if(liczby_w_wierszach[i].at(j).empty())
                ss << "_ ";
            else
                ss << liczby_w_wierszach[i].at(j) << " ";
        std::cout << ss.str() << std::endl;
    }
}

/**
 * @brief Szukanie wezla w drzewie binarnym posiadajacego wskazana wartosc.
 * 
 * @param szukany_wezel Wezel z wartoscia poszukiwana w drzewie.
 * @return struct wezel_drzewa* Wezel z poszukiwana wartoscia lub nullptr.
 * @see DrzewoBinarne::szukajRightOrder
 */
struct wezel_drzewa* DrzewoBinarne::szukajWezel(struct wezel_drzewa szukany_wezel) {
    if(this->korzen == nullptr) 
        return nullptr;
    struct wezel_drzewa *szukany_wezel_w_drzewie = szukajRightOrder(this->korzen, szukany_wezel, nullptr);
    return szukany_wezel_w_drzewie;
}

/**
 * @brief Przeszukiwanie drzewa w celu znalezienia wezla z wskazana wartoscia.
 * 
 * Metoda ta przeszukuje drzewo w kolejnosci Post-Order, lecz zaczynajac od prawej galezi. 
 * Przeszukiwanie odbywa sie tak dlugo az nie zostanie znaleziony pierwszy wezel z wskazana wartoscia.
 * 
 * @param aktualny_wezel Wezel drzewa binarnego, od ktorego odbywac sie bedzie kolejne przeszukiwanie.
 * @param szukany_wezel Wezel zawierajacy poszukiwana wartosc.
 * @param znaleziony_wezel Wskaznik na wezel poszukiwany w drzewie binarnym.
 * @return struct wezel_drzewa* Wezel drzewa binarnego z poszukiwana wartoscia lub nullptr.
 * @see DrzewoBinarne::czyWezelRowny
 */
struct wezel_drzewa* DrzewoBinarne::szukajRightOrder(struct wezel_drzewa *aktualny_wezel, struct wezel_drzewa szukany_wezel, struct wezel_drzewa *znaleziony_wezel) {
    if(znaleziony_wezel != nullptr)
        return znaleziony_wezel;
    if(aktualny_wezel != nullptr) {
        znaleziony_wezel = szukajRightOrder(aktualny_wezel->prawy, szukany_wezel, znaleziony_wezel);
        znaleziony_wezel = szukajRightOrder(aktualny_wezel->lewy, szukany_wezel, znaleziony_wezel);
        if(czyWezelRowny(szukany_wezel, *aktualny_wezel))
            znaleziony_wezel = aktualny_wezel;
    } 
    return znaleziony_wezel;
}

/**
 * @brief Usuniecie wezla z drzewa.
 * 
 * Metoda odpowiedzialna za usuniecie wartosci z drzewa, lub gdy jest to ostatnia wartosc - usuniecie wezla.
 * 
 * @param wezel Wezel z poszukiwana wartoscia.
 * @see DrzewoBinarne::szukajWezel
 * @throws NieprawidlowaWartosc Blad wywolywany gdy wezel ze wskazana wartoscia nie znajduje sie w drzewie.
 * @todo zmienic na usuwanie wartosci zamiast z gory wezla.
 */
void DrzewoBinarne::usunWezel(struct wezel_drzewa &wezel) {
    struct wezel_drzewa *szukany_wezel = szukajWezel(wezel);
    if(szukany_wezel == nullptr) {
        throw NieprawidlowaWartosc("Nie znaleziono wezla podanego do usuniecia.\n\n");
        return;
    }
    usunWartoscWezla(szukany_wezel, wezel);
    // sprawdzenie czy wezel nie jest pusty i nie ma pod soba innych wezlow
    if(szukany_wezel->lewy == nullptr && szukany_wezel->prawy == nullptr && czyWezelPusty(szukany_wezel)) {
        // sprawdzenie czy wezel nie jest korzeniem
        if(szukany_wezel->ojciec == nullptr) {
            this->korzen = nullptr;
            delete szukany_wezel;
        } else {
            // usuniecie wezla
            if(szukany_wezel->ojciec->prawy == szukany_wezel) {
                szukany_wezel->ojciec->prawy = nullptr;
            } else if(szukany_wezel->ojciec->lewy == szukany_wezel) {
                szukany_wezel->ojciec->lewy = nullptr;
            }
            szukany_wezel->ojciec = nullptr;
            delete szukany_wezel;
        }
    }
    else {
        throw NieprawidlowaWartosc("Nie mozna usunac wezla, ktory ma pod soba inne wezly.\n\n");
    }
}

/**
 * @brief Usun wskazana wartosc z wezla drzewa binarnego.
 * 
 * @param wezel_w_drzewie Wezel drzewa binarnego, z ktorego nalezy usunac wartosc.
 * @param wezel_z_wartoscia Wezel ktory wskazuje jaka wartosc nalezy usunac.
 */
void DrzewoBinarne::usunWartoscWezla(struct wezel_drzewa *wezel_w_drzewie, struct wezel_drzewa wezel_z_wartoscia) {
    if(wezel_z_wartoscia.wartosc_int) 
        wezel_w_drzewie->wartosc_int = (int)NULL;
    else if(wezel_z_wartoscia.wartosc_double)
        wezel_w_drzewie->wartosc_double = (double)NULL;
    else if(wezel_z_wartoscia.wartosc_string.empty() == false) {
        std::string pusty_napis;
        wezel_w_drzewie->wartosc_string = pusty_napis;
    }
}

/**
 * @brief Sprawdz czy wezel ma jakiekolwiek wartosci.
 * 
 * @param wezel 
 * @return true 
 * @return false 
 */
bool DrzewoBinarne::czyWezelPusty(struct wezel_drzewa *wezel) {
    if(wezel->wartosc_int == (int)NULL && wezel->wartosc_double == (double)NULL && wezel->wartosc_string.empty())
        return true;
    return false;
}