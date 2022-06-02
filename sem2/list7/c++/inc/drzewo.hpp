#ifndef DRZEWO__HPP
#define DRZEWP__HPP

#include <vector>
#include <sstream>
#include "wezel_drzewa.hpp"

/**
 * @brief Klasa drzewa binarnego.
 * 
 * Klasa drzewa binarnego, odpowiedzialna za operacje na drzewie binarnym.
 * 
 */
class DrzewoBinarne {
    public:
      // funkcje odpowiedzalne za utworzenie wezla i przekazanie do dalszego dzialania
      void utworzWezelDrzewaDoPrzekazania(int wartosc, int wybor_funkcji);
      void utworzWezelDrzewaDoPrzekazania(double wartosc, int wybor_funkcji);
      void utworzWezelDrzewaDoPrzekazania(std::string wartosc, int wybor_funkcji);
      // wyswietlenie drzewa
      void wyswietl(int typ_drzewa);

    private:
      // wskaznik na korzen drzewa
      wezel_drzewa *korzen = nullptr;
      
      // wybor funkcji dla utworzoneg wezla
      void wybierzFunkcje(struct wezel_drzewa &nowy_wezel, int wybor_funkji);
      // operacje wstawienia wartosci
      void wstawWezel(struct wezel_drzewa &nowy_wezel);
      // operacje usuniecia wartosci
      void usunWezel(struct wezel_drzewa &wezel);
      void usunWartoscWezla(struct wezel_drzewa *wezel_w_drzewie, struct wezel_drzewa wezel_z_wartoscia);
      bool czyWezelPusty(struct wezel_drzewa *wezel); 
      // przeszukanie drzewa
      struct wezel_drzewa* szukajWezel(struct wezel_drzewa szukany_wezel);
      struct wezel_drzewa* szukajRightOrder(struct wezel_drzewa *aktualny_wezel, struct wezel_drzewa szukany_wezel, struct wezel_drzewa *znaleziony_wezel);
      // operacje przeszukiwania drzewa sluzace do wyswietlenia
      void przejdzDrzewoInOrder(struct wezel_drzewa *aktualny_wezel, 
                          int numer_wiersza, 
                          std::vector<std::vector<int>> &liczby_w_wierszach,
                          int ilosc_wierszy);
      void przejdzDrzewoInOrder(struct wezel_drzewa *aktualny_wezel, 
                          int numer_wiersza, 
                          std::vector<std::vector<double>> &liczby_w_wierszach,
                          int ilosc_wierszy);
      void przejdzDrzewoInOrder(struct wezel_drzewa *aktualny_wezel, 
                          int numer_wiersza, 
                          std::vector<std::vector<std::string>> &liczby_w_wierszach,
                          int ilosc_wierszy);
      int obliczIloscWierszy(struct wezel_drzewa *aktualny_wezel, int numer_wiersza);
      // wyswietlanie wierszy drzewa
      void wyswietlajWiersze(int liczba_wierszy, std::vector<std::vector<int>> liczby_w_wierszach);
      void wyswietlajWiersze(int liczba_wierszy, std::vector<std::vector<double>> liczby_w_wierszach);
      void wyswietlajWiersze(int liczba_wierszy, std::vector<std::vector<std::string>> liczby_w_wierszach);

      // kontrola scalania wartosci wezlow
      bool czyScalic(struct wezel_drzewa *wezel_w_drzewie, struct wezel_drzewa nowy_wezel);
      void scalWezly(struct wezel_drzewa *wezel_w_drzewie, struct wezel_drzewa &nowy_wezel);
      // porownanie miedzy wartosciami dwoch wezlow
      bool czyWezelMniejszy(struct wezel_drzewa nowy_wezel, struct wezel_drzewa *wezel_w_drzewie);
      bool czyWezelRowny(struct wezel_drzewa nowy_wezel, struct wezel_drzewa wezel_w_drzewie);
};

#endif  // DRZEWO__HPP