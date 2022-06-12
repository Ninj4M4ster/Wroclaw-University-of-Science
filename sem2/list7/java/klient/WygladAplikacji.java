import javafx.scene.*;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.scene.paint.*;
import javafx.scene.text.*;
import javafx.scene.shape.*;
import javafx.application.Platform.*;
import javafx.application.*;
import javafx.geometry.*;
import javafx.animation.*;
import javafx.util.*;

/**
 * Klasa odpowiedzialna za utworzenie i kontrole wygladu GUI.
 */
class WygladAplikacji {
    // widgety aplikacji
    private Scene scena;
    private Group korzen;
    private Application aplikacja;
    private Label pasek_powiadomien;
    private Pane pasek_statusu;
    private Label tekst_statusu;
    private Button przycisk_polaczenia;
    private BorderPane uklad_aplikacji;
    private StackPane zewnetrzna_przestrzen_drzewa;
    private Pane przestrzen_drzewa;
    private VBox uklad_przestrzeni_przyciskow;

    // przyciski do kontroli drzewa
    private ChoiceBox<String> przycisk_wyboru_typu_drzewa;
    private Button przycisk_dodania_wezla;
    private Button przycisk_usuniecia_wezla;
    private Button przycisk_wyszukania_wezla;
    private Button przycisk_wyswietlenia_drzewa;

    // zmienne pomocnicze dla animacji powiadomien
    private Animation animacja_powiadomienia;

    // zmienne pomocnicze paska statusu
    private double szerokosc_tekstu_statusu;

    // zmienne pomocnicze okna    
    private double aktualna_szerokosc_okna;
    private double aktualna_wysokosc_okna;

    // stale okreslajace rozmiary widget'ow
    private final double SZEROKOSC_PRZESTRZENI_PRZYCISKOW = 200.0;
    private final double WYSOKOSC_PASKA_STATUSU = 27.0;
    private final double SZEROKOSC_TEKSTU_STATUSU = 260.0;
    private final double SZEROKOSC_PRZYCISKU_POLACZ_Z_SERWEREM = 120.0; 

    // zmienne pomocnicze kontroli przestrzeni drzewa
    private double aktualna_delta_x = 0;
    private double aktualna_delta_y = 0;

    /**
     * Konstruktor, tworzy wyglad aplikacji oraz kontroluje ja w przypadku zmiany rozmiaru GUI.
     * 
     * @param scena Scena aplikacji.
     * @param korzen Korzen aplikacji.
     * @param aplikacja Uruchomiona aplikacja.
     * @param startowa_szerokosc_okna wartosc startowej szerokosci okna.
     * @param startowa_wysokosc_okna Wartosc startowej wysokosci okna.
     */
    public WygladAplikacji(
        Scene scena, 
        Group korzen, 
        Application aplikacja, 
        double startowa_szerokosc_okna, 
        double startowa_wysokosc_okna
    ) {
        this.scena = scena;
        this.korzen = korzen;
        this.aplikacja = aplikacja;
        this.aktualna_szerokosc_okna = startowa_szerokosc_okna;
        this.aktualna_wysokosc_okna = startowa_wysokosc_okna;

        // stworzenie ukladu aplikacji oraz dodanie go do korzenia
        this.uklad_aplikacji = new BorderPane();
        this.korzen.getChildren().add(this.uklad_aplikacji);

        // utworzenie wszystkich potrzebnych elementow aplikacji
        this.stworzPasekPowiadomien();
        this.stworzPrzestrzenDrzewa();
        this.stworzPrzyciskiKontroli();
        this.stworzPasekStatusu();

        // automatyczna zmiana rozmiarow widget'ow
        this.scena.widthProperty().addListener((obs, oldVal, newVal) -> {
            this.aktualna_szerokosc_okna = newVal.doubleValue();
            this.pasek_powiadomien.setPrefWidth(newVal.doubleValue());
            this.przestrzen_drzewa.setPrefWidth(newVal.doubleValue() - this.SZEROKOSC_PRZESTRZENI_PRZYCISKOW);
            this.zewnetrzna_przestrzen_drzewa.setPrefWidth(newVal.doubleValue() - this.SZEROKOSC_PRZESTRZENI_PRZYCISKOW);
            this.pasek_statusu.setPrefWidth(newVal.doubleValue());
            if(pasek_statusu.getChildren().contains(this.przycisk_polaczenia)) {
                this.tekst_statusu.relocate(
                    this.aktualna_szerokosc_okna - this.szerokosc_tekstu_statusu - this.SZEROKOSC_PRZYCISKU_POLACZ_Z_SERWEREM - 20, 5);
                this.przycisk_polaczenia.relocate(this.aktualna_szerokosc_okna - this.SZEROKOSC_PRZYCISKU_POLACZ_Z_SERWEREM - 10, 1);
            } else {
                tekst_statusu.relocate(this.aktualna_szerokosc_okna - this.szerokosc_tekstu_statusu - 10, 5);
            }
        });

        this.scena.heightProperty().addListener((obs, oldVal, newVal) -> {
            this.aktualna_wysokosc_okna = newVal.doubleValue();
            this.przestrzen_drzewa.setPrefHeight(newVal.doubleValue() - this.WYSOKOSC_PASKA_STATUSU);
            this.zewnetrzna_przestrzen_drzewa.setPrefHeight(newVal.doubleValue() - this.WYSOKOSC_PASKA_STATUSU);
            this.uklad_przestrzeni_przyciskow.setPrefHeight(this.aktualna_wysokosc_okna - this.WYSOKOSC_PASKA_STATUSU);
        });
    }

