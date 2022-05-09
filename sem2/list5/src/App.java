import java.io.IOException;
import java.util.function.IntConsumer;

import javafx.application.Application;
import javafx.scene.*;
import javafx.scene.shape.*;
import javafx.stage.Stage;
import javafx.scene.layout.*;
import javafx.scene.control.*;
import javafx.scene.input.*;
import javafx.scene.paint.Color;
import javafx.geometry.*;
import javafx.beans.value.ObservableValue;
import javafx.beans.value.ChangeListener;
import javafx.event.*;
import javafx.collections.ObservableList;

public class App extends Application {

    // zmienne pomocnicze dla aplikacji
    private Group root;
    private Scene scena;
    private Pane przestrzenRobocza;
    private BorderPane ukladAplikacji;

    // przyciski wyboru figury
    private NiestandardowyPrzycisk przyciskKursora;
    private NiestandardowyPrzycisk przyciskProstokata;
    private NiestandardowyPrzycisk przyciskKola;
    private NiestandardowyPrzycisk przyciskTrojkata;

    // zmienne pomocnicze rozmiarow okna
    private int aktualnaSzerokoscOkna = 800;
    private int aktualnaWysokoscOkna = 500;    

    // kontrolery
    KontrolerAplikacji kontrolerAplikacji;

    @Override
    public void start(Stage stage) throws IOException {
        root = new Group();
        scena = new Scene(root, aktualnaSzerokoscOkna, aktualnaWysokoscOkna);

        // uklad aplikacji
        ukladAplikacji = new BorderPane();

        
        // utworzenie kontrolera aplikacji
        kontrolerAplikacji = new KontrolerAplikacji();

        // tworzenie widget'ow aplikacji
        utworzPasekMenu();
        utworzPrzyciski();
        utworzPrzestrzenRobocza();
        
        // odznaczenie wybranej figury
        scena.addEventFilter(MouseEvent.MOUSE_PRESSED, event -> kontrolerAplikacji.usunZaznaczenie(event));

        root.getChildren().add(ukladAplikacji);

        stage.setTitle("Prosty edytor graficzny");
        stage.setScene(scena);
        stage.show();
    }

    private void utworzPasekMenu() {
        // pasek menu
        MenuBar pasekMenu = new MenuBar();
        pasekMenu.setStyle("-fx-view-order: -2");

        // utworzenie przyciskow menu 
        Menu menuPomocy = new Menu("Pomoc");
        MenuItem info = new MenuItem("Info");
        MenuItem instrukcja = new MenuItem("Instrukcja uzytkownika");

        // dodanie przyciskow menu do paska oraz paska menu do ukladu aplikacji
        menuPomocy.getItems().add(info);
        menuPomocy.getItems().add(instrukcja);

        pasekMenu.getMenus().add(menuPomocy);

        ukladAplikacji.setTop(pasekMenu);
    }

    private void utworzPrzyciski() {
        // utworzenie przyciskow odpowiedzialnych za tworzenie figur

        // przycisk kursora
        przyciskKursora = new NiestandardowyPrzycisk("kursor");

        przyciskKursora.setOnMouseClicked(event -> kontrolerAplikacji.zmienTrybMyszki(event, "kursor"));

        // przycisk prostokata
        przyciskProstokata = new NiestandardowyPrzycisk("prostokat");

        przyciskProstokata.setOnMouseClicked(event -> kontrolerAplikacji.zmienTrybMyszki(event, "prostokat"));

        // przycisk kola
        przyciskKola = new NiestandardowyPrzycisk("kolo");

        przyciskKola.setOnMouseClicked(event -> kontrolerAplikacji.zmienTrybMyszki(event, "kolo"));

        // przycisk trojkata
        przyciskTrojkata = new NiestandardowyPrzycisk("trojkat");

        przyciskTrojkata.setOnMouseClicked(event -> kontrolerAplikacji.zmienTrybMyszki(event, "trojkat"));

        // dodanie przyciskow do ukladu VBox
        VBox ukladPrzyciskow = new VBox(przyciskKursora, przyciskProstokata, przyciskKola, przyciskTrojkata);
        ukladPrzyciskow.setStyle("-fx-background-color: #c2c2c2; -fx-border-width: 0 1 1 1; -fx-border-color: black; -fx-view-order: -2");
        ukladPrzyciskow.setSpacing(5);
        ukladPrzyciskow.setMargin(przyciskKursora, new Insets(15, 15, 15, 7));
        ukladPrzyciskow.setMargin(przyciskProstokata, new Insets(15, 7, 15, 6));
        ukladPrzyciskow.setMargin(przyciskKola, new Insets(15, 6, 15, 6));
        ukladPrzyciskow.setMargin(przyciskTrojkata, new Insets(15, 7, 15, 5.5));
        
        // dodanie przestrzeni przyciskow do glownej przestrzeni aplikacji
        ukladAplikacji.setRight(ukladPrzyciskow);

        // przekazanie przyciskow do kontrolera aplikacji
        kontrolerAplikacji.przekazPrzyciski(przyciskKursora, przyciskProstokata, przyciskKola, przyciskTrojkata);
    }

