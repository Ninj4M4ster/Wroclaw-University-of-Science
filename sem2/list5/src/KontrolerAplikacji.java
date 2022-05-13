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
 * Klasa odpowiedzialna za obsluge wszystkich wydarzen w aplikacji.
 */
class KontrolerAplikacji {

    // zmienne pomocnicze dla przyciskow
    private NiestandardowyPrzycisk przyciskKursora;
    private NiestandardowyPrzycisk przyciskProstokata;
    private NiestandardowyPrzycisk przyciskKola;
    private NiestandardowyPrzycisk przyciskTrojkata;

    /**
     * Klasa przechowujaca wartosci jednoznacznie wyznaczajace aktualny tryb myszy.
     */
    private enum TrybyMyszki {
        KURSOR,
        KOLO, 
        PROSTOKAT, 
        TROJKAT
    }
    private TrybyMyszki aktualnyTrybMyszki = TrybyMyszki.KURSOR;

    // zmienne pomocnicze dla tworzonych figur
    private double startowaWspolrzednaX;
    private double startowaWspolrzednaY;
    private Polygon tworzonyWielokat;
    private Circle tworzoneKolo;

    // zmienne pomocnicze dla modyfikowania figur
    private Polygon wybranyWielokat = null;
    private Circle wybraneKolo = null;
    private Double wspolrzednaXPrzesuwanejFigury;
    private Double wspolrzednaYPrzesuwanejFigury;

    // zmienne pomocnicze przy obracaniu figur
    private Polygon prostokatDoObrotu = null;
    private double centrXObracanejFigury;
    private double centrYObracanejFigury;

    // zmienna do zmiany koloru
    public static Color wybranyKolor = Color.BLACK;

    /**
     * Funkcja odpowiedzialna za wyswietlenie informacji o programie oraz autorze.
     * 
     * @param event Wydarzenie wywolane przez wybranie jednego z opcji w menu.
     */
    public void wyswietlInformacje(ActionEvent event) {
        Alert komunikat = new Alert(Alert.AlertType.INFORMATION);
        komunikat.setTitle("Informacje");
        komunikat.setHeaderText(null);
        komunikat.setContentText("""
                Prosty edytor graficzny.

                Program sluzy do tworzenia oraz modyfikowania 
                figur geometrycznych: prostokata, kola i trojkata.
                Autor: Jakub Drzewiecki.
            """);

        komunikat.showAndWait();
    }

    /**
     * Funkcja odpowiedzialna za wyswietlenie instrukcji uzytkownika.
     * 
     * @param event Wydarzenie wywolane przez wybranie jednego z opcji w menu.
     */
    public void wyswietlInstrukcjeUzytkownika(ActionEvent event) {
        Alert komunikat = new Alert(Alert.AlertType.INFORMATION);
        komunikat.setTitle("Instrukcja uzytkownika");
        komunikat.setHeaderText(null);
        komunikat.setContentText("""
                W celu utworzenia figury wybierz jedna z figur 
                na panelu bocznym, a nastepnie nacisnij i 
                przytrzymaj lewy przycisk myszy na przestrzeni 
                w centralnej czesci aplikacji i utworz wybrana 
                figure przeciagajac i finalnie puszczajac lewy 
                przycisk myszy.


                W celu modyfikacji jednej z utworzonych figur, 
                wybierz przycisk z ikona kursora oraz nacisnij 
                na wybrana figure. Mozliwe dzialania to:

                - zmiana pozycji figury - nacisnij i przytrzymaj 
                lewy przycisk myszy na wybranej figurze, 
                a nastepnie przeciagnij myszka w wybrane 
                miejsce na ekranie i pusc lewy przycisk myszy,

                - zmiana rozmiaru figury - nacisnij lewym 
                przyciskiem myszy na wybrana figure, 
                pozostaw kursor na wybranej figurze 
                oraz za pomoca rolki myszy powieksz lub 
                pomniejsz figure (przewijajac w gore lub w dol),

                - zmiana koloru figury - wybierz na palecie 
                docelowy kolor, nacisnij lewym przyciskiem 
                myszy na figure, ktora chcesz pomalowac,
                a nastepnie nacisnj na nia prawym przyciskiem
                myszy,

                - obrot figury - nacisnij lewym przyciskiem myszy 
                na wybrana figure, a nastepnie nacisnij i 
                przytrzymaj lewy przycisk myszy na kwadracie 
                wyswietlonym nad figura, po czym obroc figure 
                obracajac mysz wokol figury, a na koniec pusc 
                lewy przycisk myszy.
            """);
        komunikat.showAndWait();
    }