    /**
     * Metoda odpowiedzialna za utworzenie animowanego paska powiadomien.
     */
    private void stworzPasekPowiadomien() {
        this.pasek_powiadomien = new Label();
        this.pasek_powiadomien.setPrefWidth(this.aktualna_szerokosc_okna);
        this.pasek_powiadomien.setPrefHeight(40.0);
        this.pasek_powiadomien.relocate(0, -40);
        this.pasek_powiadomien.setBorder(new Border(new BorderStroke(
            Paint.valueOf("#1c1c1c"), 
            BorderStrokeStyle.SOLID, 
            new CornerRadii(0), 
            new BorderWidths(1, 1, 1, 1)
            )));
        this.pasek_powiadomien.setBackground(new Background(new BackgroundFill(
            Paint.valueOf("#a1a1a1"), 
            null, 
            null
            )));
        this.pasek_powiadomien.setAlignment(Pos.CENTER);
        this.pasek_powiadomien.setFont(new Font(20));
        
        // utworzenie animacji powiadomienia
        this.animacja_powiadomienia = new Transition() {
            {
                setCycleDuration(Duration.millis(5000));
            }
            protected void interpolate(double frac) {
                if(frac < 0.15) {
                    final double wysokosc = 266.666 * frac - 40;
                    pasek_powiadomien.relocate(0, wysokosc);
                } else if (frac >= 0.85) { 
                    final double wysokosc = -266.666 * frac + 226.666;
                    pasek_powiadomien.relocate(0, wysokosc);
                } else if(frac == 1.0) {
                    pasek_powiadomien.relocate(0, -40);
                }
            }
        };

        this.korzen.getChildren().add(this.pasek_powiadomien);
    }

    /**
     * Metoda odpowiedzialna za wyswietlenie powiadomienia z odpowiednia wiadomoscia.
     * 
     * @param powiadomienie Wiadomosc powiadomienia.
     */
    public void uruchomAnimacjePowiadomienia(String powiadomienie) {
        Platform.runLater(new Runnable() {
            @Override
            public void run() {
                pasek_powiadomien.setText(powiadomienie);
                animacja_powiadomienia.playFromStart();
            }
        });
    }

    /**
     * Metoda odpowiedzialna za utworzenie przestrzeni wyswietlajacej drzewo binarne.
     */
    private void stworzPrzestrzenDrzewa() {
        // utworzenie glownej przestrzeni
        this.przestrzen_drzewa = new Pane();
        this.przestrzen_drzewa.setPrefWidth(this.aktualna_szerokosc_okna - this.SZEROKOSC_PRZESTRZENI_PRZYCISKOW);
        this.przestrzen_drzewa.setPrefHeight(this.aktualna_wysokosc_okna - this.WYSOKOSC_PASKA_STATUSU);

        // utworzenie prostokatu przycinajacego elementy wychodzace poza dozwolony obszar
        Rectangle ograniczenie = new Rectangle();
        this.przestrzen_drzewa.setClip(ograniczenie);

        this.przestrzen_drzewa.layoutBoundsProperty().addListener((obs, oldVal, newVal) -> {
            ograniczenie.setWidth(newVal.getWidth());
            ograniczenie.setHeight(newVal.getHeight());
        }); 

        // utworzenie kontenera na wszystkie elementy z obramowaniem
        this.zewnetrzna_przestrzen_drzewa = new StackPane(this.przestrzen_drzewa);
        this.zewnetrzna_przestrzen_drzewa.setPrefHeight(this.aktualna_wysokosc_okna - this.WYSOKOSC_PASKA_STATUSU);
        this.zewnetrzna_przestrzen_drzewa.setPrefWidth(this.aktualna_szerokosc_okna - this.SZEROKOSC_PRZESTRZENI_PRZYCISKOW);
        this.zewnetrzna_przestrzen_drzewa.setBorder(new Border(new BorderStroke(
            Paint.valueOf("#262626"), 
            BorderStrokeStyle.SOLID, 
            new CornerRadii(0), 
            new BorderWidths(2, 2, 0, 0)
        )));

        this.uklad_aplikacji.setLeft(this.zewnetrzna_przestrzen_drzewa);
    }

