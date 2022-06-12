#ifndef KONTROLER_DRZEWA__HPP
#define KONTROLER_DRZEWA__HPP

#include "drzewo.hpp"
#include "bledy.hpp"

/**
 * @brief Klasa kontolera drzewa binarnego.
 * 
 * Klasa kontrolera drzewa binarnego, odpowiedzialna za przyjmowanie danych od uzytkownika i przekazywania jej do odpowiednich metod drzewa.
 * 
 */
class KontrolerDrzewa {
    public:
      KontrolerDrzewa();
      ~KontrolerDrzewa();
      void rozpocznijPraceNadDrzewem();

    private:
      // wskazniki na drzewa binarne
      DrzewoBinarne<int> *drzewo_binarne_int;
      DrzewoBinarne<double> *drzewo_binarne_double;
      DrzewoBinarne<std::string> *drzewo_binarne_string;

      // stale definujace wybor operacji na drzewie
      static constexpr int DODAWANIE_WEZLA = 0;
      static constexpr int USUWANIE_WEZLA = 1;
      static constexpr int SZUKANIE_WEZLA = 2;

      // stale definujace wybor typu drzewa
      static constexpr int DRZEWO_INT = 0;
      static constexpr int DRZEWO_DOUBLE = 1;
      static constexpr int DRZEWO_STRING = 2;

      // metody obslugujace odpowiednie dzialania na drzewie
      void dodajNowyWezel();
      void usunWezel();
      void szukajWezel();
      void wyswietlDrzewo();
};

#endif  // KONTROLER_DRZEWA__HPP