    private void utworzPrzestrzenRobocza() {
        // przestrzen do tworzenia ksztaltow
        przestrzenRobocza = new Pane();
        przestrzenRobocza.setPrefSize(aktualnaSzerokoscOkna - 45, aktualnaWysokoscOkna);
        przestrzenRobocza.setStyle("-fx-background-color: white");
        ukladAplikacji.setCenter(przestrzenRobocza);

        // automatyczna zmiana rozmiaru przestrzeni roboczej 
        scena.widthProperty().addListener((obs, oldVal, newVal) -> {przestrzenRobocza.setPrefWidth(newVal.doubleValue() - 45);});
        scena.heightProperty().addListener((obs, oldVal, newVal) -> {przestrzenRobocza.setPrefHeight(newVal.doubleValue());});

        // wydarzenia na przestrzeni roboczej

        // przytrzymanie przycisku myszy, poczatek tworzenia figury
        przestrzenRobocza.setOnMousePressed(event -> kontrolerAplikacji.nacisnietoMyszkaNaPrzestrzenRobocza(event, przestrzenRobocza));

        // przeciagniecie przycisku myszy
        przestrzenRobocza.setOnMouseDragged(event -> kontrolerAplikacji.przesunietoMyszkeNaPrzestrzeniRoboczej(event));

        // puszczenie przycisku myszy
        przestrzenRobocza.setOnMouseReleased(event -> kontrolerAplikacji.puszczonoPrzyciskNaPrzestrzeniRoboczej(event));
    }

    public static void main(String[] args) {
        launch();
    }
    
};

// klasa odpowiadajaca za utworzenie przyciskow wyboru wykonywanego dzialania w aplikacji
class NiestandardowyPrzycisk extends Button {

    // stala dla stylu przycisku nadpisujaca efekt niebieskiej obramowki
    private static final String STYL_PRZYCISKU = """
        -fx-background-color: -fx-shadow-highlight-color, -fx-outer-border, -fx-inner-border, -fx-body-color;
        -fx-background-insets: 0 0 -1 0, 0, 1, 2;
        -fx-background-radius: 5, 5, 4, 3;
            """;

    // stala dla stylu figur sluzacych jako grafika przyciskow
    private static final String STYL_FIGUR_PRZYCISKOW = """
        -fx-fill: white; -fx-stroke: black
            """;

