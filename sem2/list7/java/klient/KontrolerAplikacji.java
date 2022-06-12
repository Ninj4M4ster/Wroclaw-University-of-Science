import java.io.*;
import java.net.*;
import java.time.LocalTime;

import javafx.collections.*;
import javafx.scene.*;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.scene.input.*;
import javafx.scene.transform.*;

/**
 * Klasa odpowiedzialna za dzialanie aplikacji. Uruchamia ona odpowiednie watki w tle
 */
class KontrolerAplikacji {

    // kontroler wygladu aplikacji
    private WygladAplikacji kontroler_wygladu;

    // zmienne pomocnicze watkow
    private boolean aplikacja_aktywna;

    // przyciski do kontroli drzewa
    private ChoiceBox<String> przycisk_wyboru_typu;
    private Button przycisk_dodania_wezla;
    private Button przycisk_usuniecia_wezla;
    private Button przycisk_wyszukania_wezla;
    private Button przycisk_odnowienia_polaczenia;

    // kontener drzewa
    private Pane przestrzen_drzewa;

    // polaczenia z serwerem
    private Socket polaczenie = null;
    private BufferedReader wczyt = null;
    private PrintWriter przekaz = null;

    // zmienna przechowujaca sformatowany napis aktualnego drzewa
    private String aktualne_drzewo = null;

    // zmienne pomocnicze sluzace do przesuwania przestrzeni drzewa
    private double pozycja_myszki_x;
    private double pozycja_myszki_y;
    private double aktualna_delta_x;
    private double aktualna_delta_y;
    private double aktualna_skala;

    /**
     * Konstruktor, kontroluje wydarzenia w aplikacji oraz przypisuje funkcje odpowiednim przyciskom.
     * 
     * @param kontroler_wygladu Kontroler wygladu aplikacji.
     */
    public KontrolerAplikacji(WygladAplikacji kontroler_wygladu) {
        this.kontroler_wygladu = kontroler_wygladu;
        this.aplikacja_aktywna = true;

        // przekazanie pol i przyciskow aplikacji do kontrolera
        this.przycisk_wyboru_typu = kontroler_wygladu.przekazPrzyciskWyboruTypu();
        this.przycisk_dodania_wezla = kontroler_wygladu.przekazPrzyciskDodawania();
        this.przycisk_usuniecia_wezla = kontroler_wygladu.przekazPrzyciskUsuwania();
        this.przycisk_wyszukania_wezla = kontroler_wygladu.przekazPrzyciskSzukania();
        this.przycisk_odnowienia_polaczenia = kontroler_wygladu.przekazPrzyciskOdnowieniaPolaczenia();
        this.przestrzen_drzewa = kontroler_wygladu.przekazPrzestrzenDrzewa();

        this.bindujPrzyciski();
        
        // w trakcie uruchamiania aplikacji podejmij probe polaczenia z aplikacja
        this.sprobujPolaczycSerwer();
    }

    /**
     * Metoda odpowiedzialna za przypisanie funkcji do wydarzen w GUI.
     */
    private void bindujPrzyciski() {
        // przypisanie funkcji przyciskom
        this.przycisk_dodania_wezla.setOnAction(e -> {dodajNowyWezel();});
        this.przycisk_usuniecia_wezla.setOnAction(e -> {usunWezel();});
        this.przycisk_wyszukania_wezla.setOnAction(e -> {znajdzWezel();});
        this.przycisk_odnowienia_polaczenia.setOnAction(e -> {sprobujPolaczycSerwer();});

        // przypisanie funkcji do wydarzen na przestrzeni drzewa
        this.przestrzen_drzewa.setOnMousePressed(e -> {nacisnietoNaPrzestrzenDrzewa(e);});
        this.przestrzen_drzewa.setOnMouseDragged(e -> {przeciagnietoPrzestrzenDrzewa(e);});
    }

    /**
     * Metoda wywolujaca dialog utworzenia nowego wezla i uruchamiajaca watek komunikujacy sie z serwerem.
     */
    private void dodajNowyWezel() {
        String wartosc = DialogDodania.uruchomDialog();
        if(wartosc == null || wartosc.isEmpty())
            return;
        String typ = this.zwrocTypDrzewa();
        String polecenie = typ + " 0 " + wartosc;

        Thread watek = new Thread(new ProcesKomunikacji(polecenie));
        watek.setDaemon(true);
        watek.start();
    }

    /**
     * Metoda wywolujaca dialog usuniecia wezla z drzewa i uruchamiajaca watek komunikujacy sie z serwerem.
     */
    private void usunWezel() {
        String wartosc = DialogUsuniecia.uruchomDialog();
        if(wartosc == null || wartosc.isEmpty()) 
            return;
        String typ = this.zwrocTypDrzewa();
        String polecenie = typ + " 1 " + wartosc;

        Thread watek = new Thread(new ProcesKomunikacji(polecenie));
        watek.setDaemon(true);
        watek.start();
    }

