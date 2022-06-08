import java.io.*;
import java.net.*;

/**
 * Glowna klasa serwera, odpowiedzialna za uruchomienie serwera oraz przekazywanie klientow do osobnych watkow.
 */
public class Serwer {
    private static ServerSocket serwer;
    private static KontrolerDrzewa kontroler;

    public static void main(String[] args) {
        try {
            serwer = new ServerSocket(4444);
            System.out.println("[SERWER] Nasluchiwanie portu 4444.");

            // utworzenie kontrolera drzewa binarnego, wspolnego dla wszystkich klientow
            kontroler = new KontrolerDrzewa();

            while(true) {
                Socket klient = serwer.accept();
                System.out.println("[SERWER] Polaczono nowego klienta: " + klient.toString());

                new WatekKlienta(klient, kontroler).start();
            }
        } catch(IOException blad) {
            System.out.println("[SERWER] napotkano blad: " + blad.getMessage());
            blad.printStackTrace();
        }
    }

}