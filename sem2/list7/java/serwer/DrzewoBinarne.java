import java.util.ArrayList;

/**
 * Klasa implementujaca drzewo binarne.
 * Obsluguje dodawanie wezla, usuwanie wartosci lub wezla, 
 * wyszukiwanie wezla i wyswietlanie calego drzewa.
 */
class DrzewoBinarne {
    /**Korzen drzewa binarnego. */
    private WezelDrzewa korzen = null;

    // zmienne pomocnicze definujace dzialania na drzewie
    private final int DODAWANIE_WEZLA = 0;
    private final int USUWANIE_WEZLA = 1;
    private final int SZUKANIE_WEZLA = 2;

    // zmienne pomocnicze definiujace typy drzewa
    private final int DRZEWO_INT = 0;
    private final int DRZEWO_DOUBLE = 1;
    private final int DRZEWO_STRING = 2;

    /**
     * Metoda ta odpowiedzialna jest za utworzenie wezla drzewa binarnego z podanej wartosci oraz przekazanie go do dalszego dzialania.
     * 
     * @see DrzewoBinarne#wybierzFunkcje
     * @param wartosc Liczba calkowita podana przez uzytkownika.
     * @param wybor_funkcji Funkcja, ktora ma zostac wykonana na drzewie.
     * @return Czy pozadane dzialanie sie powiodlo?
     * @throws NieprawidlowyWyborFunkcji Wybrano nieprawidlowa funkcje.
     * @throws NieprawidlowaWartosc Przekazano do funkcji nieprawidlowa wartosc.
     */
    public boolean przekazWartosc(int wartosc, int wybor_funkcji) throws NieprawidlowyWyborFunkcji {
        WezelDrzewa wezel = new WezelDrzewa();
        wezel.wartosc_int = wartosc;
        return wybierzFunkcje(wezel, wybor_funkcji);
    }

    /**
     * Metoda ta odpowiedzialna jest za utworzenie wezla drzewa binarnego z podanej wartosci oraz przekazanie go do dalszego dzialania.
     * 
     * @see DrzewoBinarne#wybierzFunkcje
     * @param wartosc Liczba zmiennoprzecinkowa podana przez uzytkownika.
     * @param wybor_funkcji Funkcja, ktora ma zostac wykonana na drzewie.
     * @return Czy pozadane dzialanie sie powiodlo?
     * @throws NieprawidlowyWyborFunkcji Wybrano nieprawidlowa funkcje.
     * @throws NieprawidlowaWartosc Przekazano do funkcji nieprawidlowa wartosc.
     */
    public boolean przekazWartosc(double wartosc, int wybor_funkcji) throws NieprawidlowyWyborFunkcji {
        WezelDrzewa wezel = new WezelDrzewa();
        wezel.wartosc_double = wartosc;
        return wybierzFunkcje(wezel, wybor_funkcji);
    }

    /**
     * Metoda ta odpowiedzialna jest za utworzenie wezla drzewa binarnego z podanej wartosci oraz przekazanie go do dalszego dzialania.
     * 
     * @see DrzewoBinarne#wybierzFunkcje
     * @param wartosc Lancuch znakow podana przez uzytkownika.
     * @param wybor_funkcji Funkcja, ktora ma zostac wykonana na drzewie.
     * @return Czy pozadane dzialanie sie powiodlo?
     * @throws NieprawidlowyWyborFunkcji Wybrano nieprawidlowa funkcje.
     * @throws NieprawidlowaWartosc Przekazano do funkcji nieprawidlowa wartosc.
     */
    public boolean przekazWartosc(String wartosc, int wybor_funkcji) throws NieprawidlowyWyborFunkcji {
        WezelDrzewa wezel = new WezelDrzewa();
        wezel.wartosc_string = wartosc;
        return wybierzFunkcje(wezel, wybor_funkcji);
    }

