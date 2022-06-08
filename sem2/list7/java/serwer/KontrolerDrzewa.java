/**
 * Klasa kontrolera drzewa binarnego. Odpowiedzialna jest za przyjmowanie danych od watkow oraz operacje na drzewie binarnym.
 */
class KontrolerDrzewa {
    private final DrzewoBinarne drzewo;

    // zmienne okreslajace typ drzewa
    private final int DRZEWO_INT = 0;
    private final int DRZEWO_DOUBLE = 1;
    private final int DRZEWO_STRING = 2;

    /**
     * Konstruktor, tworzy nowe drzewo binarne.
     */
    public KontrolerDrzewa() {
        this.drzewo = new DrzewoBinarne();
    }

    /**
     * Metoda ta przyjmuje polecenie od klienta, ktore nastepnie przekazuje do odpowiedniej funkcji.
     * 
     * @param wiadomosc Polecenie wyslane przez klienta.
     * @return Status wykonanego polecenia lub sformatowany napis zawierajacy wszystkie wartosci w okreslonym typie drzewa.
     */
    public String przekazSformatowanyNapis(String wiadomosc) {
        String[] rozdzielone_napisy = wiadomosc.split(" ");
        int typ_drzewa = Integer.parseInt(rozdzielone_napisy[0]);
        int polecenie = Integer.parseInt(rozdzielone_napisy[1]);
        // dodawanie, usuwanie lub szukanie wezla
        if(polecenie >= 0 && polecenie <= 2) {
            String wartosc = rozdzielone_napisy[2];
            return this.przekazWartoscDoDrzewa(wartosc, typ_drzewa, polecenie);
        } else if(polecenie == 3) {
            return this.wyswietlDrzewo(typ_drzewa);
        } else {
            return "BLAD";
        }
    }

    /**
     * Metoda ta sprawdza poprawnosc wprowadzonych danych przez klienta i przekazuje je do drzewa binarnego.
     * 
     * @param wartosc Wartosc wezla podana przez klienta.
     * @param typ_drzewa Typ danych drzewa wybrany przez klienta.
     * @param polecenie Polecenie wybrane przez klienta.
     * @return Lancuch znakow okreslajacy status wykonanego polecenia.
     */
    private String przekazWartoscDoDrzewa(String wartosc, int typ_drzewa, int polecenie) {
        try {
            switch(typ_drzewa) {
                case DRZEWO_INT: {
                    try {
                        int wartosc_int = Integer.parseInt(wartosc);
                        boolean wynik;
                        synchronized(this.drzewo) {
                            wynik = this.drzewo.przekazWartosc(wartosc_int, polecenie);
                        }
                        if(wynik)
                                return "POWODZENIE";
                            else 
                                return "BLAD";
                    } catch(NumberFormatException blad) {
                        return "NIEPRAWIDLOWY_FORMAT";
                    }
                } case DRZEWO_DOUBLE: {
                    try {
                        double wartosc_double = Double.parseDouble(wartosc);
                        boolean wynik;
                        synchronized(this.drzewo) {
                            wynik = this.drzewo.przekazWartosc(wartosc_double, polecenie);
                        }
                        if(wynik)
                            return "POWODZENIE";
                        else
                            return "BLAD";
                    } catch(NumberFormatException blad) {
                        return "NIEPRAWIDLOWY_FORMAT";
                    }
                } case DRZEWO_STRING: {
                    boolean wynik;
                    wartosc = wartosc.trim();
                    // wartosc nie moze zawierac niektorych znakow potrzebnych potem do interpretowania napisu sluzacego do wyswietlania drzewa
                    if(wartosc.contains("#/#") || wartosc.contains(" "))
                        return "NIEPRAWIDLOWY_FORMAT";
                    synchronized(this.drzewo) {
                        wynik = this.drzewo.przekazWartosc(wartosc, polecenie);
                    }
                    if(wynik)
                        return "POWODZENIE";
                    else
                        return "BLAD";
                } default:
                    return "NIEPRAWIDLOWY_FORMAT";
            }
        } catch(NieprawidlowyWyborFunkcji blad) {
            return blad.getMessage();
        }
    }

    /**
     * Metoda ta przekazuje typ do drzewa binarnego w celu otrzymania napisu sluzacego do wyswietlenia drzewa.
     * Format napisu: wartosci wierszy oddzielone sa spacjami; jesli wartosc wezla to null, to napis bedzie zawierac "_"; wiersze oddzielone sa znakami "#/#".
     * 
     * @param typ_drzewa Typ danych drzewa wybrany przez klienta.
     * @return Sformatowany napis zawierajacy wszystkie wartosci drzewa binarnego.
     */
    private String wyswietlDrzewo(int typ_drzewa) {
        try {
            synchronized(this.drzewo) {
                return this.drzewo.wyswietl(typ_drzewa);
            }
        } catch(NieprawidlowyWyborFunkcji blad) {
            return blad.getMessage();
        } catch(NieprawidlowaWartosc blad) {
            return blad.getMessage();
        }
    }

}
