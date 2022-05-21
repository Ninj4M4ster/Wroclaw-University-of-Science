import java.util.List;

import javafx.scene.*;
import javafx.application.Platform;
import javafx.application.Application;


/**
 * Klasa odpowiedzialna za kontrole dzialania aplikacji.
 */
class KontrolerAplikacji {
    // zmienne przechowujace glowne elementy GUI
    private Scene scena;
    private Group root;
    
    // parametry przekazane przez uzytkownika
    private List<String> parametry;
    private int ilosc_wierszy;
    private int ilosc_kolumn;
    private double szybkosc;
    private double prawdopodobienstwo;

    // torus przechowujacy watki pol
    private ListaDwukierunkowa lista_watkow;

    // zmienna przechwujaca kontroler watkow
    private KontrolerWatkow kontroler_watkow;

    /**
     * Konstruktor kontrolera, sprawdza czy podane argumenty sa poprawne i wprowadza je do pamieci.
     * 
     * @see ListaDwukierunkowa
     * @see KontrolerWatkow
     * @see KontrolerAplikacji#sprawdzArgumenty
     * @param parametry Parametry podane przez uzytkownika przy uruchamianiu.
     * @param scena Scena aplikacji.
     * @param root Korzen elementow aplikacji.
     */
    public KontrolerAplikacji(List<String> parametry, Scene scena, Group root, Application aplikacja) {
        this.scena = scena;
        this.root = root;
        this.parametry = parametry;

        // sprawdz czy podane parametry sa poprawne
        if(this.sprawdzArgumenty(parametry) == false) {
            try {
                aplikacja.stop();
                System.exit(1);
            } catch(Exception e) {
                System.out.println(e.getMessage());
            }
        }   

        // wprowadz parametry do zmiennych
        this.ilosc_wierszy = Integer.parseInt(parametry.get(0));
        this.ilosc_kolumn = Integer.parseInt(parametry.get(1));
        this.szybkosc = Double.parseDouble(parametry.get(2));
        this.prawdopodobienstwo = Double.parseDouble(parametry.get(3));
        
        lista_watkow = new ListaDwukierunkowa();

        kontroler_watkow = new KontrolerWatkow();
    }

    /**
     * Metoda ta sprawdza poprawnosc wprowadzonych argumentow i wyswietla odpowiednie komunikaty.
     * 
     * @param parametry Parametry podane przez uzytkownika przy uruchamianiu.
     * @return Czy parametry sa poprawne? Jesli nie, wystapil blad.
     */
    public boolean sprawdzArgumenty(List<String> parametry) {
        int wartosc1;
        double wartosc2;
        boolean wynik = true;
        if(parametry.size() != 4) {
            System.out.println("Aplikacja oczekuje dokladnie 4 argumenty.");
            wynik = false;
        }
        if(parametry.size() == 4) {
            try{
                wartosc1 = Integer.parseInt(parametry.get(0));
                if(wartosc1 <= 0) {
                    System.out.println("Ilosc wierszy musi byc wieksza od 0.");
                    wynik = false;
                }
            } catch(NumberFormatException e) {
                System.out.println("Ilosc wierszy nie moze byc znakiem.");
                wynik = false;
            }
            try {
                wartosc1 = Integer.parseInt(parametry.get(1));
                if(wartosc1 <= 0) {
                    System.out.println("Ilosc kolumn musi byc wieksza od 0.");
                    wynik = false;
                }
            } catch(NumberFormatException e) {
                System.out.println("Ilosc kolumn nie moze byc znakiem.");
                wynik = false;
            }
            try {
                wartosc2 = Double.parseDouble(parametry.get(2));
                if(wartosc2 <= 0) {
                    System.out.println("Szybkosc dzialania musi byc wieksza od 0.");
                    wynik = false;
                }
            } catch(NumberFormatException e) {
                System.out.println("Szybkosc dzialania nie moze byc znakiem.");
                wynik = false;
            }
            try {
                wartosc2 = Double.parseDouble(parametry.get(3));
                if(wartosc2 < 0) {
                    System.out.println("Prawdodopodbienstwo musi byc wieksze lub rowne 0.");
                    wynik = false;
                }
                else if(wartosc2 > 1) {
                    System.out.println("Prawdopodobienstwo nie moze byc wieksze od 1.");
                    wynik = false;
                }
            } catch(NumberFormatException e) {
                System.out.println("Prawdopodobienstwo nie moze byc znakiem.");
                wynik = false;
            }
        }
        return wynik;
    }

    /**
     * Funkcja odpowiedzialna za utworzenie pol aplikacji i dodanie ich do torusu.
     * 
     * @see PoleAplikacji
     */
    public void utworzPola() {
        for(int i=0; i < ilosc_wierszy; i++) {
            for(int j=0; j < ilosc_kolumn; j++) {
                PoleAplikacji pole = new PoleAplikacji(i, j, this.parametry, this.scena, this.kontroler_watkow);
                root.getChildren().add(pole);
                if(j == 0) 
                    lista_watkow.dodaj(pole, false);
                else
                    lista_watkow.dodaj(pole, true);
            }
        }
    }

    /**
     * Metoda odpowiedzialna za uruchomienie procesow wszystkich pol.
     * 
     * @see ListaDwukierunkowa#zwrocGlowe
     * @see ElementListy#podajWatek
     * @see ElementListy#nastepnyPoziomo
     * @see ElementListy#nastepnyPionowo
     * @see PoleAplikacji#start
     */
    public void uruchomPola() {
        ElementListy glowa = lista_watkow.zwrocGlowe();
        ElementListy zmienna_pomocnicza_pionowa = glowa;
        do {
            ElementListy zmienna_pomocnicza_pozioma = zmienna_pomocnicza_pionowa;
            do {
                zmienna_pomocnicza_pozioma.podajWatek().start();
                zmienna_pomocnicza_pozioma = zmienna_pomocnicza_pozioma.nastepnyPoziomo();
            } while(zmienna_pomocnicza_pozioma != zmienna_pomocnicza_pionowa);
            zmienna_pomocnicza_pionowa = zmienna_pomocnicza_pionowa.nastepnyPionowo();
        } while(zmienna_pomocnicza_pionowa != glowa);
    }

    /**
     * Metoda odpowiedzialna za zatrzymanie wszystkich watkow.
     * 
     * @see ListaDwukierunkowa#zwrocGlowe
     * @see ElementListy#podajWatek
     * @see ElementListy#nastepnyPoziomo
     * @see ElementListy#nastepnyPionowo
     */
    public void zatrzymajWatki() {
        ElementListy glowa = lista_watkow.zwrocGlowe();
        ElementListy zmienna_pomocnicza_pionowa = glowa;
        do {
            ElementListy zmienna_pomocnicza_pozioma = zmienna_pomocnicza_pionowa;
            do {
                zmienna_pomocnicza_pozioma.podajWatek().zatrzymaj();
                zmienna_pomocnicza_pozioma = zmienna_pomocnicza_pozioma.nastepnyPoziomo();
            } while(zmienna_pomocnicza_pozioma != zmienna_pomocnicza_pionowa);
            zmienna_pomocnicza_pionowa = zmienna_pomocnicza_pionowa.nastepnyPionowo();
        } while(zmienna_pomocnicza_pionowa != glowa);
    }


}