    /**
     * Metoda ta odpowiedzialna jest za wykonanie dzialania na drzewie, przekazujac utworzony wczesniej wezel.
     * 
     * @see DrzewoBinarne#wstawWezel
     * @see DrzewoBinarne#usunWezel
     * @see DrzewoBinarne#szukajWezel
     * @param nowy_wezel Poprzednio utworzony wezel zawierajacy pojedyncza wartosc.
     * @param wybor_funkcji Funkcja wybrana przez uzytkownika.
     * @return Czy dzialanie funkcji sie powiodlo?
     * @throws NieprawidlowyWyborFunkcji Wybrano nieprawidlowa funkcje.
     * @throws NieprawidlowaWartosc Przekazano do funkcji nieprawidlowa wartosc.
     */
    private boolean wybierzFunkcje(WezelDrzewa nowy_wezel, int wybor_funkcji) throws NieprawidlowyWyborFunkcji {
        switch(wybor_funkcji) {
            case DODAWANIE_WEZLA: {
                return this.wstawWezel(nowy_wezel);
            } case USUWANIE_WEZLA: {
                return this.usunWezel(nowy_wezel);
            } case SZUKANIE_WEZLA: {
                WezelDrzewa szukany_wezel = this.szukajWezel(nowy_wezel);
                if(szukany_wezel != null)
                    return true;
                return false;
            }
        }
        return false;
    }

    /**
     * Metoda ta odpowiedzialna jest za wstawienie nowego wezla w odpowiednie miejsce w drzewie binarnym.
     * W przypadku, gdy w odpowiednim miejscu znajduje sie juz wezel, nowy wezel jest z nim scalany.
     * 
     * @see DrzewoBinarne#czyScalic
     * @see DrzewoBinarne#scalWezly
     * @see DrzewoBinarne#czyWezelMniejszy
     * @param nowy_wezel Poprzednio utworzony wezel zawierajacy pojedyncza wartosc.
     * @return Czy dodanie nowego wezla sie powidodlo?
     */
    private boolean wstawWezel(WezelDrzewa nowy_wezel) {
        if(this.korzen == null) {
            this.korzen = nowy_wezel;
            return true;
        }
        WezelDrzewa wezel_tymczasowy = this.korzen;
        while(true) {
            // jesli pod polem wezla drzewa binarnego z wybranym typem brakuje wartosci, nalezy scalic
            if(czyScalic(wezel_tymczasowy, nowy_wezel)) {
                return scalWezly(wezel_tymczasowy, nowy_wezel);
            }
            if(czyWezelMniejszy(nowy_wezel, wezel_tymczasowy)) {
                if(wezel_tymczasowy.lewy == null) {
                    wezel_tymczasowy.lewy = nowy_wezel;
                    nowy_wezel.ojciec = wezel_tymczasowy;
                    return true;
                } else {
                    wezel_tymczasowy = wezel_tymczasowy.lewy;
                }
            } else {
                if(wezel_tymczasowy.prawy == null) {
                    wezel_tymczasowy.prawy = nowy_wezel;
                    nowy_wezel.ojciec = wezel_tymczasowy;
                    return true;
                } else {
                    wezel_tymczasowy = wezel_tymczasowy.prawy;
                }
            }
        }
    }

    /**
     * Metoda ta sprawdza, czy dwa podane wezly nalezy scalic, czy nie.
     * 
     * @param wezel_w_drzewie Wezel znajdujacy sie w drzewie binarnym.
     * @param nowy_wezel Poprzednio utworzony wezel zawierajacy pojedncza wartosc.
     * @return Czy wezly nalezy scalic?
     */
    private boolean czyScalic(WezelDrzewa wezel_w_drzewie, WezelDrzewa nowy_wezel) {
        if(nowy_wezel.wartosc_int != null && wezel_w_drzewie.wartosc_int == null)
            return true;
        if(nowy_wezel.wartosc_double != null && wezel_w_drzewie.wartosc_double == null)
            return true;
        if(nowy_wezel.wartosc_string != null && wezel_w_drzewie.wartosc_string == null)
            return true;
        return false;
    }

    /**
     * Metoda ta odpowiedzialna jest za scalenie wartosci dwoch wezlow.
     * 
     * @param wezel_w_drzewie Wezel znajdujacy sie w drzewie binarnym.
     * @param nowy_wezel Poprzednio utworzony wezel zawierajacy pojedyncza wartosc.
     * @return Czy scalanie wezlow sie powiodlo?
     */
    private boolean scalWezly(WezelDrzewa wezel_w_drzewie, WezelDrzewa nowy_wezel) {
        if(nowy_wezel.wartosc_int != null && wezel_w_drzewie.wartosc_int == null) {
            wezel_w_drzewie.wartosc_int = nowy_wezel.wartosc_int;
            return true;
        }
        if(nowy_wezel.wartosc_double != null && wezel_w_drzewie.wartosc_double == null) {
            wezel_w_drzewie.wartosc_double = nowy_wezel.wartosc_double;
            return true;
        }
        if(nowy_wezel.wartosc_string != null && wezel_w_drzewie.wartosc_string == null) {
            wezel_w_drzewie.wartosc_string = nowy_wezel.wartosc_string;
            return true;
        }
        return false;
    }