    /**
     * Funkcja odpowiedzialna za przypisanie zmiennym powstalych w aplikacji przyciskow.
     * 
     * @param przyciskKursora_ Przycisk odpowiedzialny za zmiane trybu myszki na kursor.
     * @param przyciskProstokata_ Przycisk odpowiedzialny za zmiane trybu myszki na tworzenie prostokata.
     * @param przyciskKola_ Przycisk odpowiedzialny za zmiane trybu myszki na tworzenie kola.
     * @param przyciskTrojkata_ Przycisk odpowiedzialny za zmiane trybu myszki na tworzenie trojkata.
     */
    public void przekazPrzyciski(NiestandardowyPrzycisk przyciskKursora_,
            NiestandardowyPrzycisk przyciskProstokata_,
            NiestandardowyPrzycisk przyciskKola_,
            NiestandardowyPrzycisk przyciskTrojkata_) {
        przyciskKursora = przyciskKursora_;
        przyciskProstokata = przyciskProstokata_;
        przyciskKola = przyciskKola_;
        przyciskTrojkata = przyciskTrojkata_;
    }

    /**
     * Funkcja ta jest odpowiedzialna za zmiane wartosci zmiennej przechowujacej
     * kolor wybrany przez uzytkownika.
     * 
     * @param event Wydarzenie wywolane przez wybranie koloru z palety.
     * @param wyborKoloru Element aplikacji, na ktorym wybiera sie kolor.
     */
    public static void ustawKolor(ActionEvent event, ColorPicker wyborKoloru) {
        wybranyKolor = wyborKoloru.getValue();
    }

    /**
     * Funkcja odpowiedzialna za obsluge usuniecia zaznaczenia z wybranej przez uzytkownika wczesniej figury.
     * 
     * @param event Wydarzenie wywolane przez nacisniecie przycisku myszy.
     * @param przestrzenRobocza Przestrzen na ktorej tworzone sa figury.
     */
    public void usunZaznaczenie(MouseEvent event, Pane przestrzenRobocza) {
        if(wybraneKolo != null) {
            // sprawdz czy nie kliknieto wybranej figury
            if(event.getTarget() instanceof Circle &&
            (Circle)event.getTarget() == wybraneKolo)
                return;
            // usuniecie obramowki
            wybraneKolo.setStroke(Color.BLACK);
            wybraneKolo.setStrokeWidth(1);
            wybraneKolo.getStrokeDashArray().removeAll(8.0);
            wybraneKolo = null;
        }
        if(wybranyWielokat != null && prostokatDoObrotu != null) {
            // sprawdz czy nie kliknieto wybranej figury
            if(event.getTarget() instanceof Polygon &&
              (Polygon)event.getTarget() == wybranyWielokat ||
              event.getTarget() instanceof Polygon &&
              (Polygon)event.getTarget() == prostokatDoObrotu)
                return;
            // usuniecie obramowki
            wybranyWielokat.setStroke(Color.BLACK);
            wybranyWielokat.setStrokeWidth(1);
            wybranyWielokat.getStrokeDashArray().removeAll(8.0);
            wybranyWielokat = null;

            // usuniecie prostokatu do obracania
            przestrzenRobocza.getChildren().remove(prostokatDoObrotu);
            prostokatDoObrotu = null;
        }
    }

    /**
     * Funkcja odpowiedzialna za powrotne uruchomienie wylaczonego przycisku po utworzeniu przez uzytkownika nowej figury.
     */
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

    /**
     * Funkcja odpowiadajac za zmiane trybu myszy po nacisnieciu jednego z przyciskow wyboru figury.
     * 
     * @see KontrolerAplikacji#uruchomPoprzedniPrzycisk
     * @param event Wydarzenie wywolane przez nacisniecie przycisku myszy.
     * @param figura Ciag znakow jednoznacznie wyznaczajacy nacisniety przycisk wyboru figury.
     */
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