    /**
     * Metoda odpowiedzialna za utworznie paska statusu.
     */
    private void stworzPasekStatusu() {
        this.pasek_statusu = new Pane();
        this.tekst_statusu = new Label();
        this.przycisk_polaczenia = new Button();

        this.pasek_statusu.setPrefHeight(WYSOKOSC_PASKA_STATUSU);
        this.pasek_statusu.setPrefWidth(this.aktualna_szerokosc_okna);

        this.pasek_statusu.getChildren().add(this.tekst_statusu);

        // ustawienie tekstu na pasku statusu
        this.tekst_statusu.setFont(new Font(13));
        this.tekst_statusu.setTextFill(Paint.valueOf("#ffffff"));

        // utworzenie przycisku wyswietlanego przy braku polaczenia z serwerem
        this.przycisk_polaczenia.setText("Polacz z serwerem.");
        this.przycisk_polaczenia.setPrefWidth(this.SZEROKOSC_PRZYCISKU_POLACZ_Z_SERWEREM);
        this.przycisk_polaczenia.setPrefHeight(10);
        this.przycisk_polaczenia.relocate(this.aktualna_szerokosc_okna - this.SZEROKOSC_PRZYCISKU_POLACZ_Z_SERWEREM - 10, 1);

        this.uklad_aplikacji.setBottom(this.pasek_statusu);
    }

    /**
     * Metoda odpowiedzialna za ustawienie paska statusu gdy aplikacja probuje polaczyc sie z serwerem.
     */
    public void ustawStatusLaczenie() {
        Platform.runLater(new Runnable() {
            @Override
            public void run() {
                tekst_statusu.setText("Laczenie ...");
                tekst_statusu.setTextFill(Paint.valueOf("#ffffff"));
                pasek_statusu.setBackground(new Background(new BackgroundFill(Paint.valueOf("#0062ff"), null, null)));
                szerokosc_tekstu_statusu = 60.0;
                tekst_statusu.relocate(aktualna_szerokosc_okna - szerokosc_tekstu_statusu - 10, 5);
                if(pasek_statusu.getChildren().contains(przycisk_polaczenia)) {
                    pasek_statusu.getChildren().remove(przycisk_polaczenia);
                }
            }
        });
    }

    /**
     * Metoda odpowiedzialna za ustawienie paska statusu gdy aplikacja jest polaczona z serwerem.
     */
    public void ustawStatusPolaczony() {
        Platform.runLater(new Runnable() {
            @Override
            public void run() {
                tekst_statusu.setText("Polaczono z serwerem.");
                tekst_statusu.setTextFill(Paint.valueOf("#000000"));
                pasek_statusu.setBackground(new Background(new BackgroundFill(Paint.valueOf("#22fc00"), null, null)));
                szerokosc_tekstu_statusu = 125.0;
                tekst_statusu.relocate(aktualna_szerokosc_okna - szerokosc_tekstu_statusu - 10, 5);
            }
        });
    }

