import java.io.*;
import java.net.*;

/**
 * Watek uruchamiany dla nowo polaczonego klienta, odpowiedzlany za odbieranie i wysylanie wiadomosci.
 */
class WatekKlienta extends Thread {
    private final Socket klient;
    private final KontrolerDrzewa kontroler;
    private BufferedReader wczyt = null;
    private PrintWriter przekaz = null;

    /**
     * Konstruktor, zapisuje przekazane wartosci oraz tworzy zmienne sluzace do komunikacji z klientem.
     * 
     * @param klient Polaczenie z klientem.
     * @param kontroler Kontoler drzewa binanego.
     */
    public WatekKlienta(Socket klient, KontrolerDrzewa kontroler) {
        this.klient = klient;
        this.kontroler = kontroler;

        this.setDaemon(true);

        try {
            this.wczyt = new BufferedReader(new InputStreamReader(klient.getInputStream()));
            this.przekaz = new PrintWriter(klient.getOutputStream(), true);
        } catch(IOException blad) {
            System.out.println("[SERWER] Blad serwera: " + blad.getMessage());
            blad.printStackTrace();
        }
    }
    
    /**
     * Metoda dzialajaca po uruchomieniu watku. Przyjmuje wiadomosci od klienta
     * oraz wysyla je do kontrolera drzewa binarnego.
     */
    @Override
    public void run() {
        String wiadomosc = "";
        try {
            if(wczyt != null && przekaz != null) {
                do {
                    wiadomosc = wczyt.readLine();
                    // logika sprawdzania czy serwer jest aktywny
                    if(wiadomosc.startsWith("BEAT")) {
                        String drzewo = this.kontroler.przekazSformatowanyNapis(wiadomosc.substring(5));
                        przekaz.println(drzewo);
                    } else {
                        if(wiadomosc != null && !wiadomosc.isEmpty() && !wiadomosc.strip().equals("KONIEC")) {
                            System.out.println("[SERWER] Klient " + this.klient.toString() + " wyslal wiadomosc " + wiadomosc);
                            String wynik_operacji = this.kontroler.przekazSformatowanyNapis(wiadomosc);
                            przekaz.println(wynik_operacji);
                        } 
                    }
                } while(!wiadomosc.equals("KONIEC"));

                // po otrzymaniu wiadomosci "KONIEC" klient rozlaczyl sie z serwerem
                System.out.println("[SERWER] Klient " + this.klient.toString() + " rozlaczyl sie z serwerem");
            }
        } catch(IOException blad) {
            System.out.println("[SERWER] Blad serwera: " + blad.getMessage());
            blad.printStackTrace();
        }
    }
}