    NiestandardowyPrzycisk(String rodzaj) {
        super();
        this.setPrefSize(22,22);
        this.setStyle(STYL_PRZYCISKU);
        // utworzenie ksztaltu dla odpowiedniego przycisku
        switch(rodzaj) {
            case "kursor": {
                // utworzenie ksztaltu kursora
                Polygon ksztaltKursora = new Polygon();
                ksztaltKursora.getPoints().addAll(new Double[] {
                    2.0, 2.0,
                    15.0, 15.0, 
                    10.0, 15.0,
                    12.0, 20.0,
                    9.0, 21.0,
                    7.0, 15.0,
                    2.0, 18.0
                });
                ksztaltKursora.setStyle(STYL_FIGUR_PRZYCISKOW);
                this.setGraphic(ksztaltKursora);
                this.setDisable(true);
                break;
            }
            case "prostokat": {
                // utworzenie ksztaltu prostokata
                Rectangle ksztaltProstokata = new Rectangle();
                ksztaltProstokata.setX(2.0);
                ksztaltProstokata.setY(2.0);
                ksztaltProstokata.setWidth(16.0);
                ksztaltProstokata.setHeight(16.0);
                ksztaltProstokata.setStyle(STYL_FIGUR_PRZYCISKOW);
                this.setGraphic(ksztaltProstokata);
                break;
            }
            case "kolo" : {
                // utworzenie ksztaltu kola
                Circle ksztaltKola = new Circle();
                ksztaltKola.setCenterX(12.0);
                ksztaltKola.setCenterY(12.0);
                ksztaltKola.setRadius(8.0);
                ksztaltKola.setStyle(STYL_FIGUR_PRZYCISKOW);

                this.setGraphic(ksztaltKola);
                break;
            }
            case "trojkat" : {
                // utworzenie ksztaltu trojkata
                Polygon ksztaltTrojkata = new Polygon();
                ksztaltTrojkata.getPoints().addAll(new Double[] {
                    9.0, 2.0,
                    17.0, 17.0,
                    2.0, 17.0
                });
                ksztaltTrojkata.setStyle(STYL_FIGUR_PRZYCISKOW);

                this.setGraphic(ksztaltTrojkata);
                break;
            }
            default: {
                break;
            }
        }
        
    }    
};

class KontrolerAplikacji {

    // zmienne pomocnicze dla przyciskow
    private NiestandardowyPrzycisk przyciskKursora;
    private NiestandardowyPrzycisk przyciskProstokata;
    private NiestandardowyPrzycisk przyciskKola;
    private NiestandardowyPrzycisk przyciskTrojkata;

    // zmienne pomocnicze trybu myszki
    private enum TrybyMyszki {
        KURSOR,
        KOLO, 
        PROSTOKAT, 
        TROJKAT
    }
    private TrybyMyszki aktualnyTrybMyszki = TrybyMyszki.KURSOR;

    // zmienne pomocniczne dla tworzonych figur
    private double startowaPozycjaMyszkiX;
    private double startowaPozycjaMyszkiY;
    private Polygon tworzonyWielokat;
    private Circle tworzoneKolo;

    // zmienne pomocniczne dla wybierania i przesuwania ksztaltow
    private Polygon wybranyWielokat = null;
    private Circle wybraneKolo = null;
    private Double startowaPozycjaPrzesuwaniaX;
    private Double startowaPozycjaPrzesuwaniaY;

    // konstruktor
    public void przekazPrzyciski(NiestandardowyPrzycisk przyciskKursora_,
            NiestandardowyPrzycisk przyciskProstokata_,
            NiestandardowyPrzycisk przyciskKola_,
            NiestandardowyPrzycisk przyciskTrojkata_) {
        przyciskKursora = przyciskKursora_;
        przyciskProstokata = przyciskProstokata_;
        przyciskKola = przyciskKola_;
        przyciskTrojkata = przyciskTrojkata_;
    }

    // usuniecie zaznaczenia z wybranej wczesniej figury
    public void usunZaznaczenie(MouseEvent event) {
        if(wybranyWielokat != null) {
            wybranyWielokat.setStroke(null);
            wybranyWielokat = null;
        }
        if(wybraneKolo != null) {
            wybraneKolo.setStroke(null);
            wybraneKolo = null;
        }
    }

    // powrotne uruchomienie poprzedniego przycisku po utworzeniu figury
    public void uruchomPoprzedniPrzycisk() {
        switch(aktualnyTrybMyszki) {
            case KURSOR:
                przyciskKursora.setDisable(false);
                break;
            case PROSTOKAT:
                przyciskProstokata.setDisable(false);
                break;
            case KOLO:
                przyciskKola.setDisable(false);
                break;
            case TROJKAT:
                przyciskTrojkata.setDisable(false);
                break;
        }
    }