    /**
     * Metoda wywolujaca dialog wyszukania wezla i uruchamiajaca watek komunikujacy sie z drzewem.
     */
    private void znajdzWezel() {
        String wartosc = DialogWyszukania.uruchomDialog();
        if(wartosc == null || wartosc.isEmpty())
            return;
        String typ = this.zwrocTypDrzewa();
        String polecenie = typ + " 2 " + wartosc;

        Thread watek = new Thread(new ProcesKomunikacji(polecenie));
        watek.setDaemon(true);
        watek.start();
    }

    /**
     * Metoda odpowiedzialna za okreslenie aktualnie wybranego typu danych przez klienta.
     * 
     * @return Napis okreslajacy typ danych w drzewie.
     */
    protected synchronized String zwrocTypDrzewa() {
        String typ = this.przycisk_wyboru_typu.getValue().split(" ")[1];
        if(typ.equals("int"))
            return "0";
        else if(typ.equals("double"))
            return "1";
        else
            return "2";
    }

    /**
     * Wydarzenie wywolywane w przypadku nacisniecia na kontener wyswietlonego drzewa.
     * 
     * @param event Wydarzenie wywolane nacisnieciem przycisku myszy.
     */
    private void nacisnietoNaPrzestrzenDrzewa(MouseEvent event) {
        this.pozycja_myszki_x = event.getScreenX();
        this.pozycja_myszki_y = event.getScreenY();
    }

    /**
     * Wydarzenie wywolane w przypadku, gdy po przytrzymaniu przycisku myszy, zostala ona przeciagnieta w dowolnym kierunku.
     * 
     * @param event Wydarzenie wywolane ruszeniem myszy trzymajac jej przycisk.
     */
    private void przeciagnietoPrzestrzenDrzewa(MouseEvent event) {
        double nowaPozycjaX = event.getScreenX();
        double nowaPozycjaY = event.getScreenY();
        
        // aktualizacja polozenia wszystkich wezlow
        for(Node element : this.przestrzen_drzewa.getChildren()) {
            Translate przesuniecie = (Translate)element.getTransforms().get(0);
            przesuniecie.setX(przesuniecie.getX() + nowaPozycjaX - this.pozycja_myszki_x);
            przesuniecie.setY(przesuniecie.getY() + nowaPozycjaY - this.pozycja_myszki_y);
        }

        // aktualizacja aktualnego przesuniecia kazdego z wezlow
        this.aktualna_delta_x += nowaPozycjaX - this.pozycja_myszki_x;
        this.aktualna_delta_y += nowaPozycjaY - this.pozycja_myszki_y;

        kontroler_wygladu.podajAktualnePrzesuniecie(this.aktualna_delta_x, this.aktualna_delta_y);

        this.pozycja_myszki_x = nowaPozycjaX;
        this.pozycja_myszki_y = nowaPozycjaY;
    }

    /**
     * Metoda uruchamiajaca watek odpowiedzialny za polaczenie klienta z serwerem.
     */
    private void sprobujPolaczycSerwer() {
        Thread watek = new Thread(new PolaczSerwer());
        watek.setDaemon(true);
        watek.start();
    }

    /**
     * Klasa odpowiedzialna za polaczenie sie z serwerem. 
     * Ustawia odpowiedni wyglad paska w zaleznosci od statusu polaczenia.
     */
    private class PolaczSerwer implements Runnable {
        /**
         * Metoda odpowiedzialna za laczenie aplikacji z serwerem.
         * Podejmuje ona proby polaczenia przez 10 sekund.
         */
        public void run() { 
            boolean polaczony = false;
            double czas_start = LocalTime.now().getSecond();
            double czas_aktualny;
            // ustaw wyglad paska przy laczeniu sie z serwerem
            kontroler_wygladu.ustawStatusLaczenie();
            // probuj przez 10 sekund polaczyc sie z serwerem
            do {
                if(!aplikacja_aktywna)
                    return;
                czas_aktualny = LocalTime.now().getSecond();
                try {
                    polaczenie = new Socket("localhost", 4444);

                    wczyt = new BufferedReader(new InputStreamReader(polaczenie.getInputStream()));
                    przekaz = new PrintWriter(polaczenie.getOutputStream(), true);
                    polaczony = true;
                    break;
                } catch(IOException blad) {
                    polaczony = false;
                } 
            } while(czas_aktualny - czas_start < 10);
            // wyswietl odpowiedni status w zaleznosci od polaczenia z serwerem
            if(polaczony) {
                kontroler_wygladu.ustawStatusPolaczony();
                uruchomMonitorSerwera();
            } else {
                kontroler_wygladu.ustawStatusBrakPolaczenia();
            }
        }
    }