    /**
     * Funkcja odpowiadajaca za obsluge nacisniecia mysza na obszar roboczy w celu utworzenia nowej figury.
     * 
     * @param event Wydarzenie wywolane przez nacisniecie przycisku myszy.
     * @param przestrzenRobocza Przestrzen w ktorej uzytkownik tworzy figury.
     */
    public void nacisnietoMyszkaNaPrzestrzenRobocza(MouseEvent event, Pane przestrzenRobocza) {
        if(event.isPrimaryButtonDown()) {                
            startowaWspolrzednaX = event.getX();
            startowaWspolrzednaY = event.getY();
            switch(aktualnyTrybMyszki) {
                case PROSTOKAT: {
                    tworzonyWielokat = new Polygon();
                    przestrzenRobocza.getChildren().add(tworzonyWielokat);
                    tworzonyWielokat.getPoints().addAll(new Double[] {
                        startowaWspolrzednaX, startowaWspolrzednaY,
                        startowaWspolrzednaX, startowaWspolrzednaY,
                        startowaWspolrzednaX, startowaWspolrzednaY,
                        startowaWspolrzednaX, startowaWspolrzednaY
                    });
                    tworzonyWielokat.setFill(Color.YELLOW);
                    tworzonyWielokat.setStroke(Color.BLACK);
                    break;
                }
                case KOLO: {
                    tworzoneKolo = new Circle();
                    przestrzenRobocza.getChildren().add(tworzoneKolo);
                    tworzoneKolo.setCenterX(startowaWspolrzednaX);
                    tworzoneKolo.setCenterY(startowaWspolrzednaY);
                    tworzoneKolo.setFill(Color.ORANGE);
                    tworzoneKolo.setStroke(Color.BLACK);
                    break;
                }
                case TROJKAT: {
                    tworzonyWielokat = new Polygon();
                    przestrzenRobocza.getChildren().add(tworzonyWielokat);
                    tworzonyWielokat.getPoints().addAll(new Double[] {
                        startowaWspolrzednaX, startowaWspolrzednaY,
                        startowaWspolrzednaX, startowaWspolrzednaY,
                        startowaWspolrzednaX, startowaWspolrzednaY
                    });
                    tworzonyWielokat.setFill(Color.GREEN);
                    tworzonyWielokat.setStroke(Color.BLACK);
                    break;
                }
                default:
                    break;
            }
        }
    }

    /**
     * Funkcja odpowiadajaca za obsluge przesuwania myszki w trakcie tworzenia figury.
     * 
     * @param event Wydarzenie wywolane przez przesuwanie myszy w trakcie trzymania przycisku.
     */
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
                    double wiekszaWartosc = Math.abs(event.getX() - startowaWspolrzednaX) >=
                        Math.abs(event.getY() - startowaWspolrzednaY) ?
                            Math.abs(event.getX() - startowaWspolrzednaX) : 
                                Math.abs(event.getY() - startowaWspolrzednaY);

