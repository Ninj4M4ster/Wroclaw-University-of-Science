import javafx.scene.*;
import javafx.scene.control.*;
import javafx.scene.shape.*;
import javafx.scene.layout.*;
import javafx.scene.paint.*;
import javafx.geometry.*;
import javafx.scene.transform.*;

/**
 * Klasa odpowiedzialna za utworzenie wezla drzewa w GUI klienta z podana wartoscia.
 */
class GraficznyWezel {
    // widgety aplikacji
    private Pane przestrzen_drzewa;

    // dane charakteryzujace wezel
    private String[][] wiersze;
    private int numer_wartosci;
    private int numer_wiersza;
    private int ilosc_wierszy;
    private int ilosc_wartosci;
    private String wartosc;

    // stale pomocnicze przy ustawianiu wezlow
    private final double ODDALENIE_OD_GORNEJ_KRAWEDZI = 60.0;
    private final double ODLEGLOSC_WEZLOW_PIONOWA = 10.0;
    private final double ODLEGLOSC_WEZLOW_POZIOMA = 10.0;
    private final double ODLEGLOSC_OD_LEWEJ_KRAWEDZI = 40.0;

    // tworzone widgety
    private StackPane kontener;
    private Line linia_lewy;
    private Line linia_prawy;
    
    /**
     * Konstruktor, przyjmuje wartosci od kontrolera oraz tworzy strukture reprezentujaca wezel drzewa binarnego.
     * 
     * @param wiersze Wszystkie wartosci drzewa binarnego.
     * @param numer_wiersza Numer wiersza tworzonego wezla.
     * @param numer_wartosci Numer wartosci tworzonego wezla.
     * @param wartosc Wartosc do wyswietlenia przez wezel. 
     * @param przestrzen_drzewa Widget aplikacji wyswietlajacy drzewo.
     */
    public GraficznyWezel(
        String[][] wiersze,
        int numer_wiersza,
        int numer_wartosci,
        String wartosc,
        Pane przestrzen_drzewa
    ) {
        this.wartosc = wartosc;
        this.przestrzen_drzewa = przestrzen_drzewa;
        this.wiersze = wiersze;
        this.numer_wartosci = numer_wartosci;
        this.numer_wiersza = numer_wiersza;

        this.ilosc_wierszy = wiersze.length;
        this.ilosc_wartosci = wiersze[numer_wiersza].length;

        // utworzenie konteneru struktury
        kontener = new StackPane();
        kontener.setPrefWidth(60);
        kontener.setPrefHeight(60);
        kontener.getTransforms().add(new Translate(0, 0));

        // utworzenie kola jako tla wezla
        Circle kolo = new Circle(); 
        kolo.setRadius(30);
        kolo.setFill(Color.WHITE);
        kolo.setStroke(Color.BLACK);

        // utworzenie wyswietlanego tekstu z wartoscia wezla
        Label tekst = new Label(this.wartosc);
        tekst.setAlignment(Pos.CENTER);
        tekst.setWrapText(true);
        tekst.setBackground(new Background(new BackgroundFill(Paint.valueOf("#ffffffaf"), null, null)));

        double wspolrzedna_x = this.obliczX(this.numer_wartosci, this.numer_wiersza, this.ilosc_wierszy);
        double wspolrzedna_y = this.obliczY(this.numer_wiersza, this.ilosc_wierszy);

        // dodanie elementow i ustawienie kontenera
        this.kontener.getChildren().addAll(kolo, tekst);
        this.kontener.setAlignment(Pos.CENTER);
        this.kontener.relocate(wspolrzedna_x - 30.0, wspolrzedna_y - 30.0);

        // rysowanie linii pomiedzy wezlami
        if(this.numer_wiersza > 0) {
            double wspolrzedna_lewy_x = this.obliczX(2 * numer_wartosci, numer_wiersza - 1, ilosc_wierszy);
            double wspolrzedna_prawy_x = this.obliczX(2 * numer_wartosci + 1, numer_wiersza - 1, ilosc_wierszy);

            double wspolrzedna_lewy_prawy_y = this.obliczY(numer_wiersza - 1, ilosc_wierszy);

            if(this.wiersze[numer_wiersza - 1][2 * numer_wartosci] != null && !this.wiersze[numer_wiersza - 1][2 * numer_wartosci].equals("_")) {
                this.linia_lewy = new Line();
                this.linia_lewy.setStartX(wspolrzedna_lewy_x);
                this.linia_lewy.setStartY(wspolrzedna_lewy_prawy_y);
                this.linia_lewy.setEndX(wspolrzedna_x);
                this.linia_lewy.setEndY(wspolrzedna_y);

                this.linia_lewy.getTransforms().add(new Translate(0, 0));

                this.przestrzen_drzewa.getChildren().add(linia_lewy);
            }
            if(this.wiersze[numer_wiersza - 1][2 * numer_wartosci + 1] != null && !this.wiersze[numer_wiersza - 1][2 * numer_wartosci + 1].equals("_")) {
                this.linia_prawy = new Line();
                this.linia_prawy.setStartX(wspolrzedna_prawy_x);
                this.linia_prawy.setStartY(wspolrzedna_lewy_prawy_y);
                this.linia_prawy.setEndX(wspolrzedna_x);
                this.linia_prawy.setEndY(wspolrzedna_y);

                this.linia_prawy.getTransforms().add(new Translate(0, 0));

                this.przestrzen_drzewa.getChildren().add(linia_prawy);
            }
            
        }   

        this.przestrzen_drzewa.getChildren().add(kontener);
    }