    // zmiana trybu myszki na wybrana z przycisku figure
    public void zmienTrybMyszki(MouseEvent event, String figura) {
        uruchomPoprzedniPrzycisk();
        switch(figura) {
            case "kursor":
                aktualnyTrybMyszki = TrybyMyszki.KURSOR;
                przyciskKursora.setDisable(true);
                break;
            case "prostokat":
                aktualnyTrybMyszki = TrybyMyszki.PROSTOKAT;
                przyciskProstokata.setDisable(true);
                break;
            case "kolo":
                aktualnyTrybMyszki = TrybyMyszki.KOLO;
                przyciskKola.setDisable(true);
                break;
            case "trojkat":
                aktualnyTrybMyszki = TrybyMyszki.TROJKAT;
                przyciskTrojkata.setDisable(true);
                break;
            default:
                break;
        }
    }

    public void nacisnietoMyszkaNaPrzestrzenRobocza(MouseEvent event, Pane przestrzenRobocza) {
        if(event.isPrimaryButtonDown()) {                
            startowaPozycjaMyszkiX = event.getX();
            startowaPozycjaMyszkiY = event.getY();
            switch(aktualnyTrybMyszki) {
                case PROSTOKAT: {
                    tworzonyWielokat = new Polygon();
                    przestrzenRobocza.getChildren().add(tworzonyWielokat);
                    tworzonyWielokat.getPoints().addAll(new Double[] {
                        startowaPozycjaMyszkiX, startowaPozycjaMyszkiY,
                        startowaPozycjaMyszkiX, startowaPozycjaMyszkiY,
                        startowaPozycjaMyszkiX, startowaPozycjaMyszkiY,
                        startowaPozycjaMyszkiX, startowaPozycjaMyszkiY
                    });
                    break;
                }
                case KOLO: {
                    tworzoneKolo = new Circle();
                    przestrzenRobocza.getChildren().add(tworzoneKolo);
                    tworzoneKolo.setCenterX(startowaPozycjaMyszkiX);
                    tworzoneKolo.setCenterY(startowaPozycjaMyszkiY);
                    break;
                }
                case TROJKAT: {
                    tworzonyWielokat = new Polygon();
                    przestrzenRobocza.getChildren().add(tworzonyWielokat);
                    tworzonyWielokat.getPoints().addAll(new Double[] {
                        startowaPozycjaMyszkiX, startowaPozycjaMyszkiY,
                        startowaPozycjaMyszkiX, startowaPozycjaMyszkiY,
                        startowaPozycjaMyszkiX, startowaPozycjaMyszkiY
                    });
                    break;
                }
                default:
                    break;
            }
        }
    }

    // obsluga przesuwania myszki przy tworzeniu nowej figury
    public void przesunietoMyszkeNaPrzestrzeniRoboczej(MouseEvent event) {
        if(event.isPrimaryButtonDown()) {
            switch(aktualnyTrybMyszki) {
                case PROSTOKAT: {
                    ObservableList<Double> wspolrzedneProstokata = tworzonyWielokat.getPoints();
                    // zmiana wspolrzednych rogow prostokata
                    wspolrzedneProstokata.set(2, event.getX());

                    wspolrzedneProstokata.set(4, event.getX());
                    wspolrzedneProstokata.set(5, event.getY());
                    
                    wspolrzedneProstokata.set(7, event.getY());
                    break;
                }
                case KOLO: {
                    double wiekszaWartosc = Math.abs(event.getX() - startowaPozycjaMyszkiX) >=
                    Math.abs(event.getY() - startowaPozycjaMyszkiY) ?
                    Math.abs(event.getX() - startowaPozycjaMyszkiX) : Math.abs(event.getY() - startowaPozycjaMyszkiY);
                    tworzoneKolo.setRadius(wiekszaWartosc);
                    break;
                }
                case TROJKAT: {
                    ObservableList<Double> wspolrzedneTrojkata = tworzonyWielokat.getPoints();
                    // zmiana wspolrzednych rogow trojkata
                    wspolrzedneTrojkata.set(1, event.getY());
                    wspolrzedneTrojkata.set(2, (startowaPozycjaMyszkiX + event.getX()) / 2);
                    wspolrzedneTrojkata.set(4, event.getX());
                    wspolrzedneTrojkata.set(5, event.getY());
                    break;
                }
                default: 
                    break;
            }
        }
    }

