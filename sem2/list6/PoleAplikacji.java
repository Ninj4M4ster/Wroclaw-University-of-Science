import java.util.List;

import javafx.scene.shape.*;
import javafx.scene.*;
import javafx.scene.paint.Color;
import javafx.application.Platform;

/**
 * Klasa implementujaca pole aplikacji samoczynnie zmieniajace swoj kolor.
 */
class PoleAplikacji extends Rectangle implements Runnable {

    // zmienne pomocnicze pola
    private int numer_wiersza;
    private int numer_kolumny;
    private int ilosc_kolumn;
    private int ilosc_wierszy;
    private double szybkosc;
    private double prawdopodobienstwo;

    private Thread watek;

    private boolean aktywny;

    // zmienna przechowujaca element torusu odpowiadajacy danemu polu
    private ElementListy element_w_liscie;

    // zmienna przechowujaca kontroler watkow
    private KontrolerWatkow kontroler_watkow;

    /**
     * Konstruktor odpowiedzialny za utworzenie pola aplikacji w odpowiednim miejscu 
     * oraz zmiane pozycji i rozmiaru przy rozszerzaniu okna.
     * 
     * @param numer_wiersza Indeks wiersza danego pola.
     * @param numer_kolumny Indeks kolumny danego pola.
     * @param parametry Parametry wprowadzone przy uruchamianiu aplikacji.
     * @param scena Scena aplikacji.
     * @param kontroler_watkow Instancja kontrolera watkow.
     */
    public PoleAplikacji(int numer_wiersza, int numer_kolumny, List<String> parametry, Scene scena, KontrolerWatkow kontroler_watkow) {
        super();
        // przekazanie parametrow do pol klasy
        this.numer_wiersza = numer_wiersza;
        this.numer_kolumny = numer_kolumny;

        this.ilosc_wierszy = Integer.parseInt(parametry.get(0));
        this.ilosc_kolumn = Integer.parseInt(parametry.get(1));
        this.szybkosc = Double.parseDouble(parametry.get(2));
        this.prawdopodobienstwo = Double.parseDouble(parametry.get(3));

        this.kontroler_watkow = kontroler_watkow;
    
        // ustawienie wygladu i polozenia pola
        setX(this.numer_kolumny * scena.getWidth() / this.ilosc_kolumn);
        setY(this.numer_wiersza * scena.getHeight() / this.ilosc_wierszy);

        setWidth(scena.getWidth() / this.ilosc_kolumn);
        setHeight(scena.getHeight() / this.ilosc_wierszy);
        
        setFill(Color.color(Math.random(), Math.random(), Math.random()));

        // automatyczne dostosowywanie rozmiaru do okna aplikacji
        scena.widthProperty().addListener((obs, oldVal, newVal) -> {
            synchronized(this) {
                setWidth(newVal.doubleValue() / this.ilosc_kolumn);
                setX(this.numer_kolumny * newVal.doubleValue() / this.ilosc_kolumn);
            }
        });
        scena.heightProperty().addListener((obs, oldVal, newVal) -> {
            synchronized(this) {
                setHeight(newVal.doubleValue() / this.ilosc_wierszy);
                setY(this.numer_wiersza * newVal.doubleValue() / this.ilosc_wierszy);
            }
        });

        this.watek = new Thread(this, this.numer_wiersza + " - " + this.numer_kolumny);
        this.watek.setDaemon(true);
    }

    /**
     * Metoda odpowiadajaca za przekazanie z listy elementu torusu odpowiadajacego danemu polu.
     * 
     * @param element Element torusu.
     */
    public void przekazElementListy(ElementListy element) {
        this.element_w_liscie = element;
    }

    /**
     * Metoda odpowiedzialna za zatrzymanie dzialania watku.
     */
    public void zatrzymaj() {
        this.aktywny = false;
    }

    /**
     * Akcja wykonywana przez watek. Na podstawie wygenerowanego prawdopodobienstwa 
     * decyduje o zmianie koloru pola aplikacji.
     * 
     * @see KontrolerWatkow#generujSzybkosc
     * @see KontrolerWatkow#generujPrawdopodobienstwo
     * @see KontrolerWatkow#generujKolor
     * @see KontrolerWatkow#obliczSredniaKolorow
     */
    @Override
    public void run() {
        this.aktywny = true;
        while(this.aktywny) {
            try {
                Thread.sleep(Double.valueOf(kontroler_watkow.generujSzybkosc(this.szybkosc)).longValue());
                double wygenerowane_prawdopodobienstwo = kontroler_watkow.generujPrawdopodobienstwo();
                Color nowy_kolor;
                if(wygenerowane_prawdopodobienstwo <= this.prawdopodobienstwo) {
                    System.out.println(this.numer_wiersza + " - " + this.numer_kolumny + ", zmieniam kolor na losowy");
                    nowy_kolor = kontroler_watkow.generujKolor();
                } else {
                    System.out.println(this.numer_wiersza + " - " + this.numer_kolumny + ", obliczam srednia kolorow");
                    nowy_kolor = this.kontroler_watkow.obliczSredniaKolorow(this.element_w_liscie);
                }
                Platform.runLater(new Runnable() {
                    @Override
                    public void run() {
                        setFill(nowy_kolor);
                    }
                });
            } catch(Exception e) {
                System.out.println(e.getMessage());
            }
            
        }
    }

    /**
     * Metoda odpowiedzialna za uruchomienie watku.
     */
    public void start() {
        this.watek.start();
    }

    
}
