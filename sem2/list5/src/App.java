import java.io.IOException;

import java.awt.Dimension;
import java.awt.Toolkit;

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
import javafx.event.EventHandler;
import javafx.collections.ObservableList;

public class App extends Application {

    // zmienne pomocnicze dla aplikacji
    private Group root;
    private Scene scena;
    private Pane przestrzenRobocza;
    private BorderPane ukladAplikacji;
    private enum TrybyMyszki {
        KURSOR,
        KOLO, 
        PROSTOKAT, 
        TROJKAT
    }
    private TrybyMyszki aktualnyTrybMyszki = TrybyMyszki.KURSOR;

    // przyciski wyboru figury
    Button przyciskKursora;
    Button przyciskProstokata;
    Button przyciskKola;
    Button przyciskTrojkata;

    // zmienne pomocnicze dla okna
    private int aktualnaSzerokoscOkna = 800;
    private int aktualnaWysokoscOkna = 500;

    // zmienne pomocnicze dla tworzenia ksztaltow
    private double startowaPozycjaMyszkiX;
    private double startowaPozycjaMyszkiY;
    private Polygon tworzonyProstokat;
    private Circle tworzoneKolo;
    private Polygon tworzonyTrojkat;

    // stala dla stylu przycisku nadpisujaca efekt niebieskiej obramowki
    private static final String STYL_PRZYCISKU = """
        -fx-background-color: -fx-shadow-highlight-color, -fx-outer-border, -fx-inner-border, -fx-body-color;
        -fx-background-insets: 0 0 -1 0, 0, 1, 2;
        -fx-background-radius: 5, 5, 4, 3;
            """;

    private static final String STYL_FIGUR_PRZYCISKOW = """
        -fx-fill: white; -fx-stroke: black
            """;

    @Override
    public void start(Stage stage) throws IOException {
        root = new Group();

        scena = new Scene(root, aktualnaSzerokoscOkna, aktualnaWysokoscOkna);

        // uklad aplikacji
        ukladAplikacji = new BorderPane();

        // tworzenie widget'ow aplikacji
        utworzPasekMenu();
        utworzPrzyciski();
        utworzPrzestrzenRobocza();

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

        // przycisk kursora razem z grafika
        przyciskKursora = new Button();
        przyciskKursora.setPrefSize(22, 22);
        przyciskKursora.setDisable(true);
        przyciskKursora.setStyle(STYL_PRZYCISKU);

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

        przyciskKursora.setGraphic(ksztaltKursora);
        przyciskKursora.setOnMouseClicked((new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                uruchomPoprzedniPrzycisk();
                aktualnyTrybMyszki = TrybyMyszki.KURSOR;
                przyciskKursora.setDisable(true);
            }
        }));

        // przycisk prostokata razem z grafika
        przyciskProstokata = new Button();
        przyciskProstokata.setPrefSize(22, 22);

        przyciskProstokata.setStyle(STYL_PRZYCISKU);

        Rectangle ksztaltProstokata = new Rectangle();
        ksztaltProstokata.setX(2.0);
        ksztaltProstokata.setY(2.0);
        ksztaltProstokata.setWidth(16.0);
        ksztaltProstokata.setHeight(16.0);
        ksztaltProstokata.setStyle(STYL_FIGUR_PRZYCISKOW);
        przyciskProstokata.setGraphic(ksztaltProstokata);

        przyciskProstokata.setOnMouseClicked((new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                uruchomPoprzedniPrzycisk();
                aktualnyTrybMyszki = TrybyMyszki.PROSTOKAT;
                przyciskProstokata.setDisable(true);
            }
        }));

        // przycisk kola razem z grafika
        przyciskKola = new Button();
        przyciskKola.setPrefSize(22, 22);
        przyciskKola.setStyle(STYL_PRZYCISKU);

        Circle ksztaltKola = new Circle();
        ksztaltKola.setCenterX(12.0);
        ksztaltKola.setCenterY(12.0);
        ksztaltKola.setRadius(8.0);
        ksztaltKola.setStyle(STYL_FIGUR_PRZYCISKOW);

        przyciskKola.setGraphic(ksztaltKola);

        przyciskKola.setOnMouseClicked((new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                uruchomPoprzedniPrzycisk();
                aktualnyTrybMyszki = TrybyMyszki.KOLO;
                przyciskKola.setDisable(true);
            }
        }));

        // przycisk trojkata razem z grafika
        przyciskTrojkata = new Button();
        przyciskTrojkata.setPrefSize(22, 22);
        przyciskTrojkata.setStyle(STYL_PRZYCISKU);

        Polygon ksztaltTrojkata = new Polygon();
        ksztaltTrojkata.getPoints().addAll(new Double[] {
            9.0, 2.0,
            17.0, 17.0,
            2.0, 17.0
        });
        ksztaltTrojkata.setStyle(STYL_FIGUR_PRZYCISKOW);

        przyciskTrojkata.setGraphic(ksztaltTrojkata);

        przyciskTrojkata.setOnMouseClicked((new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                uruchomPoprzedniPrzycisk();
                aktualnyTrybMyszki = TrybyMyszki.TROJKAT;
                przyciskTrojkata.setDisable(true);
            }
        }));

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

        // przytrzymanie przycisku myszy
        przestrzenRobocza.setOnMousePressed((new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                if(event.isPrimaryButtonDown()) {                
                    startowaPozycjaMyszkiX = event.getX();
                    startowaPozycjaMyszkiY = event.getY();
                    switch(aktualnyTrybMyszki) {
                        case PROSTOKAT: {
                            tworzonyProstokat = new Polygon();
                            przestrzenRobocza.getChildren().add(tworzonyProstokat);
                            tworzonyProstokat.getPoints().addAll(new Double[] {
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
                            tworzonyTrojkat = new Polygon();
                            przestrzenRobocza.getChildren().add(tworzonyTrojkat);
                            tworzonyTrojkat.getPoints().addAll(new Double[] {
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
                System.out.println(event.getPickResult());
            }
        }));

        // przeciagniecie przycisku myszy
        przestrzenRobocza.setOnMouseDragged((new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                if(event.isPrimaryButtonDown()) {
                    switch(aktualnyTrybMyszki) {
                        case PROSTOKAT: {
                            ObservableList<Double> wspolrzedneProstokata = tworzonyProstokat.getPoints();
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
                            ObservableList<Double> wspolrzedneTrojkata = tworzonyTrojkat.getPoints();
                            // zmiana wspolrzednych rogow trokata
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
        }));

        // puszczenie przycisku myszy
        przestrzenRobocza.setOnMouseReleased((new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                switch(aktualnyTrybMyszki) {
                    case PROSTOKAT: {
                        tworzonyProstokat = null;
                        break;
                    }
                    case KOLO: {
                        tworzoneKolo = null;
                        break;
                    }
                    case TROJKAT: {
                        tworzonyTrojkat = null;
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
        }));
    }

    private void uruchomPoprzedniPrzycisk() {
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

    public static void main(String[] args) {
        launch();
    }
    
}