    // obsluga wyczyszczenia zmiennych po utworzeniu nowej figury
    public void puszczonoPrzyciskNaPrzestrzeniRoboczej(MouseEvent event) {
        switch(aktualnyTrybMyszki) {
            case KURSOR: {
                break;
            }
            case KOLO: {
                // dodanie funkcji przy nacisnieciu myszki na figurze
                tworzoneKolo.setOnMousePressed(mouseEvent -> this.wybranoFigure(mouseEvent));
                
                // dodanie funkcji przy przesunieciu figury
                tworzoneKolo.setOnMouseDragged(mouseEvent -> this.przesunietoFigure(mouseEvent));

                // dodanie funkcji przy uzywaniu scrolla na figurze
                tworzoneKolo.setOnScroll(mouseEvent -> this.uzytoScrollaNaFigurze(mouseEvent));
                
                tworzoneKolo = null;
                break;
            }
            default: {
                // dodanie funkcji przy nacisnieciu myszki na figurze
                tworzonyWielokat.setOnMousePressed(mouseEvent -> this.wybranoFigure(mouseEvent));
                
                // dodanie funkcji przy przesunieciu figury
                tworzonyWielokat.setOnMouseDragged(mouseEvent -> this.przesunietoFigure(mouseEvent));

                // dodanie funkcji przy uzywaniu srolla na figure
                tworzonyWielokat.setOnScroll(mouseEvent -> this.uzytoScrollaNaFigurze(mouseEvent));

                
                tworzonyWielokat = null;
                break;
            }
        }
        uruchomPoprzedniPrzycisk();
        przyciskKursora.setDisable(true);
        aktualnyTrybMyszki = TrybyMyszki.KURSOR;
    }

    // obsluga wyboru jednej z utworzonych figur
    public void wybranoFigure(MouseEvent event) {
        if(aktualnyTrybMyszki == TrybyMyszki.KURSOR && event.isPrimaryButtonDown()) {
            startowaPozycjaPrzesuwaniaX = event.getSceneX();
            startowaPozycjaPrzesuwaniaY = event.getSceneY();
            if(event.getTarget() instanceof Polygon) {
                wybranyWielokat = (Polygon)event.getTarget();
            
                // dodanie ramki
                wybranyWielokat.setStroke(Color.BLUE);
                wybranyWielokat.setStrokeWidth(4);
                wybranyWielokat.getStrokeDashArray().addAll(8.0);
                wybranyWielokat.toFront();
            }
            else if(event.getTarget() instanceof Circle) {
                wybraneKolo = (Circle)event.getTarget();

                // dodanie ramki
                wybraneKolo.setStroke(Color.BLUE);
                wybraneKolo.setStrokeWidth(4);
                wybraneKolo.getStrokeDashArray().addAll(8.0);
                wybraneKolo.toFront();
            }
        }
    } 

    // obsluga przesuwania wybranej figury
    public void przesunietoFigure(MouseEvent event) {
        if(aktualnyTrybMyszki == TrybyMyszki.KURSOR && event.isPrimaryButtonDown()) {
            // obliczenie przesuniecia myszki i zaktualizowanie nowej pozycji do kolejnych obliczen
            double roznicaX = event.getSceneX() - startowaPozycjaPrzesuwaniaX;
            double roznicaY = event.getSceneY() - startowaPozycjaPrzesuwaniaY;
            startowaPozycjaPrzesuwaniaX = event.getSceneX();
            startowaPozycjaPrzesuwaniaY = event.getSceneY();

            // wybor odpowiedniej figury do przesuniecia
            if(wybraneKolo != null) {
                wybraneKolo.setCenterX(wybraneKolo.getCenterX() + roznicaX);
                wybraneKolo.setCenterY(wybraneKolo.getCenterY() + roznicaY);
            }
            else if(wybranyWielokat != null) {
                ObservableList<Double> listaWspolrzednych = wybranyWielokat.getPoints();
                for(int i=0; i < listaWspolrzednych.size(); i += 2) {
                    listaWspolrzednych.set(i, listaWspolrzednych.get(i) + roznicaX);
                    listaWspolrzednych.set(i + 1, listaWspolrzednych.get(i+1) + roznicaY);
                }
            }
        }
    }

