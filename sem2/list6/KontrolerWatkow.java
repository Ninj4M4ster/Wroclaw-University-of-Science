import java.util.Random;
import javafx.scene.paint.Color;

/**
 * Klasa odpowiedzialna za kontrole watkow. Generuje synchronicznie liczby losowe.
 */
class KontrolerWatkow {
    // generator liczb pseudolosowych
    private Random generator;

    /**
     * Konstruktor. Tworzy nowy generator.
     */
    public KontrolerWatkow() {
        this.generator = new Random();
    }

    /**
     * Metoda generujaca prawdopodobienstwo dla pola aplikacji.
     * 
     * @return Prawdopodobienstwo potrzebne do okreslenia kolejnej akcji przez pole aplikacji.
     */
    synchronized public double generujPrawdopodobienstwo() {
        return this.generator.nextDouble();
    }

    /**
     * Metoda generujaca szybkosc zmiany koloru pola.
     * 
     * @param szybkosc Szybkosc pol prowadzona jako parametr.
     * @return Czas po jakim pole ma zmienic kolor.
     */
    synchronized public double generujSzybkosc(double szybkosc) {
        return (this.generator.nextDouble() + 0.5) * szybkosc;
    }

    /**
     * Metoda generujaca losowy kolor dla pola aplikacji.
     * 
     * @return Losowo wygenerowany kolor.
     */
    synchronized public Color generujKolor() {
        return Color.color(this.generator.nextDouble(), this.generator.nextDouble(), this.generator.nextDouble());
    }

    /**
     * Metoda odpowiedzialna za obliczenie sredniego koloru z aktywnych pol znajdujacych sie wokol wybranego pola.
     * 
     * @see ElementListy#podajWatek
     * @see ElementListy#nastepnyPoziomo
     * @see ElementListy#nastepnyPionowo
     * @see ElementListy#poprzedniPoziomo
     * @see ElementListy#poprzedniPionowo
     * @param element Pole, dla ktorego obliczany jest nowy kolor.
     * @return Sredni kolor obliczony z pol sasiadujacych z wybranym polem.
     */
    public Color obliczSredniaKolorow(ElementListy element) {
        double wartosc_red = 0;
        double wartosc_blue = 0;
        double wartosc_green = 0;
        ElementListy[] elementy = {element.nastepnyPoziomo(), element.nastepnyPionowo(), 
            element.poprzedniPoziomo(), element.poprzedniPionowo()};
        // iteracja po kazdym sasiedzie wybranego pola
        for(ElementListy sasiad : elementy) {
            synchronized(sasiad) {
                Color aktualny_kolor = (Color)sasiad.podajWatek().getFill();
                wartosc_red += aktualny_kolor.getRed();
                wartosc_blue += aktualny_kolor.getBlue();
                wartosc_green += aktualny_kolor.getGreen();
            }
        }
        return Color.color(wartosc_red/4, wartosc_green/4, wartosc_blue/4);
    }
}
