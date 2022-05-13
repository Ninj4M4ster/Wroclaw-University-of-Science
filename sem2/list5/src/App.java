import java.io.IOException;

import javafx.application.Application;
import javafx.scene.*;
import javafx.scene.shape.*;
import javafx.stage.Stage;
import javafx.scene.layout.*;
import javafx.scene.control.*;
import javafx.scene.input.*;
import javafx.scene.paint.Color;
import javafx.scene.transform.*;
import javafx.geometry.*;
import javafx.beans.value.ObservableValue;
import javafx.beans.value.ChangeListener;
import javafx.event.*;
import javafx.collections.ObservableList;

/**
 * Klasa aplikacji odpowiedzialna za uruchomienie wszystkich procesow potrzebnych do jej poprawnego funkcjonowania.
 * 
 * @author Jakub Drzewiecki
 */
public class App extends Application {

    // zmienne pomocnicze dla aplikacji
    private Scene scena;
    private BorderPane ukladAplikacji;
    private Pane przestrzenRobocza;

    // zmienne pomocnicze rozmiarow okna
    private int aktualnaSzerokoscOkna = 800;
    private int aktualnaWysokoscOkna = 500;    

    // kontrolery
    KontrolerAplikacji kontrolerAplikacji;

    /** 
     * Konstruktor, uruchamia wszystkie funkcje tworzace aplikacje.
     * 
     * @see App#utworzPasekMenu
     * @see App#utworzPrzyciski
     * @see App#utworzPrzestrzenRobocza
     * @see KontrolerAplikacji#usunZaznaczenie
     */
    @Override
    public void start(Stage stage) throws IOException {
        Group root = new Group();
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
        scena.addEventFilter(MouseEvent.MOUSE_PRESSED, event -> kontrolerAplikacji.usunZaznaczenie(event, przestrzenRobocza));

        root.getChildren().add(ukladAplikacji);

        stage.setTitle("Prosty edytor graficzny");
        stage.setScene(scena);
        stage.show();
    }

    /**
     * Funkcja odpowiedzialna za utworzenie paska menu z mozliwoscia wyswietlenia informaji o aplikacji oraz 
     * instrukcji uzytkownika
     * 
     * @see KontrolerAplikacji#wyswietlInformacje
     * @see KontrolerAplikacji#wyswietlInstrukcjeUzytkownika
     */
    private void utworzPasekMenu() {
        // pasek menu
        MenuBar pasekMenu = new MenuBar();
        pasekMenu.setStyle("-fx-view-order: -2");

        // utworzenie przyciskow menu 
        Menu menuPomocy = new Menu("Pomoc");
        MenuItem info = new MenuItem("Info");
        info.setOnAction(event -> kontrolerAplikacji.wyswietlInformacje(event));

        MenuItem instrukcja = new MenuItem("Instrukcja uzytkownika");
        instrukcja.setOnAction(event -> kontrolerAplikacji.wyswietlInstrukcjeUzytkownika(event));

        // dodanie przyciskow menu do paska oraz paska menu do ukladu aplikacji
        menuPomocy.getItems().add(info);
        menuPomocy.getItems().add(instrukcja);

        pasekMenu.getMenus().add(menuPomocy);

        ukladAplikacji.setTop(pasekMenu);
    }