    /**
     * Metoda odpowiedzialna za ustawienie paska stausu gdy aplikacji nie uda sie polaczyc z serwerem.
     */
    public void ustawStatusBrakPolaczenia() {
        Platform.runLater(new Runnable() {
            @Override
            public void run() {
                tekst_statusu.setText("Nie udalo sie polaczyc z serwerem. Sprobuj ponownie.");
                tekst_statusu.setTextFill(Paint.valueOf("#ffffff"));
                pasek_statusu.setBackground(new Background(new BackgroundFill(Paint.valueOf("#ff0000"), null, null)));
                szerokosc_tekstu_statusu = 310.0;
                tekst_statusu.relocate(
                    aktualna_szerokosc_okna - szerokosc_tekstu_statusu - SZEROKOSC_PRZYCISKU_POLACZ_Z_SERWEREM - 20, 5
                    );
                przycisk_polaczenia.relocate(aktualna_szerokosc_okna - SZEROKOSC_PRZYCISKU_POLACZ_Z_SERWEREM - 10, 1);
                pasek_statusu.getChildren().add(przycisk_polaczenia);
            }
        });
    }

    /**
     * Metoda odpowiedzialna za ustawienie paska statusu gdy nastapi rozlaczenie z serwerem.
     */
    public void ustawStatusRozlaczono() {
        Platform.runLater(new Runnable() {
            @Override
            public void run() {
                tekst_statusu.setText("Polaczenie z serwerem zostalo zerwane.");
                tekst_statusu.setTextFill(Paint.valueOf("#ffffff"));
                pasek_statusu.setBackground(new Background(new BackgroundFill(Paint.valueOf("#ff0000"), null, null)));
                szerokosc_tekstu_statusu = 231.0;
                tekst_statusu.relocate(
                    aktualna_szerokosc_okna - szerokosc_tekstu_statusu - SZEROKOSC_PRZYCISKU_POLACZ_Z_SERWEREM - 20, 5
                    );
                przycisk_polaczenia.relocate(aktualna_szerokosc_okna - SZEROKOSC_PRZYCISKU_POLACZ_Z_SERWEREM - 10, 1);
                pasek_statusu.getChildren().add(przycisk_polaczenia);
            }
        });
    }

    /**
     * Metoda odpowiedzialna za utworzenie przyciskow sluzacych do kontroli drzewa binarnego.
     */
    private void stworzPrzyciskiKontroli() {
        // stworzenie i skonfigurowanie przestrzeni przyciskow
        this.uklad_przestrzeni_przyciskow = new VBox();

        this.uklad_przestrzeni_przyciskow.setPrefWidth(this.SZEROKOSC_PRZESTRZENI_PRZYCISKOW);
        this.uklad_przestrzeni_przyciskow.setPrefHeight(this.aktualna_wysokosc_okna - this.WYSOKOSC_PASKA_STATUSU);
        this.uklad_przestrzeni_przyciskow.setAlignment(Pos.CENTER);
        this.uklad_przestrzeni_przyciskow.setSpacing(30);
        this.uklad_przestrzeni_przyciskow.setBorder(new Border(new BorderStroke(
            Paint.valueOf("#262626"), 
            BorderStrokeStyle.SOLID, 
            new CornerRadii(0), 
            new BorderWidths(2, 0, 0, 0)
        )));
        this.uklad_przestrzeni_przyciskow.setBackground(new Background(new BackgroundFill(
            Paint.valueOf("#c7c7c7"),
            null,
            null
        )));

        // przycisk odpowiedzialny za wybor typu danych
        this.przycisk_wyboru_typu_drzewa = new ChoiceBox<String>();

        this.przycisk_wyboru_typu_drzewa.getItems().add(new String("Typ int"));
        this.przycisk_wyboru_typu_drzewa.getItems().add(new String("Typ double"));
        this.przycisk_wyboru_typu_drzewa.getItems().add(new String("Typ String"));

        this.przycisk_wyboru_typu_drzewa.setValue(new String("Typ int"));
        this.przycisk_wyboru_typu_drzewa.setPrefWidth(100);

        // przycisk sluzacy do dodawania wezla
        this.przycisk_dodania_wezla = new Button("Dodaj wezel");
        this.przycisk_dodania_wezla.setPrefWidth(100);

        // przycisk sluzacy do usuwania wezla
        this.przycisk_usuniecia_wezla = new Button("Usun wezel");
        this.przycisk_usuniecia_wezla.setPrefWidth(100);

        // przycisk sluzacy do wyszukiwania wezla
        this.przycisk_wyszukania_wezla = new Button("Wyszukaj wezel");
        this.przycisk_wyszukania_wezla.setPrefWidth(100);

        this.uklad_przestrzeni_przyciskow.getChildren().addAll(
            this.przycisk_wyboru_typu_drzewa, 
            this.przycisk_dodania_wezla, 
            this.przycisk_usuniecia_wezla, 
            this.przycisk_wyszukania_wezla
            );

        this.uklad_aplikacji.setRight(this.uklad_przestrzeni_przyciskow);
    }