                    // zmiana promienia kola
                    tworzoneKolo.setRadius(wiekszaWartosc);
                    break;
                }
                case TROJKAT: {
                    ObservableList<Double> wspolrzedneTrojkata = tworzonyWielokat.getPoints();
                    // zmiana wspolrzednych rogow trojkata
                    wspolrzedneTrojkata.set(1, event.getY());
                    wspolrzedneTrojkata.set(2, (startowaWspolrzednaX + event.getX()) / 2);
                    wspolrzedneTrojkata.set(4, event.getX());
                    wspolrzedneTrojkata.set(5, event.getY());
                    break;
                }
                default: 
                    break;
            }
        }
    }

    /**
     * Funkcja odpowiadajaca za obsluge usuniecia wartosci zmiennych po utworzeniu figury oraz 
     * dodanie obslugi wydarzen do nowej figury.
     * 
     * @see KontrolerAplikacji#wybranoFigure
     * @see KontrolerAplikacji#przesunietoFigure
     * @see KontrolerAplikacji#uzytoScrollaNaFigurze
     * @see KontrolerAplikacji#uruchomPoprzedniPrzycisk
     * @param event Wydarzenie wywolane przez puszczenie przycisku myszy.
     * @param przestrzenRobocza Przestrzen na ktorej tworzone sa figury.
     */
    public void puszczonoPrzyciskNaPrzestrzeniRoboczej(MouseEvent event, Pane przestrzenRobocza) {
        switch(aktualnyTrybMyszki) {
            case KURSOR: {
                break;
            }
            case KOLO: {
                // dodanie funkcji przy nacisnieciu myszki na figurze
                tworzoneKolo.setOnMousePressed(mouseEvent -> this.wybranoFigure(mouseEvent, przestrzenRobocza));
                
                // dodanie funkcji przy przesunieciu figury
                tworzoneKolo.setOnMouseDragged(mouseEvent -> this.przesunietoFigure(mouseEvent));

                // dodanie funkcji przy uzywaniu scrolla na figurze
                tworzoneKolo.setOnScroll(scrollEvent -> this.uzytoScrollaNaFigurze(scrollEvent, przestrzenRobocza));
                
                tworzoneKolo = null;
                break;
            }
            default: {
                // dodanie funkcji przy nacisnieciu myszki na figurze
                tworzonyWielokat.setOnMousePressed(mouseEvent -> this.wybranoFigure(mouseEvent, przestrzenRobocza));
                
                // dodanie funkcji przy przesunieciu figury
                tworzonyWielokat.setOnMouseDragged(mouseEvent -> 
                    this.przesunietoFigure(mouseEvent));

                // dodanie funkcji przy uzywaniu srolla na figure
                tworzonyWielokat.setOnScroll(scrollEvent -> this.uzytoScrollaNaFigurze(scrollEvent, przestrzenRobocza));

                tworzonyWielokat = null;
                break;
            }
        }
        uruchomPoprzedniPrzycisk();
        przyciskKursora.setDisable(true);
        aktualnyTrybMyszki = TrybyMyszki.KURSOR;
    }

    /**
     * Funkcja obliczajaca wspolczynnik kierunkowy prostej poprowadzonej przez wspolrzedne dwoch punktow.
     * 
     * @param X1 Wspolrzedna X pierwszego punktu.
     * @param X2 Wspolrzedna X drugiego punktu.
     * @param Y1 Wspolrzedna Y pierwszego punktu.
     * @param Y2 Wspolrzedna Y drugiego punktu.
     * @return Wspolczynnik kierunkowy.
     */
    private double obliczWspolczynnikKierunkowy(double X1, double X2, double Y1, double Y2) {
        double wspolczynnikKierunkowyKrawedzi;
            if(X1 == X2) {
                if(Math.signum(Y1 - Y2) > 0)
                    wspolczynnikKierunkowyKrawedzi = Double.POSITIVE_INFINITY;
                else
                    wspolczynnikKierunkowyKrawedzi = Double.NEGATIVE_INFINITY;
            }
            else
                wspolczynnikKierunkowyKrawedzi = (Y2 - Y1) / (X2 - X1);
        return wspolczynnikKierunkowyKrawedzi;
    }
    
    /**
     * Funkcja ta oblicza kat prostej poprowadzonej przez centrum figury i wskaznik myszy.
     * Nastepnie wyliczony kat przeksztalca, aby na osi OY wynosil 0 stopni.
     * 
     * @see KontrolerAplikacji#obliczWspolczynnikKierunkowy
     * @param X Wspolrzedna x pierwszego punktu.
     * @param Y Wspolrzedna y pierwszego punktu.
     * @return Kat w stopniach.
     */
    public double katWzgledemOsiOY(double X, double Y) {
        double wspolczynnikKierunkowy1 = this.obliczWspolczynnikKierunkowy(X, centrXObracanejFigury, Y, centrYObracanejFigury);
        
        return Math.atan(wspolczynnikKierunkowy1) - Math.PI / 2;
    }

    /**
     * Funkcja ta oblicza wspolrzedne srodka ciezkosci aktualnie wybranej figury.
     * 
     * @return Punkt srodka
     */
    public Point2D srodekCiezkosciWybranejFigury() {
        ObservableList<Double> listaWspolrzednych = wybranyWielokat.getPoints();
        Point2D srodekCiezkosci;
        // wybrany wielokat to prostokat
        if(listaWspolrzednych.size() == 8) {
            Point2D wierzcholek1, wierzcholek2;
            wierzcholek1 = wybranyWielokat.localToParent(listaWspolrzednych.get(0), listaWspolrzednych.get(1));
            wierzcholek2 = wybranyWielokat.localToParent(listaWspolrzednych.get(4), listaWspolrzednych.get(5));

            centrXObracanejFigury = (wierzcholek1.getX() + wierzcholek2.getX()) / 2 ;
            centrYObracanejFigury = (wierzcholek1.getY() + wierzcholek2.getY()) / 2 ;
        } 
        // wybrany wielokat to trojkat
        else {
                Point2D wierzcholek1, wierzcholek2, wierzcholek3;
                wierzcholek1 = wybranyWielokat.localToParent(listaWspolrzednych.get(0), listaWspolrzednych.get(1));
                wierzcholek2 = wybranyWielokat.localToParent(listaWspolrzednych.get(2), listaWspolrzednych.get(3));
                wierzcholek3 = wybranyWielokat.localToParent(listaWspolrzednych.get(4), listaWspolrzednych.get(5));
                
                centrXObracanejFigury = (wierzcholek1.getX() + wierzcholek2.getX() + wierzcholek3.getX()) / 3;
                centrYObracanejFigury = (wierzcholek1.getY() + wierzcholek2.getY() + wierzcholek3.getY()) / 3;
        }
        return wybranyWielokat.parentToLocal(centrXObracanejFigury, centrYObracanejFigury);
    }

    /**
     * Funkcja ta okresla czy gorna krawedz oryginalnej figury znajduje sie na gorze, czy na dole.
     * 
     * @return Wspolczynnik o wartosci 1 lub -1.
     */
    private int znajdzWspolczynnikUstawieniaFigury() {
        ObservableList<Double> listaWspolrzednych = wybranyWielokat.getPoints();
        if(listaWspolrzednych.size() == 8) {
            return listaWspolrzednych.get(1) > listaWspolrzednych.get(7) ?
                -1 : 1;
        }
        else {
            return listaWspolrzednych.get(3) > ((listaWspolrzednych.get(1) + listaWspolrzednych.get(5)) / 2) ?
                -1 : 1;
        }
    }

    /**
     * Funkcja odpowiedzialna za utworzenie znacznika nad prostokatem sluzacego do obracania wybranej figury.
     * Funkcja ta liczy wspolczynniki kierunkowe wzgledem wierzcholkow prostokata i na ich podstawie 
     * wyznacza wspolrzedne jego srodka.
     * 
     * @param event Wydarzenie wywolane przez nacisniecie przycisku myszy na figure.
     * @param przestrzenRobocza Przestrzen sluzaca do tworzenia figur przez uzytkownika.
     */
    public void utworzProstokatDoObrotuDlaProstokata(MouseEvent event,
                                                    Pane przestrzenRobocza) {
        if(prostokatDoObrotu == null) {
            ObservableList<Double> listaWspolrzednych = wybranyWielokat.getPoints();
            double wspolrzednaX1, wspolrzednaX2, wspolrzednaY1, wspolrzednaY2;

            wspolrzednaX1 = listaWspolrzednych.get(0);
            wspolrzednaX2 = listaWspolrzednych.get(2);
            wspolrzednaY1 = listaWspolrzednych.get(1);
            wspolrzednaY2 = listaWspolrzednych.get(3);
                
            // wyznaczenie srodkow gornej krawedzi
            double srodekGornejKrawedziX = (wspolrzednaX1 + wspolrzednaX2) / 2;
            double srodekGornejKrawedziY = (wspolrzednaY1 + wspolrzednaY2) / 2;

            // utworzenie prostokatu do obrotu z obliczonych wartosci
            prostokatDoObrotu = new Polygon();
            prostokatDoObrotu.getPoints().addAll(new Double[] {
                srodekGornejKrawedziX + 10, srodekGornejKrawedziY + 10,
                srodekGornejKrawedziX + 10, srodekGornejKrawedziY - 10,
                srodekGornejKrawedziX - 10, srodekGornejKrawedziY - 10,
                srodekGornejKrawedziX - 10, srodekGornejKrawedziY + 10
            });
        }
    }

    /**
     * Funkcja odpowiedzialna za utworzenie znacznika nad trojkatem sluzacego do obracania figury.
     * 
     * @param event Wydarzenie wywolane przez nacisniecie przycisku myszy na figure.
     * @param przestrzenRobocza Przestrzen sluzaca do tworzenia figur przez uzytkownika.
     */
    public void utworzProstokatDoObrotuDlaTrojkata(MouseEvent event, Pane przestrzenRobocza) {
        if(prostokatDoObrotu == null) {
            ObservableList<Double> listaWspolrzednych = wybranyWielokat.getPoints();
            double wspolrzednaX = listaWspolrzednych.get(2);
            double wspolrzednaY = listaWspolrzednych.get(3);

            // utworzenie prostokatu do obrotu z obliczonych wartosci
            prostokatDoObrotu = new Polygon();
            prostokatDoObrotu.getPoints().addAll(new Double[] {
                wspolrzednaX + 10, wspolrzednaY + 10,
                wspolrzednaX + 10, wspolrzednaY - 10,
                wspolrzednaX - 10, wspolrzednaY - 10,
                wspolrzednaX - 10, wspolrzednaY + 10
            });
        }
    }

    /**
     * Funkcja ta odpowiedzialna jest za utworzenie i ustawienie prostokatu do obrotu wybranej figury.
     * 
     * @see KontrolerAplikacji#utworzProstokatDoObrotuDlaProstokata
     * @see KontrolerAplikacji#utworzProstokatDoObrotuDlaTrojkata
     * @see KontrolerAplikacji#srodekCiezkosciWybranejFigury
     * @see KontrolerAplikacji#nacisnietoNaProstokatDoObrotu
     * @see KontrolerAplikacji#przesunietoProstokatDoObrotu
     * @param event Wydarzenie wywolane przez nacisniecie mysza na figure.
     * @param przestrzenRobocza Przestrzen, na ktorej tworzone sa figury.
     * @param wspolczynnikUstawieniaFigury Wspolczynnik okreslajacy polozenie gornej krawedzi oryginalnej figury.
     */
    public void utworzProstokatDoObrotu(MouseEvent event, Pane przestrzenRobocza, int wspolczynnikUstawieniaFigury) {
        // dodanie prostokata sluzacego do obrotu
        ObservableList<Double> listaWspolrzednych = wybranyWielokat.getPoints();
        if(prostokatDoObrotu == null) {
            if(listaWspolrzednych.size() == 8)
                this.utworzProstokatDoObrotuDlaProstokata(event, przestrzenRobocza);
            else
                this.utworzProstokatDoObrotuDlaTrojkata(event, przestrzenRobocza);
            
            double domyslnePrzemieszczenieProstokata = -70.0 * wspolczynnikUstawieniaFigury;

            prostokatDoObrotu.setFill(Color.CYAN);
            prostokatDoObrotu.setStroke(Color.GREEN);
            przestrzenRobocza.getChildren().add(prostokatDoObrotu);
            prostokatDoObrotu.toFront();

            // przesuniecie i obrot prostokata do obrotu
            prostokatDoObrotu.setLayoutX(wybranyWielokat.getLayoutX());
            prostokatDoObrotu.setLayoutY(wybranyWielokat.getLayoutY());

            Rotate obrotProstokata = new Rotate(0,0,0);
            Rotate obrotFigury = (Rotate)wybranyWielokat.getTransforms().get(0);
            Scale skalaFigury = (Scale)wybranyWielokat.getTransforms().get(1);

            Point2D srodekCiezkosci = this.srodekCiezkosciWybranejFigury();

            double przemieszczenieProstokataY = domyslnePrzemieszczenieProstokata
                + domyslnePrzemieszczenieProstokata * (skalaFigury.getY() - 1);

            obrotProstokata.setPivotX(srodekCiezkosci.getX());
            obrotProstokata.setPivotY(srodekCiezkosci.getY() - przemieszczenieProstokataY);

            prostokatDoObrotu.getTransforms().add(new Translate(0, przemieszczenieProstokataY));
            
            obrotProstokata.angleProperty().bind(obrotFigury.angleProperty());
            prostokatDoObrotu.getTransforms().add(obrotProstokata);

            // obsluga wydarzen dla prostokatu do obrotu
            prostokatDoObrotu.setOnMousePressed(e -> this.nacisnietoNaProstokatDoObrotu(e));
            prostokatDoObrotu.setOnMouseDragged(e -> this.przesunietoProstokatDoObrotu(e));
        }
    }

    /**
     * Funkcja obslugujaca wydarzenie nacisniecia na prostokat sluzacy do obrotu wybranej figury. 
     * Znajduje ona srodek ciezkosci wybranej figury w celu dalszego jej obrotu.
     * 
     * @see KontrolerAplikacji#srodekCiezkosciWybranejFigury
     * @param event Wydarzenie nacisniecia przycisku myszy.
     */
    public void nacisnietoNaProstokatDoObrotu(MouseEvent event) {
       if(event.isPrimaryButtonDown()) {
            Point2D srodekCiezkosci = this.srodekCiezkosciWybranejFigury();

            Rotate obrotFigury = (Rotate)wybranyWielokat.getTransforms().get(0);
            obrotFigury.setPivotX(srodekCiezkosci.getX());
            obrotFigury.setPivotY(srodekCiezkosci.getY());
       }
    }

    /** 
     * Funkcja obslugujaca wydarzenie przesuniecia prostokatu sluzacego do obrotu figury.
     * Oblicza ona kat miedzy poprzednim polozeniem myszki, a aktualnym.
     * Nastepnie ustawia wybrana figure w odpowiednim obrocie wzgledem aktualnego polozenia myszy.
     * 
     * @see KontrolerAplikacji#katWzgledemOsiOY
     * @see KontrolerAplikacji#znajdzWspolczynnikUstawieniaFigury
     * @param event Wydarzenie przeciagniecia mysza prostokatu do obrotu.
     */
    public void przesunietoProstokatDoObrotu(MouseEvent event) {
        if(event.isPrimaryButtonDown()) {
            Point2D wspolrzedneMyszy = prostokatDoObrotu.localToParent(event.getX(), event.getY());
            // obliczenie katu obrotu wzgledem poprzedniej pozycji myszki
            double roznicaKatu = katWzgledemOsiOY(wspolrzedneMyszy.getX(), 
                                                                wspolrzedneMyszy.getY());
            
            int wspolczynnikUstawieniaFigury = this.znajdzWspolczynnikUstawieniaFigury();
            double katDlaFiguryOdwroconej;
            if(wspolczynnikUstawieniaFigury == -1) {
                katDlaFiguryOdwroconej = 180;
            }
            else
                katDlaFiguryOdwroconej = 0;

            // obrot figur
            Rotate obrotFigury = (Rotate)wybranyWielokat.getTransforms().get(0);
            if(wspolrzedneMyszy.getX() >= centrXObracanejFigury)
                obrotFigury.setAngle(Math.toDegrees(roznicaKatu) - 180 + katDlaFiguryOdwroconej);
            else
                obrotFigury.setAngle(Math.toDegrees(roznicaKatu) + katDlaFiguryOdwroconej);
        }
    }

    /**
     * Funkcja odpowiedzialna za obsluge wyboru jednej z utworzonych figur na przestrzeni roboczej 
     * lub zmiane koloru wybranej figury.
     * 
     * @see KontrolerAplikacji#utworzProstokatDoObrotu
     * @param event Wydarzenie wywolane przez klikniecie myszy.
     * @param przestrzenRobocza Przestrzen na ktorej tworzone sa figury.
     */
    public void wybranoFigure(MouseEvent event, Pane przestrzenRobocza) {
        if(aktualnyTrybMyszki == TrybyMyszki.KURSOR && event.isPrimaryButtonDown()) {
            wspolrzednaXPrzesuwanejFigury = event.getX();
            wspolrzednaYPrzesuwanejFigury = event.getY();
            if(event.getTarget() instanceof Polygon) {
                wybranyWielokat = (Polygon)event.getTarget();
            
                // dodanie ramki
                wybranyWielokat.setStroke(null);
                wybranyWielokat.setStroke(Color.BLUE);
                wybranyWielokat.setStrokeWidth(4);
                wybranyWielokat.getStrokeDashArray().removeAll(8.0);
                wybranyWielokat.getStrokeDashArray().addAll(8.0);
                wybranyWielokat.toFront();
                if(wybranyWielokat.getTransforms().size() == 0) {
                    wybranyWielokat.getTransforms().add(new Rotate(0,0,0));
                    wybranyWielokat.getTransforms().add(new Scale(1,1));
                }

                // sprawdzenie czy gorna krawedz znajduje sie nad dolna
                int wspolczynnikUstawieniaFigury = this.znajdzWspolczynnikUstawieniaFigury();

                // obliczenia potrzebne do przesuwania prostokatu lub trojkata
                Point2D wspolrzedneMyszy = wybranyWielokat.localToParent(event.getX(), event.getY());
                wspolrzednaXPrzesuwanejFigury = wybranyWielokat.getLayoutX() - wspolrzedneMyszy.getX();
                wspolrzednaYPrzesuwanejFigury =  wybranyWielokat.getLayoutY() - wspolrzedneMyszy.getY();

                // utworzenie prostokatu do obrotu
                this.utworzProstokatDoObrotu(event, przestrzenRobocza, wspolczynnikUstawieniaFigury);
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
        // obsluga zmiany koloru ksztaltu
        else if(aktualnyTrybMyszki == TrybyMyszki.KURSOR && event.isSecondaryButtonDown()) {
            if(event.getTarget() instanceof Polygon && wybranyWielokat != null) {
                wybranyWielokat.setFill(wybranyKolor);
            }
            else if(event.getTarget() instanceof Circle && wybraneKolo != null) {
                wybraneKolo.setFill(wybranyKolor);
            }
        }
    } 

    /**
     * Funkcja odpowiedzialna za obsluge przesuwania wybranej figury.
     * 
     * @param event Wydarzenie wywolane przez klikniecie myszy.
     */
    public void przesunietoFigure(MouseEvent event) {
        if(aktualnyTrybMyszki == TrybyMyszki.KURSOR && event.isPrimaryButtonDown()) {
            // obliczenie przesuniecia myszki i zaktualizowanie nowej pozycji do kolejnych obliczen
            double roznicaX = event.getX() - wspolrzednaXPrzesuwanejFigury;
            double roznicaY = event.getY() - wspolrzednaYPrzesuwanejFigury;

            // wybor odpowiedniej figury do przesuniecia
            if(wybraneKolo != null) {
                wybraneKolo.setCenterX(wybraneKolo.getCenterX() + roznicaX);
                wybraneKolo.setCenterY(wybraneKolo.getCenterY() + roznicaY);
                
                wspolrzednaXPrzesuwanejFigury = event.getX();
                wspolrzednaYPrzesuwanejFigury = event.getY();
            }
            else if(wybranyWielokat != null) {
                Point2D wspolrzedneMyszy = wybranyWielokat.localToParent(event.getX(), event.getY());
                wybranyWielokat.setLayoutX(wspolrzedneMyszy.getX() + wspolrzednaXPrzesuwanejFigury);
                wybranyWielokat.setLayoutY(wspolrzedneMyszy.getY() + wspolrzednaYPrzesuwanejFigury);
                prostokatDoObrotu.setLayoutX(wspolrzedneMyszy.getX() + wspolrzednaXPrzesuwanejFigury);
                prostokatDoObrotu.setLayoutY(wspolrzedneMyszy.getY() + wspolrzednaYPrzesuwanejFigury);
                prostokatDoObrotu.toFront();
            }
        }
    }

    /**
     * Funkcja obslugujaca powiekszanie i pomniejszanie figur za pomoca scroll'a.
     * 
     * @see KontrolerAplikacji#srodekCiezkosciWybranejFigury
     * @see KontrolerAplikacji#znajdzWspolczynnikUstawieniaFigury
     * @see KontrolerAplikacji#utworzProstokatDoObrotu
     * @param scrollEvent Wydarzenie wywolane przez uzycie scroll'a.
     * @param przestrzenRobocza Przestrzen na ktorej tworzone sa figury.
     */
    public void uzytoScrollaNaFigurze(ScrollEvent scrollEvent, Pane przestrzenRobocza) {
        if(aktualnyTrybMyszki == TrybyMyszki.KURSOR) {
            if(wybranyWielokat == scrollEvent.getTarget()) {
                Scale skalaFigury = (Scale)wybranyWielokat.getTransforms().get(1);
                Point2D srodekCiezkosci = this.srodekCiezkosciWybranejFigury();

                skalaFigury.setPivotX(srodekCiezkosci.getX());
                skalaFigury.setPivotY(srodekCiezkosci.getY());

                double wartosc = scrollEvent.getDeltaY() / 400;
                skalaFigury.setX(skalaFigury.getX() + wartosc);
                skalaFigury.setY(skalaFigury.getY() + wartosc);

                // zaktualizuj srodek obrotu
                Rotate obrotFigury = (Rotate)wybranyWielokat.getTransforms().get(0);
                obrotFigury.setPivotX(srodekCiezkosci.getX());
                obrotFigury.setPivotY(srodekCiezkosci.getY());

                // utworz na nowo prostokat w odpowiedniej pozycji
                int wspolczynnikUstawieniaFigury = this.znajdzWspolczynnikUstawieniaFigury();

                przestrzenRobocza.getChildren().remove(prostokatDoObrotu);
                prostokatDoObrotu = null;
                this.utworzProstokatDoObrotu(null, przestrzenRobocza, wspolczynnikUstawieniaFigury);
            }
            if(wybraneKolo == scrollEvent.getTarget()) {
                wybraneKolo.setRadius(wybraneKolo.getRadius() + (scrollEvent.getDeltaY() * 0.5));
            }
        }
    }
    

}
