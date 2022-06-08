import java.io.*;
import java.net.*;
import javafx.application.Application;
import javafx.scene.*;
import javafx.stage.Stage;

/**
 * Glowna klasa GUI klienta, odpowiedzialna za utworzenie okna oraz kontrolerow.
 */
public class App extends Application {
    // pola pomocnicze okna aplikacji
    private int STARTOWA_SZEROKOSC_OKNA = 800;
    private int STARTOWA_WYSOKOSC_OKNA = 600;

    // kontrolery aplikacji - dzialania i wygladu
    KontrolerAplikacji kontroler;
    WygladAplikacji kontroler_wygladu;


    /**
     * Metoda start, tworzy kontrolery oraz ustawia okno.
     * 
     * @param stage Host sceny.
     * @throws IOException Blad wejscia/wyjscia.
     */
    @Override
    public void start(Stage stage) throws IOException {
        Group korzen = new Group();
        Scene scena = new Scene(korzen, STARTOWA_SZEROKOSC_OKNA, STARTOWA_WYSOKOSC_OKNA);

        kontroler_wygladu = new WygladAplikacji(scena, korzen, this, STARTOWA_SZEROKOSC_OKNA, STARTOWA_WYSOKOSC_OKNA);
        kontroler = new KontrolerAplikacji(kontroler_wygladu);

        stage.setTitle("Klient drzewa binarnego.");
        stage.setMinHeight(300);
        stage.setMinWidth(300);
        stage.setScene(scena);
        stage.show();
    }

    /**
     * Metoda wywolywana przy zamykaniu aplikacji, odpowiedzialna za wylaczenie wszystkich aktywnych watkow.
     * 
     * @throws Exception Blad przy zamykaniu aplikacji.
     */
    @Override
    public void stop() throws Exception {
        kontroler.rozlaczZSerwerem();
        kontroler.wylaczWatki();
        super.stop();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