    /**
     * Metoda ta odpowiedzialna jest za okreslenie, czy nowy wezel ma wartosci mniejsze 
     * niz podany wezel znajdujacy sie w drzewie binarnym.
     * 
     * @param nowy_wezel Poprzednio utworzony wezel zawierajacy pojedyncza wartosc.
     * @param wezel_w_drzewie Wezel znajdujacy sie w drzewie binarnym.
     * @return Czy wartosc w nowym wezle jest mniejsza od wartosci w wezle znajdujacym sie w drzewie binarnym?
     */
    private boolean czyWezelMniejszy(WezelDrzewa nowy_wezel, WezelDrzewa wezel_w_drzewie) {
        if(nowy_wezel.wartosc_int != null)
            return nowy_wezel.wartosc_int < wezel_w_drzewie.wartosc_int;
        if(nowy_wezel.wartosc_double != null)
            return Double.compare(nowy_wezel.wartosc_double, wezel_w_drzewie.wartosc_double) < 0 ? true : false;
        if(nowy_wezel.wartosc_string != null)
            return nowy_wezel.wartosc_string.compareTo(wezel_w_drzewie.wartosc_string) < 0 ? true : false;
        return false;
    }

    /**
     * Metoda ta odpowiedzialna jest za okreslenie, czy wartosc w nowym wezle jest rowna wartosci
     * znajdujacej sie w wezle drzewa binarnego.
     * 
     * @param nowy_wezel Poprzednio utworzony wezel zawierajacy pojedyncza wartosc.
     * @param wezel_w_drzewie Wezel znajdujacy sie w drzewie binarnym.
     * @return Czy wartosc nowego wezla jest rowna wartosci znajdujacej sie w wezle drzewa binarnego?
     */
    private boolean czyWezelRowny(WezelDrzewa nowy_wezel, WezelDrzewa wezel_w_drzewie) {
        if(nowy_wezel.wartosc_int != null && wezel_w_drzewie.wartosc_int != null)
            return nowy_wezel.wartosc_int == wezel_w_drzewie.wartosc_int;
        if(nowy_wezel.wartosc_double != null && wezel_w_drzewie.wartosc_double != null)
            return Double.compare(nowy_wezel.wartosc_double, wezel_w_drzewie.wartosc_double) == 0 ? true : false;
        if(nowy_wezel.wartosc_string != null && wezel_w_drzewie.wartosc_string != null)
            return nowy_wezel.wartosc_string.compareTo(wezel_w_drzewie.wartosc_string) == 0 ? true : false;
        return false;
    }