    /**
     * Metoda odpowiedzialna za policzenie wspolrzednej X srodka kontenera.
     * 
     * @param numer_wartosci Numer wartosci tworzonego wezla.
     * @param numer_wiersza Numer wiersza tworzonego wezla.
     * @param ilosc_wierszy Ilosc wierszy w drzewie.
     * @return Wspolrzedna X.
     */
    public double obliczX(int numer_wartosci, int numer_wiersza, int ilosc_wierszy) {
        if(numer_wiersza != 0) {
            return (obliczX(2 * numer_wartosci, numer_wiersza - 1, ilosc_wierszy) + obliczX(2 * numer_wartosci + 1, numer_wiersza - 1, ilosc_wierszy)) / 2.0;
        }
        return 60.0 * numer_wartosci + ODLEGLOSC_OD_LEWEJ_KRAWEDZI + ODLEGLOSC_WEZLOW_POZIOMA * (numer_wartosci);
    }

    /**
     * Metoda odpowiedzialna za policzenie wspolrzednej Y srodka kontenera.
     * 
     * @param numer_wiersza Numer wiersza tworzonego wezla.
     * @param ilosc_wierszy Ilosc wierszy w drzewie.
     * @return Wspolrzedna Y.
     */
    public double obliczY(int numer_wiersza, int ilosc_wierszy) {
        return 60.0 * (ilosc_wierszy - numer_wiersza) + ODDALENIE_OD_GORNEJ_KRAWEDZI + (ODLEGLOSC_WEZLOW_PIONOWA * (ilosc_wierszy - numer_wiersza));
    }
    
    /**
     * Metoda odpowiedzialna za przesuniecie kontenera o okreslona odleglosc.
     * 
     * @param delta_x Roznica odleglosci na osi X.
     * @param delta_y Roznica odleglosci na osi Y.
     */
    public void przesun(double delta_x, double delta_y) {
        Translate przesuniecie_kontenera = (Translate)kontener.getTransforms().get(0);
        przesuniecie_kontenera.setX(przesuniecie_kontenera.getX() + delta_x);
        przesuniecie_kontenera.setY(przesuniecie_kontenera.getY() + delta_y);

        if(linia_lewy != null) {
            Translate przesuniecie_lewy = (Translate)linia_lewy.getTransforms().get(0);
            przesuniecie_lewy.setX(przesuniecie_lewy.getX() + delta_x);
            przesuniecie_lewy.setY(przesuniecie_lewy.getY() + delta_y);
        }
        if(linia_prawy != null) {
            Translate przesuniecie_prawy = (Translate)linia_prawy.getTransforms().get(0);
            przesuniecie_prawy.setX(przesuniecie_prawy.getX() + delta_x);
            przesuniecie_prawy.setY(przesuniecie_prawy.getY() + delta_y);
        }
    }
}