    /**
     * Funkcja odpowiedzialna za utworzenie przyciskow wyboru tworzonej figury oraz koloru.
     * 
     * @see NiestandardowyPrzycisk
     * @see KontrolerAplikacji#zmienTrybMyszki
     * @see KontrolerAplikacji#przekazPrzyciski
     * @see KontrolerAplikacji#ustawKolor
     */
    private void utworzPrzyciski() {
        // utworzenie przyciskow odpowiedzialnych za tworzenie figur

        // przycisk kursora
        NiestandardowyPrzycisk przyciskKursora = new NiestandardowyPrzycisk("kursor");

        przyciskKursora.setOnMouseClicked(
            event -> kontrolerAplikacji.zmienTrybMyszki(event, "kursor"));

        // przycisk prostokata
        NiestandardowyPrzycisk przyciskProstokata = new NiestandardowyPrzycisk("prostokat");

        przyciskProstokata.setOnMouseClicked(
            event -> kontrolerAplikacji.zmienTrybMyszki(event, "prostokat"));

        // przycisk kola
        NiestandardowyPrzycisk przyciskKola = new NiestandardowyPrzycisk("kolo");

        przyciskKola.setOnMouseClicked(event -> kontrolerAplikacji.zmienTrybMyszki(event, "kolo"));

        // przycisk trojkata
        NiestandardowyPrzycisk przyciskTrojkata = new NiestandardowyPrzycisk("trojkat");

        przyciskTrojkata.setOnMouseClicked(
            event -> kontrolerAplikacji.zmienTrybMyszki(event, "trojkat"));

        // przycisk palety kolorow
        ColorPicker wyborKoloru = new ColorPicker(Color.BLACK);
        wyborKoloru.setStyle("""
            -fx-text-visibility: false;
            """);

        wyborKoloru.setOnAction(e -> KontrolerAplikacji.ustawKolor(e, wyborKoloru));

        // dodanie przyciskow do ukladu VBox
        VBox ukladPrzyciskow = new VBox(przyciskKursora, przyciskProstokata,
                                        przyciskKola, przyciskTrojkata, wyborKoloru);
        ukladPrzyciskow.setStyle("""
            -fx-background-color: #c2c2c2; -fx-border-width: 0 1 1 1; 
            -fx-border-color: black; -fx-view-order: -2
            """);
        ukladPrzyciskow.setSpacing(5);
        ukladPrzyciskow.setMargin(przyciskKursora, new Insets(15, 15, 15, 7));
        ukladPrzyciskow.setMargin(przyciskProstokata, new Insets(15, 7, 15, 6));
        ukladPrzyciskow.setMargin(przyciskKola, new Insets(15, 6, 15, 6));
        ukladPrzyciskow.setMargin(przyciskTrojkata, new Insets(15, 7, 15, 5.5));
        ukladPrzyciskow.setMargin(wyborKoloru, new Insets(15, 7, 15, 5.5));
        
        // dodanie przestrzeni przyciskow do glownej przestrzeni aplikacji
        ukladAplikacji.setRight(ukladPrzyciskow);

        // przekazanie przyciskow do kontrolera aplikacji
        kontrolerAplikacji.przekazPrzyciski(przyciskKursora, przyciskProstokata, 
                                            przyciskKola, przyciskTrojkata);
    }

    /**
     * Funkcja odpowiedzialna za utworzenie przestrzeni roboczej aplikacji, czyli obszaru,
     * w ktorym uzytkownik tworzyc bedzie figury.
     * Funkcja ta przypisuje rowniez funkcje obslugujace wydarzenia przestrzeni oraz dodaje obsluge zmieniania
     * rozmiaru obszaru roboczego przy zmienianiu wielkosci calego okna.
     * 
     * @see KontrolerAplikacji#nacisnietoMyszkaNaPrzestrzenRobocza
     * @see KontrolerAplikacji#przesunietoMyszkeNaPrzestrzeniRoboczej
     * @see KontrolerAplikacji#puszczonoPrzyciskNaPrzestrzeniRoboczej
     */
    private void utworzPrzestrzenRobocza() {
        // przestrzen do tworzenia ksztaltow
        przestrzenRobocza = new Pane();
        przestrzenRobocza.setPrefSize(aktualnaSzerokoscOkna - 140, aktualnaWysokoscOkna);
        przestrzenRobocza.setStyle("-fx-background-color: white");
        ukladAplikacji.setCenter(przestrzenRobocza);

        // automatyczna zmiana rozmiaru przestrzeni roboczej 
        scena.widthProperty().addListener((obs, oldVal, newVal) -> 
            przestrzenRobocza.setPrefWidth(newVal.doubleValue() - 140));
        scena.heightProperty().addListener((obs, oldVal, newVal) -> 
            przestrzenRobocza.setPrefHeight(newVal.doubleValue()));

        // wydarzenia na przestrzeni roboczej

        // przytrzymanie przycisku myszy, poczatek tworzenia figury
        przestrzenRobocza.setOnMousePressed(event -> 
            kontrolerAplikacji.nacisnietoMyszkaNaPrzestrzenRobocza(event, przestrzenRobocza));

        // przeciagniecie przycisku myszy
        przestrzenRobocza.setOnMouseDragged(event -> 
            kontrolerAplikacji.przesunietoMyszkeNaPrzestrzeniRoboczej(event));

        // puszczenie przycisku myszy
        przestrzenRobocza.setOnMouseReleased(event -> 
            kontrolerAplikacji.puszczonoPrzyciskNaPrzestrzeniRoboczej(event, przestrzenRobocza));
    }

    public static void main(String[] args) {
        launch();
    }
    
}
