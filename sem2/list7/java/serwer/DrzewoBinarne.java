import java.util.ArrayList;

/**
 * Klasa implementujaca drzewo binarne.
 * Obsluguje dodawanie wezla, usuwanie wartosci lub wezla, 
 * wyszukiwanie wezla i wyswietlanie calego drzewa.
 */
class DrzewoBinarne {
    /**Korzen drzewa binarnego. */
    private WezelDrzewa<?> korzen_int = null;
    private WezelDrzewa<?> korzen_double = null;
    private WezelDrzewa<?> korzen_string = null;

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
    public boolean przekazWartosc(int wartosc, int wybor_funkcji) throws NieprawidlowyWyborFunkcji, NieprawidlowaWartosc {
        WezelDrzewa<Integer> wezel = new WezelDrzewa<Integer>();
        wezel.wartosc = wartosc;
        return wybierzFunkcje(wezel, wybor_funkcji, DRZEWO_INT);
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
    public boolean przekazWartosc(double wartosc, int wybor_funkcji) throws NieprawidlowyWyborFunkcji,NieprawidlowaWartosc {
        WezelDrzewa<Double> wezel = new WezelDrzewa<Double>();
        wezel.wartosc = wartosc;
        return wybierzFunkcje(wezel, wybor_funkcji, DRZEWO_DOUBLE);
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
    public boolean przekazWartosc(String wartosc, int wybor_funkcji) throws NieprawidlowyWyborFunkcji, NieprawidlowaWartosc {
        WezelDrzewa<String> wezel = new WezelDrzewa<String>();
        wezel.wartosc = wartosc;
        return wybierzFunkcje(wezel, wybor_funkcji, DRZEWO_STRING);
    }

    /**
     * Metoda ta odpowiedzialna jest za wykonanie dzialania na drzewie, przekazujac utworzony wczesniej wezel.
     * 
     * @see DrzewoBinarne#wstawWezel
     * @see DrzewoBinarne#usunWezel
     * @see DrzewoBinarne#szukajWezel
     * @param nowy_wezel Poprzednio utworzony wezel zawierajacy pojedyncza wartosc.
     * @param wybor_funkcji Funkcja wybrana przez uzytkownika.
     * @param typ_danych Typ danych wprowadzonych przez klienta.
     * @return Czy dzialanie funkcji sie powiodlo?
     * @throws NieprawidlowyWyborFunkcji Wybrano nieprawidlowa funkcje.
     * @throws NieprawidlowaWartosc Przekazano do funkcji nieprawidlowa wartosc.
     */
    private boolean wybierzFunkcje(WezelDrzewa<?> nowy_wezel, int wybor_funkcji, int typ_danych) throws NieprawidlowyWyborFunkcji, NieprawidlowaWartosc {
        switch(wybor_funkcji) {
            case DODAWANIE_WEZLA: {
                return this.wstawWezel(nowy_wezel, typ_danych);
            } case USUWANIE_WEZLA: {
                return this.usunWezel(nowy_wezel, typ_danych);
            } case SZUKANIE_WEZLA: {
                WezelDrzewa<?> szukany_wezel = this.szukajWezel(nowy_wezel, typ_danych);
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
     * @see DrzewoBinarne#czyWezelMniejszy
     * @param nowy_wezel Poprzednio utworzony wezel zawierajacy pojedyncza wartosc.
     * @param typ_danych Typ danych wprowadzonych przez klienta.
     * @return Czy dodanie nowego wezla sie powidodlo?
     */
    private boolean wstawWezel(WezelDrzewa<? extends Object> nowy_wezel, int typ_danych) {
        // sprawdzenie korzenia odpowiadajacego danemu typowi
        if(typ_danych == 0 && this.korzen_int == null) {
            this.korzen_int = new WezelDrzewa<Integer>(nowy_wezel);
            return true;
        } else if(typ_danych == 1 && this.korzen_double == null) {
            this.korzen_double = new WezelDrzewa<Double>(nowy_wezel);
            return true;
        } else if(typ_danych == 2 && this.korzen_string == null) {
            this.korzen_string = new WezelDrzewa<String>(nowy_wezel);
            return true;
        }

        // wybor korzenia na podstawie typu danych
        WezelDrzewa<? extends Object> wezel_tymczasowy;
        if(typ_danych == 0)
            wezel_tymczasowy = this.korzen_int;
        else if(typ_danych == 1)
            wezel_tymczasowy = this.korzen_double;
        else
            wezel_tymczasowy = this.korzen_string;

        while(true) {
            if(czyWezelMniejszy(nowy_wezel, wezel_tymczasowy, typ_danych)) {
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
     * Metoda ta odpowiedzialna jest za okreslenie, czy nowy wezel ma wartosci mniejsze 
     * niz podany wezel znajdujacy sie w drzewie binarnym.
     * 
     * @param nowy_wezel Poprzednio utworzony wezel zawierajacy pojedyncza wartosc.
     * @param wezel_w_drzewie Wezel znajdujacy sie w drzewie binarnym.
     * @param typ_danych Typ danych wprowadzonych przez klienta.
     * @return Czy wartosc w nowym wezle jest mniejsza od wartosci w wezle znajdujacym sie w drzewie binarnym?
     */
    private boolean czyWezelMniejszy(WezelDrzewa<?> nowy_wezel, WezelDrzewa<?> wezel_w_drzewie, int typ_danych) {
        if(nowy_wezel.wartosc != null) {
            if(typ_danych == 0)
            return Integer.compare((Integer)nowy_wezel.wartosc, (Integer)wezel_w_drzewie.wartosc) < 0 ? true : false;
            else if(typ_danych == 1)
                return Double.compare((Double)nowy_wezel.wartosc, (Double)wezel_w_drzewie.wartosc) < 0 ? true : false;
            else
                return ((String)nowy_wezel.wartosc).compareTo((String)wezel_w_drzewie.wartosc) < 0 ? true : false;
        }
        return false;
    }

    /**
     * Metoda ta odpowiedzialna jest za okreslenie, czy wartosc w nowym wezle jest rowna wartosci
     * znajdujacej sie w wezle drzewa binarnego.
     * 
     * @param nowy_wezel Poprzednio utworzony wezel zawierajacy pojedyncza wartosc.
     * @param wezel_w_drzewie Wezel znajdujacy sie w drzewie binarnym.
     * @param typ_danych Typ dancyh wprowadzonych przez klienta.
     * @return Czy wartosc nowego wezla jest rowna wartosci znajdujacej sie w wezle drzewa binarnego?
     */
    private boolean czyWezelRowny(WezelDrzewa<?> nowy_wezel, WezelDrzewa<?> wezel_w_drzewie, int typ_danych) {
        if(nowy_wezel.wartosc != null && wezel_w_drzewie.wartosc != null) {
            if(typ_danych == 0)
                return Integer.compare((Integer)nowy_wezel.wartosc, (Integer)wezel_w_drzewie.wartosc) == 0 ? true : false;
            else if(typ_danych == 1)
                return Double.compare((Double)nowy_wezel.wartosc, (Double)wezel_w_drzewie.wartosc) == 0 ? true : false;
            else 
                return ((String)nowy_wezel.wartosc).compareTo((String)wezel_w_drzewie.wartosc) == 0 ? true : false;
        }
        return false;
    }


    /**
     * Metoda ta odpowiedzialna jest za zapisanie wartosci wezlow drzewa w wiersze i utworzenie napisu,
     * ktory nastepnie zostanie wyslany do klienta.
     * 
     * @see DrzewoBinarne#obliczIloscWierszy
     * @see DrzewoBinarne#przejdzDrzewoInOrder
     * @see DrzewoBinarne#wierszeNaNapis
     * @param typ_drzewa Typ danych w drzewie.
     * @return Sformatowany napis zawierajacy wartosci drzewa binarnego.
     * @throws NieprawidlowaWartosc Podano zly typ drzewa.
     * @throws NieprawidlowyWyborFunkcji Korzen drzewa jest pusty.
     */
    public String wyswietl(int typ_drzewa) throws NieprawidlowyWyborFunkcji, NieprawidlowaWartosc {
        if(typ_drzewa == 0 && this.korzen_int == null ||
          typ_drzewa == 1 && this.korzen_double == null ||
          typ_drzewa == 2 && this.korzen_string == null)
            throw new NieprawidlowyWyborFunkcji("EMPTY_TREE");
        int numer_wiersza = 0;
        int ilosc_wierszy;

        // wprowadzenie wierszy do listy oraz wyswietlenie jej jest zalezne od wybranego typu drzewa
        switch(typ_drzewa) {
            case DRZEWO_INT: {
                ilosc_wierszy = obliczIloscWierszy(this.korzen_int, numer_wiersza);
                ArrayList<ArrayList<Object>> wartosci_wierszy = new ArrayList<>(ilosc_wierszy);
                for(int i=0; i < ilosc_wierszy; i++)
                    wartosci_wierszy.add(new ArrayList<>());
                przejdzDrzewoInOrder(this.korzen_int, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
                return wierszeNaNapis(ilosc_wierszy, wartosci_wierszy);
            } case DRZEWO_DOUBLE: {
                ilosc_wierszy = obliczIloscWierszy(this.korzen_double, numer_wiersza);
                ArrayList<ArrayList<Object>> wartosci_wierszy = new ArrayList<>(ilosc_wierszy);
                for(int i=0; i < ilosc_wierszy; i++)
                    wartosci_wierszy.add(new ArrayList<>());
                przejdzDrzewoInOrder(this.korzen_double, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
                return wierszeNaNapis(ilosc_wierszy, wartosci_wierszy);
            } case DRZEWO_STRING: {
                ilosc_wierszy = obliczIloscWierszy(this.korzen_string, numer_wiersza);
                ArrayList<ArrayList<Object>> wartosci_wierszy = new ArrayList<>(ilosc_wierszy);
                for(int i=0; i < ilosc_wierszy; i++)
                    wartosci_wierszy.add(new ArrayList<>());
                przejdzDrzewoInOrder(this.korzen_string, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
                return wierszeNaNapis(ilosc_wierszy, wartosci_wierszy);
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
    private int obliczIloscWierszy(WezelDrzewa<?> aktualny_wezel, int numer_wiersza) {
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
    private void przejdzDrzewoInOrder(WezelDrzewa<? extends Object> aktualny_wezel, int numer_wiersza, ArrayList<ArrayList<Object>> wartosci_wierszy, int ilosc_wierszy) {
        if(aktualny_wezel == null) {
            // jezeli wezel nie istnieje, do listy wprowadzane sa wartosci NULL tak dlugo, az funkcja nie znajduje sie w ostatnim wierszu drzewa
            if(numer_wiersza < ilosc_wierszy) {
                wartosci_wierszy.get(numer_wiersza).add(null);
                numer_wiersza++;
                przejdzDrzewoInOrder(null, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
                przejdzDrzewoInOrder(null, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
            } else
                return;
        } else {
            wartosci_wierszy.get(numer_wiersza).add((Object)aktualny_wezel.wartosc);
            numer_wiersza++;
            przejdzDrzewoInOrder(aktualny_wezel.lewy, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
            przejdzDrzewoInOrder(aktualny_wezel.prawy, numer_wiersza, wartosci_wierszy, ilosc_wierszy);
        }
    }

    /**
     * Metoda ta odpowiedzialna jest za przekonwertowanie liczb calkowitych z listy do pojedynczego, sformatowanego napisu.
     * 
     * @param liczba_wierszy Dlugosc najdluzszej sciezki od korzenia drzewa do liscia.
     * @param wartosci_wierszy Lista przechowujaca wartosci wezlow drzewa.
     * @return Sformatowany napis zawierajacy wartosci wszystkich wezlow drzewa, w kolejnosci od lisci do korzenia.
     */
    private String wierszeNaNapis(int liczba_wierszy, ArrayList<ArrayList<Object>> wartosci_wierszy) {
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
     * @param typ_drzewa Typ danych wprowadzonych przez klienta.
     * @return Wezel drzewa binarnego z poszukiwana wartoscia.
     * @throws NieprawidlowaWartosc Blad przy wybraniu zlego typu drzewa.
     */
    private WezelDrzewa<?> szukajWezel(WezelDrzewa<?> szukany_wezel, int typ_drzewa) throws NieprawidlowaWartosc {
        if(typ_drzewa == 0 && this.korzen_int == null)
            return null;
        else if(typ_drzewa == 1 && this.korzen_double == null)
            return null;
        else if(typ_drzewa == 2 && this.korzen_string == null)
            return null;
        
        switch(typ_drzewa) {
            case DRZEWO_INT: {
                WezelDrzewa<?> szukany_wezel_w_drzewie = szukajRightOrder(this.korzen_int, szukany_wezel, null, typ_drzewa);
                return szukany_wezel_w_drzewie;
            } case DRZEWO_DOUBLE: {
                WezelDrzewa<?> szukany_wezel_w_drzewie = szukajRightOrder(this.korzen_double, szukany_wezel, null, typ_drzewa);
                return szukany_wezel_w_drzewie;
            } case DRZEWO_STRING: {
                WezelDrzewa<?> szukany_wezel_w_drzewie = szukajRightOrder(this.korzen_string, szukany_wezel, null, typ_drzewa);
                return szukany_wezel_w_drzewie;
            } default:
                throw new NieprawidlowaWartosc("WRONG_TYPE");
        } 
    }

    /**
     * Metoda odpowiedzialna za przeszukanie drzewa binarnego w kolejnosci Post-Order, ale zaczynajac od prawej galezi.
     * 
     * @see DrzewoBinarne#czyWezelRowny
     * @param aktualny_wezel Aktualnie przeszukiwany wezel drzewa.
     * @param szukany_wezel Wezel zawierajacy poszukiwana wartosc.
     * @param znaleziony_wezel Wezel drzewa binarnego zawierajacy poszukiwana wartosc lub null.
     * @param typ_drzewa Typ danych wprowadzonych przez klienta.
     * @return Wezel drzewa binarnego z poszukiwana wartoscia lub null.
     */
    private WezelDrzewa<?> szukajRightOrder(WezelDrzewa<?> aktualny_wezel, WezelDrzewa<?> szukany_wezel, WezelDrzewa<?> znaleziony_wezel, int typ_drzewa) {
        if(znaleziony_wezel != null)
            return znaleziony_wezel;
        if(aktualny_wezel != null) {
            znaleziony_wezel = szukajRightOrder(aktualny_wezel.prawy, szukany_wezel, znaleziony_wezel, typ_drzewa);
            if(znaleziony_wezel == null)
                znaleziony_wezel = szukajRightOrder(aktualny_wezel.lewy, szukany_wezel, znaleziony_wezel, typ_drzewa);
            if(znaleziony_wezel == null && czyWezelRowny(szukany_wezel, aktualny_wezel, typ_drzewa))
                znaleziony_wezel = aktualny_wezel;
        }
        return znaleziony_wezel;
    }

    /**
     * Metoda odpowiedzialna za usuniecie wezla z wartoscia wybrana przez uzytkownika z drzewa binarnego.
     * 
     * @see DrzewoBinarne#szukajWezel
     * @see DrzewoBinarne#znajdzMinGalezi
     * @see DrzewoBinarne#znajdzMaxGalezi
     * @see DrzewoBinarne#zamienKorzen
     * @see DrzewoBinarne#oderwijNastepce
     * @param wezel Wezel zawierajacy wartosc do usuniecia.
     * @param typ_drzewa Typ danych wprowadzonych przez klienta.
     * @return Czy usuniecie wartosci sie udalo? 
     * @throws NieprawidlowyWyborFunkcji Wezel z podana wartoscia nie znajduje sie w drzewie.
     * @throws NieprawidlowaWartosc Blad przy wybraniu zlego typu drzewa.
     */
    private boolean usunWezel(WezelDrzewa<?> wezel, int typ_drzewa) throws NieprawidlowyWyborFunkcji, NieprawidlowaWartosc {
        WezelDrzewa<?> szukany_wezel;
        WezelDrzewa<?> nastepca = null;
        szukany_wezel = szukajWezel(wezel, typ_drzewa);
        // nie znaleziono wezla z podana wartoscia
        if(szukany_wezel == null) {
            throw new NieprawidlowyWyborFunkcji("BRAK_WEZLA");
        }
        // szukamy w prawej galezi min, a jesli jej nie ma to w lewej max
        if(szukany_wezel.prawy != null) {
            nastepca = znajdzMinGalezi(szukany_wezel.prawy, typ_drzewa);
        } else if(szukany_wezel.lewy != null) {
            nastepca = znajdzMaxGalezi(szukany_wezel.lewy, typ_drzewa);
        }
        // nie ma prawej ani lewej galezi, sprawdzamy czy to nie korzen i usuwamy
        else {
            if(szukany_wezel.ojciec == null) {
                // jest to korzen, wiec go zamieniamy na null
                zamienKorzen(null, typ_drzewa);
            } else {
                if(szukany_wezel.ojciec.lewy == szukany_wezel) {
                    szukany_wezel.ojciec.lewy = null;
                    szukany_wezel.ojciec = null;
                } else {
                    szukany_wezel.ojciec.prawy = null;
                    szukany_wezel.ojciec = null;
                }
            }
            return true;
        }
        if(nastepca != null) {
            // laczymy ojca i lisc nastepcy
            oderwijNastepce(nastepca);
            
            // zamieniamy wybrany do usuniecia wezel na nastepce
            nastepca.lewy = szukany_wezel.lewy;
            nastepca.prawy = szukany_wezel.prawy;
            nastepca.ojciec = szukany_wezel.ojciec;
            
            if(szukany_wezel.lewy != null) {
                szukany_wezel.lewy.ojciec = nastepca;
            }
            if(szukany_wezel.prawy != null) {
                szukany_wezel.prawy.ojciec = nastepca;
            }
            if(szukany_wezel.ojciec != null) {
                if(szukany_wezel.ojciec.prawy == szukany_wezel)
                    szukany_wezel.ojciec.prawy = nastepca;
                else
                    szukany_wezel.ojciec.lewy = nastepca;
            } else {
                // jesli ojciec jest null to trzeba zamienic korzen
                zamienKorzen(nastepca, typ_drzewa);
            }

            // usuwamy wybrany wezel
            szukany_wezel.ojciec = null;
            szukany_wezel.prawy = null;
            szukany_wezel.lewy = null;

            return true;
        }
        return false;
    }

    /**
     * Metoda odpowiedzialna za znalezienie najmniejszej wartosci w drzewie wybranego typu.
     * 
     * @param aktualny_wezel Wezel drzewa binarnego.
     * @param typ_drzewa Typ danych wprowadzonych przez klienta.
     * @return Wezel z najmniejsza wartoscia w drzewie.
     */
    private WezelDrzewa<?> znajdzMinGalezi(WezelDrzewa<?> aktualny_wezel, int typ_drzewa) {
        if(aktualny_wezel != null) {
            if(aktualny_wezel.lewy == null && aktualny_wezel.prawy == null)
                return aktualny_wezel;
            WezelDrzewa<?> min_lewo = znajdzMinGalezi(aktualny_wezel.lewy, typ_drzewa);
            WezelDrzewa<?> min_prawo = znajdzMinGalezi(aktualny_wezel.prawy, typ_drzewa);
            if(min_lewo == null) {
                if(czyWezelMniejszy(aktualny_wezel, min_prawo, typ_drzewa))
                    return aktualny_wezel;
                else
                    return min_prawo;
            } else if(min_prawo == null) {
                return min_lewo;
            } else {
                if(!czyWezelMniejszy(min_lewo, min_prawo, typ_drzewa))
                    min_lewo = min_prawo;
                return min_lewo;
            }
        }
        return aktualny_wezel;
    }

    /**
     * Metoda odpowiedzialna za znalezienie najwiekszej wartosci w drzewie wybranego typu.
     * 
     * @param aktualny_wezel Wezel drzewa binarnego.
     * @param typ_drzewa Typ danych wprowadzonych przez klienta.
     * @return Wezel z najwieksza wartoscia w drzewie.
     */
    private WezelDrzewa<?> znajdzMaxGalezi(WezelDrzewa<?> aktualny_wezel, int typ_drzewa) {
        if(aktualny_wezel != null) {
            if(aktualny_wezel.lewy == null && aktualny_wezel.prawy == null)
                return aktualny_wezel;
            WezelDrzewa<?> max_lewo = znajdzMaxGalezi(aktualny_wezel.lewy, typ_drzewa);
            WezelDrzewa<?> max_prawo = znajdzMaxGalezi(aktualny_wezel.prawy, typ_drzewa);
            if(max_prawo == null) {
                if(!czyWezelMniejszy(aktualny_wezel, max_lewo, typ_drzewa)) 
                    return aktualny_wezel;
                else
                    return max_lewo;
            } else if(max_lewo == null)
                return max_prawo;
            else {
                if(czyWezelMniejszy(max_prawo, max_lewo, typ_drzewa) || czyWezelRowny(max_lewo, max_prawo, typ_drzewa))
                    max_prawo = max_lewo;
                return max_prawo;
            }
        }
        return aktualny_wezel;
    }

    /**
     * Metoda odpowiedzialna za rozlaczenie wezla ze znaleziona wartoscia najmniejsza lub najwieksza od drzewa 
     * oraz polaczenie galezi wychodzacych od tego wezla.
     * 
     * @param wezel Wezel drzewa binarnego o wartosci najmniejszej lub najwiekszej.
     */
    private void oderwijNastepce(WezelDrzewa<?> wezel) {
        if(wezel.lewy == null && wezel.prawy == null) {
            if(wezel.ojciec.lewy == wezel) {
                wezel.ojciec.lewy = null;
            } else {
                wezel.ojciec.prawy = null;
            }
        } else if(wezel.lewy != null) {
            wezel.lewy.ojciec = wezel.ojciec;
            if(wezel.ojciec.lewy == wezel)
                wezel.ojciec.lewy = wezel.lewy;
            else 
                wezel.ojciec.prawy = wezel.lewy;
        } else {
            wezel.prawy.ojciec = wezel.ojciec;
            if(wezel.ojciec.lewy == wezel)
                wezel.ojciec.lewy = wezel.prawy;
            else
                wezel.ojciec.prawy = wezel.prawy;
        }
    }

    /**
     * Metoda odpowiedzialna za podmienienie korzenia drzewa wybranego typu.
     * 
     * @param nowy_korzen Wezel drzewa binarnego majacy zastapic korzen.
     * @param typ_drzewa Typ danych wprowadzonych przez klienta.
     */
    private void zamienKorzen(WezelDrzewa<?> nowy_korzen, int typ_drzewa) {
        switch(typ_drzewa) {
            case DRZEWO_INT: {
                this.korzen_int = nowy_korzen;
                return;
            } case DRZEWO_DOUBLE: {
                this.korzen_double = nowy_korzen;
                return;
            } case DRZEWO_STRING: {
                this.korzen_string = nowy_korzen;
                return;
            }
        }
    }
    
}
