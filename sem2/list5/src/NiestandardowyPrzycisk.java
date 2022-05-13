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
 * Klasa odpowiedzialna za utworzenie przyciskow wyboru figury.
 */
class NiestandardowyPrzycisk extends Button {

    // stala dla stylu przycisku nadpisujaca efekt niebieskiej obramowki
    private static final String STYL_PRZYCISKU = """
        -fx-background-color: -fx-shadow-highlight-color, 
            -fx-outer-border, -fx-inner-border, -fx-body-color;
        -fx-background-insets: 0 0 -1 0, 0, 1, 2;
        -fx-background-radius: 5, 5, 4, 3;
            """;

    // stala dla stylu figur sluzacych jako grafika przyciskow
    private static final String STYL_FIGUR_PRZYCISKOW = """
        -fx-fill: white; -fx-stroke: black
            """;

    /**
     * Konstruktor przycisku, ktory na podstawie wybranego rodzaju tworzy odpowiedni przycisk z recznie utworzona grafika.
     * 
     * @param rodzaj Zmienna jednoznacznie wyznaczajaca rodzaj przycisku.
     */
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
}

