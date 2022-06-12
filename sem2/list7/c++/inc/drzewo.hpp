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
template <typename T>
class DrzewoBinarne {
    public:
      // funkcje odpowiedzalne za utworzenie wezla i przekazanie do dalszego dzialania
      void utworzWezelDrzewaDoPrzekazania(T wartosc, int wybor_funkcji);
      // wyswietlenie drzewa
      void wyswietl();

    private:
      // wskaznik na korzen drzewa
      wezel_drzewa<T> *korzen = nullptr;

      // stale definujace wybor typu drzewa
      static constexpr int DRZEWO_INT = 0;
      static constexpr int DRZEWO_DOUBLE = 1;
      static constexpr int DRZEWO_STRING = 2;
      
      // wybor funkcji dla utworzoneg wezla
      void wybierzFunkcje(struct wezel_drzewa<T> &nowy_wezel, int wybor_funkji);

      // operacje wstawienia wartosci
      void wstawWezel(struct wezel_drzewa<T> &nowy_wezel);

      // operacje usuniecia wartosci
      void usunWezel(struct wezel_drzewa<T> &wezel);
      struct wezel_drzewa<T>* znajdzMinGalezi(struct wezel_drzewa<T> *aktualny_wezel);
      struct wezel_drzewa<T>* znajdzMaxGalezi(struct wezel_drzewa<T> *aktualny_wezel);
      void oderwijNastepce(struct wezel_drzewa<T> *wezel);
      void zamienKorzen(struct wezel_drzewa<T> *nowy_korzen);


      // przeszukanie drzewa
      struct wezel_drzewa<T>* szukajWezel(struct wezel_drzewa<T> szukany_wezel);
      struct wezel_drzewa<T>* szukajRightOrder(struct wezel_drzewa<T> *aktualny_wezel, struct wezel_drzewa<T> szukany_wezel, struct wezel_drzewa<T> *znaleziony_wezel);

      // operacje przeszukiwania drzewa sluzace do wyswietlenia
      void przejdzDrzewoInOrder(struct wezel_drzewa<T> *aktualny_wezel, 
                          int numer_wiersza, 
                          std::vector<std::vector<T>> &liczby_w_wierszach,
                          int ilosc_wierszy);
      int obliczIloscWierszy(struct wezel_drzewa<T> *aktualny_wezel, int numer_wiersza);

      // wyswietlanie wierszy drzewa
      void wyswietlajWiersze(int liczba_wierszy, std::vector<std::vector<T>> liczby_w_wierszach);
    
      // porownanie miedzy wartosciami dwoch wezlow
      bool czyWezelMniejszy(struct wezel_drzewa<T> nowy_wezel, struct wezel_drzewa<T> *wezel_w_drzewie);
      bool czyWezelRowny(struct wezel_drzewa<T> nowy_wezel, struct wezel_drzewa<T> wezel_w_drzewie);

};

#endif  // DRZEWO__HPP