    /**
     * Metoda ta odpowiedzialna jest za zapisanie wartosci wezlow drzewa w wiersze i utworzenie napisu,
     * ktory nastepnie zostanie wyslany do klienta.
     * 
     * @see DrzewoBinarne#obliczIloscWierszy
     * @see DrzewoBinarne#przejdzDrzewoIntInOrder
     * @see DrzewoBinarne#przejdzDrzewoDoubleInOrder
     * @see DrzewoBinarne#przejdzDrzewoStringInOrder
     * @see DrzewoBinarne#wierszeIntNaNapis
     * @see DrzewoBinarne#wierszeDoubleNaNapis
     * @see DrzewoBinarne#wierszeStringNaNapis
     * @param typ_drzewa Typ danych w drzewie.
     * @return Sformatowany napis zawierajacy wartosci drzewa binarnego.
     * @throws NieprawidlowaWartosc Podano zly typ drzewa.
     * @throws NieprawidlowyWyborFunkcji Korzen drzewa jest pusty.
     */
    public String wyswietl(int typ_drzewa) throws NieprawidlowyWyborFunkcji, NieprawidlowaWartosc {
        if(this.korzen == null)
            throw new NieprawidlowyWyborFunkcji("EMPTY_TREE");
        int numer_wiersza = 0;
        int ilosc_wierszy = obliczIloscWierszy(this.korzen, numer_wiersza);

        // wprowadzenie wierszy do listy oraz wyswietlenie jej jest zalezne od wybranego typu drzewa
        switch(typ_drzewa) {
            case DRZEWO_INT: {
                ArrayList<ArrayList<Integer>> wartosci_wierszy = new ArrayList<>(ilosc_wierszy);
                for(int i=0; i < ilosc_wierszy; i++)
                    wartosci_wierszy.add(new ArrayList<Integer>());
                przejdzDrzewoIntInOrder(this.korzen, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
                return wierszeIntNaNapis(ilosc_wierszy, wartosci_wierszy);
            } case DRZEWO_DOUBLE: {
                ArrayList<ArrayList<Double>> wartosci_wierszy = new ArrayList<>(ilosc_wierszy);
                for(int i=0; i< ilosc_wierszy; i++)
                    wartosci_wierszy.add(new ArrayList<Double>());
                przejdzDrzewoDoubleInOrder(this.korzen, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
                return wierszeDoubleNaNapis(ilosc_wierszy, wartosci_wierszy);
            } case DRZEWO_STRING: {
                ArrayList<ArrayList<String>> wartosci_wierszy = new ArrayList<>(ilosc_wierszy);
                for(int i=0; i< ilosc_wierszy; i++)
                    wartosci_wierszy.add(new ArrayList<String>());
                przejdzDrzewoStringInOrder(this.korzen, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
                return wierszeStringNaNapis(ilosc_wierszy, wartosci_wierszy);
            } default:
                throw new NieprawidlowaWartosc("WRONG_TYPE");
        }
    }

    /**
     * Metoda odpowiedzialna za obliczenie lacznej ilosci wierszy drzewa binarnego.
     * Przeszukuje ona kazdy wezel w celu znalezienie najdluzszej trasy od korzena do liscia.
     * 
     * @param aktualny_wezel Wezel drzewa binarnego.
     * @param numer_wiersza Aktualna dlugosc sciezki od korzenia drzewa.
     * @return Ilosc wierszy w drzewie binarnym.
     */
    private int obliczIloscWierszy(WezelDrzewa aktualny_wezel, int numer_wiersza) {
        if(aktualny_wezel != null) {
            numer_wiersza ++;
            // przeszukuj drzewo w lewo i prawo aby sie upewnic, czy glebi drzewa nie znajduja sie jeszcze wezly
            int ilosc_wierszy_lewo = obliczIloscWierszy(aktualny_wezel.lewy, numer_wiersza);
            int ilosc_wierszy_prawo = obliczIloscWierszy(aktualny_wezel.prawy, numer_wiersza);
            if(ilosc_wierszy_lewo > ilosc_wierszy_prawo)
                numer_wiersza = ilosc_wierszy_lewo;
            else
                numer_wiersza = ilosc_wierszy_prawo;
        }
        return numer_wiersza;
    }

    /**
     * Metoda odpowiedzialna za wprowadzenie wartosci calkowitych wezlow drzewa do list. 
     * 
     * @param aktualny_wezel Wezel drzewa binarnego.
     * @param numer_wiersza Aktualna dlugosc sciezki od korzenia do aktualnego wezla.
     * @param wartosci_wierszy Lista przechowujaca wartosci wezlow drzewa.
     * @param ilosc_wierszy Dlugosc najdluzszej sciezki od korzenia drzewa do najdalszego liscia.
     */
    private void przejdzDrzewoIntInOrder(WezelDrzewa aktualny_wezel, int numer_wiersza, ArrayList<ArrayList<Integer>> wartosci_wierszy, int ilosc_wierszy) {
        if(aktualny_wezel == null) {
            // jezeli wezel nie istnieje, do listy wprowadzane sa wartosci NULL tak dlugo, az funkcja nie znajduje sie w ostatnim wierszu drzewa
            if(numer_wiersza < ilosc_wierszy) {
                wartosci_wierszy.get(numer_wiersza).add(null);
                numer_wiersza++;
                przejdzDrzewoIntInOrder(null, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
                przejdzDrzewoIntInOrder(null, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
            } else
                return;
        } else {
            wartosci_wierszy.get(numer_wiersza).add(aktualny_wezel.wartosc_int);
            numer_wiersza++;
            przejdzDrzewoIntInOrder(aktualny_wezel.lewy, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
            przejdzDrzewoIntInOrder(aktualny_wezel.prawy, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
        }
    }

    /**
     * Metoda odpowiedzialna za wprowadzenie wartosci zmiennoprzecinkowych wezlow drzewa do list. 
     * 
     * @param aktualny_wezel Wezel drzewa binarnego.
     * @param numer_wiersza Aktualna dlugosc sciezki od korzenia do aktualnego wezla.
     * @param wartosci_wierszy Lista przechowujaca wartosci wezlow drzewa.
     * @param ilosc_wierszy Dlugosc najdluzszej sciezki od korzenia drzewa do najdalszego liscia.
     */
    private void przejdzDrzewoDoubleInOrder(WezelDrzewa aktualny_wezel, int numer_wiersza, ArrayList<ArrayList<Double>> wartosci_wierszy, int ilosc_wierszy) {
        if(aktualny_wezel == null) {
            // jezeli wezel nie istnieje, do listy wprowadzane sa wartosci NULL tak dlugo, az funkcja nie znajduje sie w ostatnim wierszu drzewa
            if(numer_wiersza < ilosc_wierszy) {
                wartosci_wierszy.get(numer_wiersza).add(null);
                numer_wiersza++;
                przejdzDrzewoDoubleInOrder(null, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
                przejdzDrzewoDoubleInOrder(null, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
            } else
                return;
        } else {
            wartosci_wierszy.get(numer_wiersza).add(aktualny_wezel.wartosc_double);
            numer_wiersza++;
            przejdzDrzewoDoubleInOrder(aktualny_wezel.lewy, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
            przejdzDrzewoDoubleInOrder(aktualny_wezel.prawy, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
        }
    }

    /**
     * Metoda odpowiedzialna za wprowadzenie wartosci lancuchow znakow wezlow drzewa do list. 
     * 
     * @param aktualny_wezel Wezel drzewa binarnego.
     * @param numer_wiersza Aktualna dlugosc sciezki od korzenia do aktualnego wezla.
     * @param wartosci_wierszy Lista przechowujaca wartosci wezlow drzewa.
     * @param ilosc_wierszy Dlugosc najdluzszej sciezki od korzenia drzewa do liscia.
     */
    private void przejdzDrzewoStringInOrder(WezelDrzewa aktualny_wezel, int numer_wiersza, ArrayList<ArrayList<String>> wartosci_wierszy, int ilosc_wierszy) {
        if(aktualny_wezel == null) {
            // jezeli wezel nie istnieje, do listy wprowadzane sa wartosci NULL tak dlugo, az funkcja nie znajduje sie w ostatnim wierszu drzewa
            if(numer_wiersza < ilosc_wierszy) {
                wartosci_wierszy.get(numer_wiersza).add(null);
                numer_wiersza++;
                przejdzDrzewoStringInOrder(null, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
                przejdzDrzewoStringInOrder(null, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
            } else
                return;
        } else {
            wartosci_wierszy.get(numer_wiersza).add(aktualny_wezel.wartosc_string);
            numer_wiersza++;
            przejdzDrzewoStringInOrder(aktualny_wezel.lewy, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
            przejdzDrzewoStringInOrder(aktualny_wezel.prawy, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
        }
    }

    /**
     * Metoda ta odpowiedzialna jest za przekonwertowanie liczb calkowitych z listy do pojedynczego, sformatowanego napisu.
     * 
     * @param liczba_wierszy Dlugosc najdluzszej sciezki od korzenia drzewa do liscia.
     * @param wartosci_wierszy Lista przechowujaca wartosci wezlow drzewa.
     * @return Sformatowany napis zawierajacy wartosci wszystkich wezlow drzewa, w kolejnosci od lisci do korzenia.
     */
    private String wierszeIntNaNapis(int liczba_wierszy, ArrayList<ArrayList<Integer>> wartosci_wierszy) {
        String koncowy_napis = "";
        for(int i=liczba_wierszy - 1; i >= 0; i--) {
            for(int j=0; j < wartosci_wierszy.get(i).size(); j++) {
                if(wartosci_wierszy.get(i).get(j) == null)
                    koncowy_napis += "_ ";
                else
                    koncowy_napis += wartosci_wierszy.get(i).get(j);
                if(j != wartosci_wierszy.get(i).size() - 1)
                    koncowy_napis += " ";
            }
            // symbol, ktory bedzie symbolizowac, ze kolejne wartosci znajduja sie w wyzszym wierszu
            koncowy_napis += "#/#";
        }
        return koncowy_napis;
    }

    /**
     * Metoda ta odpowiedzialna jest za przekonwertowanie liczb zmiennoprzecinkowych z listy do pojedynczego, sformatowanego napisu.
     * 
     * @param liczba_wierszy Dlugosc najdluzszej sciezki od korzenia drzewa do liscia.
     * @param wartosci_wierszy Lista przechowujaca wartosci wezlow drzewa.
     * @return Sformatowany napis zawierajacy wartosci wszystkich wezlow drzewa, w kolejnosci od lisci do korzenia.
     */
    private String wierszeDoubleNaNapis(int liczba_wierszy, ArrayList<ArrayList<Double>> wartosci_wierszy) {
        String koncowy_napis = "";
        for(int i=liczba_wierszy - 1; i >= 0; i--) {
            for(int j=0; j < wartosci_wierszy.get(i).size(); j++) {
                if(wartosci_wierszy.get(i).get(j) == null)
                    koncowy_napis += "_ ";
                else
                    koncowy_napis += wartosci_wierszy.get(i).get(j);
                if(j != wartosci_wierszy.get(i).size() - 1)
                    koncowy_napis += " ";
            }
            // symbol, ktory bedzie symbolizowac, ze kolejne wartosci znajduja sie w wyzszym wierszu
            koncowy_napis += "#/#";
        }
        return koncowy_napis;
    }

    /**
     * Metoda ta odpowiedzialna jest za przekonwertowanie lancuchow znakowych z listy do pojedynczego, sformatowanego napisu.
     * 
     * @param liczba_wierszy Dlugosc najdluzszej sciezki od korzenia drzewa do liscia.
     * @param wartosci_wierszy Lista przechowujaca wartosci wezlow drzewa.
     * @return Sformatowany napis zawierajacy wartosci wszystkich wezlow drzewa, w kolejnosci od lisci do korzenia.
     */
    private String wierszeStringNaNapis(int liczba_wierszy, ArrayList<ArrayList<String>> wartosci_wierszy) {
        String koncowy_napis = "";
        for(int i=liczba_wierszy - 1; i >= 0; i--) {
            for(int j=0; j < wartosci_wierszy.get(i).size(); j++) {
                if(wartosci_wierszy.get(i).get(j) == null)
                    koncowy_napis += "_ ";
                else
                    koncowy_napis += wartosci_wierszy.get(i).get(j);
                if(j != wartosci_wierszy.get(i).size() - 1)
                    koncowy_napis += " ";
            }
            // symbol, ktory bedzie symbolizowac, ze kolejne wartosci znajduja sie w wyzszym wierszu
            koncowy_napis += "#/#";
        }
        return koncowy_napis;
    }

    /**
     * Metoda odpowiedzialna za przekazanie wezla do przeszukiwania drzewa binarnego.
     * 
     * @see DrzewoBinarne#szukajRightOrder
     * @param szukany_wezel Wezel zawierajacy pojedyncza wartosc, poszukiwana przez uzytkownika.
     * @return Wezel drzewa binarnego z poszukiwana wartoscia.
     */
    private WezelDrzewa szukajWezel(WezelDrzewa szukany_wezel) {
        if(this.korzen == null)
            return null;
        WezelDrzewa szukany_wezel_w_drzewie = szukajRightOrder(this.korzen, szukany_wezel, null);
        return szukany_wezel_w_drzewie;
    }

    /**
     * Metoda odpowiedzialna za przeszukanie drzewa binarnego w kolejnosci Post-Order, ale zaczynajac od prawej galezi.
     * 
     * @see DrzewoBinarne#czyWezelRowny
     * @param aktualny_wezel Aktualnie przeszukiwany wezel drzewa.
     * @param szukany_wezel Wezel zawierajacy poszukiwana wartosc.
     * @param znaleziony_wezel Wezel drzewa binarnego zawierajacy poszukiwana wartosc lub null.
     * @return Wezel drzewa binarnego z poszukiwana wartoscia lub null.
     */
    private WezelDrzewa szukajRightOrder(WezelDrzewa aktualny_wezel, WezelDrzewa szukany_wezel, WezelDrzewa znaleziony_wezel) {
        if(znaleziony_wezel != null)
            return znaleziony_wezel;
        if(aktualny_wezel != null) {
            znaleziony_wezel = szukajRightOrder(aktualny_wezel.prawy, szukany_wezel, znaleziony_wezel);
            if(znaleziony_wezel == null)
                znaleziony_wezel = szukajRightOrder(aktualny_wezel.lewy, szukany_wezel, znaleziony_wezel);
            if(znaleziony_wezel == null && czyWezelRowny(szukany_wezel, aktualny_wezel))
                znaleziony_wezel = aktualny_wezel;
        }
        return znaleziony_wezel;
    }

    /**
     * Metoda odpowiedzialna za usuniecie wartosci wybranej przez uzytkownika z drzewa binarnego.
     * Jesli po usunieciu wartosci wezel jest pusty, to jest on tez usuwany z drzewa binarnego.
     * 
     * @see DrzewoBinarne#szukajWezel
     * @see DrzewoBinarne#czyWezelPusty
     * @param wezel Wezel zawierajacy wartosc do usuniecia.
     * @return Czy usuniecie wartosci sie udalo? 
     * @throws NieprawidlowyWyborFunkcji Wezel z podana wartoscia nie znajduje sie w drzewie.
     */
    private boolean usunWezel(WezelDrzewa wezel) throws NieprawidlowyWyborFunkcji {
        WezelDrzewa szukany_wezel = szukajWezel(wezel);
        if(szukany_wezel == null) {
            throw new NieprawidlowyWyborFunkcji("BRAK_WEZLA");
        }
        boolean wynik_operacji = usunWartoscWezla(szukany_wezel, wezel);
        // sprawdzenie czy wezel jest pusty i nie ma pod soba innych wezlow
        if(szukany_wezel.lewy == null && szukany_wezel.prawy == null && czyWezelPusty(szukany_wezel)) {
            // sprawdzenie czy wezel nie jest korzeniem
            if(szukany_wezel.ojciec == null) {
                this.korzen = null;
                return true;
            } else {
                if(szukany_wezel.ojciec.prawy == szukany_wezel) {
                    szukany_wezel.ojciec.prawy = null;
                } else if(szukany_wezel.ojciec.lewy == szukany_wezel) {
                    szukany_wezel.ojciec.lewy = null;
                }
                szukany_wezel.ojciec = null;
                return true;
            }
        }
        return wynik_operacji;
    }

    /**
     * Metoda odpowiedzialna za usuniecie podanej wartosci z wybranego wezla drzewa binarnego.
     * 
     * @param wezel_w_drzewie Wezel drzewa binarnego z ktorego usuwana jest wartosc.
     * @param wezel_z_wartoscia Wezel zawierajacy pojedyncza wartosc do usuniecia.
     * @return Czy usuniecie wartosci sie powiodlo?
     */
    private boolean usunWartoscWezla(WezelDrzewa wezel_w_drzewie, WezelDrzewa wezel_z_wartoscia) {
        if(wezel_z_wartoscia.wartosc_int != null) {
            wezel_w_drzewie.wartosc_int = null;
            return true;
        } else if(wezel_z_wartoscia.wartosc_double != null) {
            wezel_w_drzewie.wartosc_double = null;
            return true;
        } else if(wezel_z_wartoscia.wartosc_string != null) {
            wezel_w_drzewie.wartosc_string = null;
            return true;
        }
        return false;
    }

    /**
     * Metoda odpowiedzialna za sprawdzenie, czy podany wezel drzewa binarnego ma jakakolwiek wartosc.
     * 
     * @param wezel Wezel drzewa binarnego.
     * @return Czy wezel nie ma zadnej wartosci?
     */
    private boolean czyWezelPusty(WezelDrzewa wezel) {
        if(wezel.wartosc_int == null && wezel.wartosc_double == null && wezel.wartosc_string == null) {
            return true;
        }
        return false;
    }
    
}