    /**
     * Metoda uruchamiajaca watek monitorujacy polaczenie z serwerem.
     */
    protected void uruchomMonitorSerwera() {
        Thread monitor_serwera = new Thread(new MonitorSerwera());
        monitor_serwera.setDaemon(true);
        monitor_serwera.start();
    }

    /**
     * Klasa odpowiedzialna za monitorowanie polaczenia z serwerem.
     */
    private class MonitorSerwera implements Runnable {
        /**
         * Metoda monitorujaca serwer.
         * Wysyla ona rowniez zapytanie o wyswietlenie przy kazdym przebiegu petli, aby
         * drzewo aktualizowane bylo w aplikacji automatycznie.
         */
        public void run() {
            while(true) {
                if(!aplikacja_aktywna) {
                    return;
                }
                try {
                    String typ = zwrocTypDrzewa();
                    String drzewo = wyslijOdbierz("BEAT " + typ + " 3");
                    // ciag znakow "BEAT" odpowiedzialny jest za odroznienie monitorowania serwera od komunikacji w celu dzialania na drzewie binarnym
                    if(!drzewo.equals(aktualne_drzewo)) {
                        kontroler_wygladu.wyswietlDrzewo(drzewo);
                        aktualne_drzewo = drzewo;
                    }
                } catch(IOException blad) {
                    kontroler_wygladu.ustawStatusRozlaczono();
                    return;
                }
            }
        }
    }

    /**
     * Metoda komunikujaca sie z serwerem. Wysyla ciag znakow, a nastepnie odbiera rowniez ciag znakow.
     * 
     * @param wiadomosc Polecenie wysylane do serwera.
     * @return Odpowiedz serwera na wyslane polecenie.
     * @throws IOException Blad wywolywany przy problemie z polaczeniem z serwerem.
     */
    protected synchronized String wyslijOdbierz(String wiadomosc) throws IOException {
        przekaz.println(wiadomosc);
        return wczyt.readLine();
    }

    /**
     * Klasa odpowiedzialna za proces komunikowania sie z serwerem.
     */
    private class ProcesKomunikacji implements Runnable {
        private String polecenie;

        /**
         * Konstuktor, zapisuje podane przez uzytkownika polecenie.
         * 
         * @param polecenie Polecenie do wykonania na drzewie
         */
        public ProcesKomunikacji(String polecenie) {
            this.polecenie = polecenie;
        }

        /**
         * Metoda odpowiedzialna za wyslanie polecenia do serwera oraz odebranie odpowiedzi.
         * Po odebraniu odpowiedzi nastepuje wyswietlenie komunikatu zawierajaca status wykonanego polecenia.
         */
        public void run() {
            // format polecenia: "[typ_drzewa | int] [polecenie | int] [opcjonalna wartosc | int/double/string]"

            String wiadomosc = "";
            if(przekaz != null && wczyt != null) {
                try {
                    do {
                        if(!aplikacja_aktywna)
                            return;
                        wiadomosc = wyslijOdbierz(this.polecenie);
                    } while(wiadomosc.isEmpty());
                } catch(IOException blad) {
                    kontroler_wygladu.uruchomAnimacjePowiadomienia("Brak polaczenia z serwerem.");
                    return;
                }
                if(wiadomosc.equals("POWODZENIE"))
                    kontroler_wygladu.uruchomAnimacjePowiadomienia("Operacja zakonczona powodzeniem");
                else if(wiadomosc.equals("BLAD"))
                    kontroler_wygladu.uruchomAnimacjePowiadomienia("Operacja sie nie powiodla");
                else if(wiadomosc.equals("NIEPRAWIDLOWY_FORMAT"))
                    kontroler_wygladu.uruchomAnimacjePowiadomienia("Wprowadzono dane o nieprawidlowym formacie.");
                else if(wiadomosc.equals("BRAK_WEZLA"))
                    kontroler_wygladu.uruchomAnimacjePowiadomienia("Drzewo nie posiada wezla z podana wartoscia");
                else
                    kontroler_wygladu.uruchomAnimacjePowiadomienia(wiadomosc);
            } else {
                kontroler_wygladu.uruchomAnimacjePowiadomienia("Brak polaczenia z serwerem.");
            }
        }
    }

    /**
     * Metoda odpowiedzialna za wylaczenie wszystkich aktywnych watkow.
     */
    public void wylaczWatki() {
        this.aplikacja_aktywna = false;
    }

    /**
     * Metoda odpowiedzialna za rozlaczenie klienta z serwerem.
     */
    public void rozlaczZSerwerem() {
        try {
            if(this.polaczenie != null) {
                this.przekaz.println("KONIEC");
                this.polaczenie.close();
            }
        } catch(IOException blad) {
            return;
        }
    }
}