    // funkcja odpowiedzialna za powiekszenie wybranego trojkata
    public void powiekszTrojkat(double wartosc, ObservableList<Double> listaWspolrzednych) {
        // okreslenie w ktora strone zbudowana zostala figura
        int wspolczynnikRozrostuFiguryY = listaWspolrzednych.get(1) > listaWspolrzednych.get(3) ? 1 : -1;
        int wspolczynnikRozrostuFiguryX = listaWspolrzednych.get(0) < listaWspolrzednych.get(4) ? 1 : -1;

        // przesuniecie wspolrzednych
        listaWspolrzednych.set(0, listaWspolrzednych.get(0) + (wartosc * wspolczynnikRozrostuFiguryX * 0.5));
        listaWspolrzednych.set(1, listaWspolrzednych.get(1) + (wartosc * wspolczynnikRozrostuFiguryY * -0.5));                                        
        listaWspolrzednych.set(3, listaWspolrzednych.get(3) + (wartosc * wspolczynnikRozrostuFiguryY * 0.5));
        listaWspolrzednych.set(4, listaWspolrzednych.get(4) + (wartosc * wspolczynnikRozrostuFiguryX * -0.5));
        listaWspolrzednych.set(5, listaWspolrzednych.get(5) + (wartosc * wspolczynnikRozrostuFiguryY * -0.5));
    }

    // funkcja odpowiedzialna za powiekszenie wybranego prostokata
    public void powiekszProstokat(double wartosc, ObservableList<Double> listaWspolrzednych) {
        // okreslenie w ktora strone zbudowana zostala figura
        int wspolczynnikRozrostuFiguryY = listaWspolrzednych.get(1) < listaWspolrzednych.get(7) ? 1 : -1;
        int wspolczynnikRozrostuFiguryX = listaWspolrzednych.get(0) < listaWspolrzednych.get(2) ? 1 : -1;

        // przesuniecie wspolrzednych
        listaWspolrzednych.set(0, listaWspolrzednych.get(0) + (wartosc * wspolczynnikRozrostuFiguryX * 0.5));
        listaWspolrzednych.set(1, listaWspolrzednych.get(1) + (wartosc * wspolczynnikRozrostuFiguryY * 0.5));
        listaWspolrzednych.set(2, listaWspolrzednych.get(2) + (wartosc * wspolczynnikRozrostuFiguryX * -0.5));
        listaWspolrzednych.set(3, listaWspolrzednych.get(3) + (wartosc * wspolczynnikRozrostuFiguryY * 0.5));
        listaWspolrzednych.set(4, listaWspolrzednych.get(4) + (wartosc * wspolczynnikRozrostuFiguryX * -0.5));
        listaWspolrzednych.set(5, listaWspolrzednych.get(5) + (wartosc * wspolczynnikRozrostuFiguryY * -0.5));
        listaWspolrzednych.set(6, listaWspolrzednych.get(6) + (wartosc * wspolczynnikRozrostuFiguryX *0.5));
        listaWspolrzednych.set(7, listaWspolrzednych.get(7) + (wartosc * wspolczynnikRozrostuFiguryY * -0.5));
    }

    // obsluga powiekszania i pomniejszania figury za pomoca scroll'a
    public void uzytoScrollaNaFigurze(ScrollEvent scrollEvent) {
        if(aktualnyTrybMyszki == TrybyMyszki.KURSOR) {
            if(wybranyWielokat == scrollEvent.getTarget() && wybranyWielokat.getPoints().size() == 8) {
                powiekszProstokat(scrollEvent.getDeltaY(), wybranyWielokat.getPoints());
                
            }
            if(wybraneKolo == scrollEvent.getTarget()) {
                wybraneKolo.setRadius(wybraneKolo.getRadius() + (scrollEvent.getDeltaY() * -0.5));
            }
            if(wybranyWielokat == scrollEvent.getTarget() && wybranyWielokat.getPoints().size() == 6) {
                this.powiekszTrojkat(scrollEvent.getDeltaY(), wybranyWielokat.getPoints());
            }
        }
    }



}