    /**
     * Metoda wykorzystywana przez kontroler do uzyskania przycisku wyboru typu danych.
     * 
     * @return Przycisk wyboru typu danych.
     */
    public ChoiceBox<String> przekazPrzyciskWyboruTypu() {
        return this.przycisk_wyboru_typu_drzewa;
    }

    /**
     * Metoda wykorzystywana przez kontroler do uzyskania przycisku dodania nowego wezla.
     * 
     * @return Przycisk dodania nowego wezla.
     */
    public Button przekazPrzyciskDodawania() {
        return this.przycisk_dodania_wezla;
    }

    /**
     * Metoda wykorzystywana przez kontroler do uzyskania przycisku usuwania wezla.
     * 
     * @return Przycisk usuwania wezla.
     */
    public Button przekazPrzyciskUsuwania() {
        return this.przycisk_usuniecia_wezla;
    }

    /**
     * Metoda wykorzystywana przez kontroler do uzyskania przycisku wyszukiwania wezla.
     * 
     * @return Przycisk wyszukiwania wezla.
     */
    public Button przekazPrzyciskSzukania() {
        return this.przycisk_wyszukania_wezla;
    }

    /**
     * Metoda wykorzystywana przez kontroler do uzyskania przycisku odnowienia polaczenia.
     * 
     * @return Przycisk odnowienia polaczenia.
     */
    public Button przekazPrzyciskOdnowieniaPolaczenia() {
        return this.przycisk_polaczenia;
    }

    /**
     * Metoda wykorzystywana przez kontroler do uzyskania dostepu do przestrzeni, na ktorej wyswietlane jest drzewo.
     * 
     * @return Przestrzen na ktorej wyswietlane jest drzewo.
     */
    public Pane przekazPrzestrzenDrzewa() {
        return this.przestrzen_drzewa;
    }

    /**
     * Metoda ta wyswietla drzewo binarne w odpowiednim obszarze na podstawie danych uzyskanych z serwera.
     * 
     * @param sformatowane_drzewo Sformatowany napis przedstawiajacy wszystkie wiersze drzewa.
     */
    public void wyswietlDrzewo(String sformatowane_drzewo) {
        Platform.runLater(new Runnable() {
            @Override
            public void run() {
                // usuniecie aktualnie wyswietlonego drzewa
                przestrzen_drzewa.getChildren().clear();
                GraficznyWezel wezel;

                String[] rozdzielone_wiersze = sformatowane_drzewo.split("#/#");
                int ilosc_wierszy = rozdzielone_wiersze.length;
                String[][] wiersze = new String[ilosc_wierszy][];
                for(int numer_wiersza = ilosc_wierszy - 1; numer_wiersza >= 0; numer_wiersza--) {
                    wiersze[numer_wiersza] = rozdzielone_wiersze[numer_wiersza].trim().split("\\s+");
                }

                for(int numer_wiersza = ilosc_wierszy - 1; numer_wiersza >= 0; numer_wiersza--) {
                    int ilosc_wartosci = wiersze[numer_wiersza].length;
                    for(int numer_wartosci = 0; numer_wartosci < ilosc_wartosci; numer_wartosci++) {
                        // jesli wartosc jest poprawna, to tworzymy wezel w przestrzeni sluzacej do wyswietlania drzewa
                        if(wiersze[numer_wiersza][numer_wartosci] != null 
                                && !wiersze[numer_wiersza][numer_wartosci].equals("_") 
                                && !wiersze[numer_wiersza][numer_wartosci].equals("EMPTY_TREE")) {
                            wezel = new GraficznyWezel(wiersze, numer_wiersza, numer_wartosci, wiersze[numer_wiersza][numer_wartosci], przestrzen_drzewa);
                            wezel.przesun(aktualna_delta_x, aktualna_delta_y);
                        }
                    }
                }
            }
        });
    }

    /**
     * Metoda sluzaca do zapisania aktualnego przesuniecia wszystkich wyswietlonych wezlow.
     * 
     * @param nowa_delta_x Przesuniecie wzgledem osi X.
     * @param nowa_delta_y Przesuniecie wzgledem osi Y.
     */
    public void podajAktualnePrzesuniecie(double nowa_delta_x, double nowa_delta_y) {
        this.aktualna_delta_x = nowa_delta_x;
        this.aktualna_delta_y = nowa_delta_y;
    }

}
