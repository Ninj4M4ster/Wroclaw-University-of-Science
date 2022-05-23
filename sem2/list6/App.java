import java.io.IOException;
import java.util.List;

import javafx.application.Application;
import javafx.application.Application.Parameters;
import javafx.scene.*;
import javafx.stage.Stage;

/**
 * Glowna klasa aplikacji.
 */
public class App extends Application{
    // zmienne pomocnicze dla pol
    private int ilosc_pol_poziomo;
    private int ilosc_pol_pionowo;
    private int szybkosc_dzialania;
    private int prawdopodobientswo;

    // zmienne pomocnicze okna
    private double aktualnaSzerokoscOkna = 800;
    private double aktualnaWysokoscOkna = 500;

    // zmienna przechowujaca kontroler aplikacji
    private KontrolerAplikacji kontroler;

    /**
     * Metoda uruchamiajaca gui aplikacji oraz tworzaca niezbedne komponenty.
     * 
     * @see KontrolerAplikacji
     * @see KontrolerAplikacji#utworzPola
     * @see KontrolerAplikacji#uruchomPola
     * @param stage Glowny kontener aplikacji.
     * @throws IOException Blad operacji I/O.
     */
    @Override
    public void start(Stage stage) throws IOException {
        Group root = new Group();
        Scene scena = new Scene(root, aktualnaSzerokoscOkna, aktualnaWysokoscOkna);
        
        // pobranie parametrow podanych przez uzytkownika i przekazanie ich do kontrolera aplikacji
        List<String> parametry = getParameters().getUnnamed();
        KontrolerAplikacji kontroler = new KontrolerAplikacji(parametry, scena, root, this);
        kontroler.utworzPola();

        stage.setTitle("Symulacja wielowatkowej planszy");
        stage.setScene(scena);
        stage.show();

        // uruchomienie pol
        kontroler.uruchomPola();
    }

    /**
     * Metoda uruchamiana przy zamykaniu okna. 
     * 
     * @see KontrolerAplikacji#zakonczWatki
     * @throws Exception Blad przy zamykaniu okna
     */
    @Override
    public void stop() throws Exception {
        if(kontroler != null) {
            kontroler.zakonczWatki();
        }
        super.stop();
    }

    /**
     * Main - metoda wywolywana przy uruchamianiu aplikacji przez uzytkownika.
     */
    public static void main(String[] args) {
        launch(args);
    }
}
