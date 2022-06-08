import javafx.stage.*;
import javafx.scene.*;
import javafx.scene.control.*;
import javafx.scene.layout.GridPane;
import javafx.geometry.*;

/**
 * Specjalny dialog wywolywany w celu znalezienia wartosci w drzewie.
 */
class DialogWyszukania { 
    private static String wartosc;

    /**
     * Metoda wywolujaca dialog z odpowiednimi widgetami.
     * 
     * @return Wartosc wprowadzona do pola dialogu.
     */
    public static String uruchomDialog() {
        wartosc = null;
        Stage stage = new Stage();
        stage.initModality(Modality.APPLICATION_MODAL);

        TextField pole_wartosci = new TextField();

        Label opis_okna = new Label("Wprowadz wartosc do wyszukania w drzewie.");
        Label opis_pola_tekstowego = new Label("Wartosc:");

        Button przycisk = new Button("Wyślij");
        przycisk.setOnAction(e -> {
            wartosc = pole_wartosci.getText();
            stage.close();
        });

        GridPane uklad = new GridPane();

        uklad.setPadding(new Insets(10, 10, 10, 10));
        uklad.setVgap(10);
        uklad.setHgap(10);

        uklad.add(opis_okna, 1, 0);
        uklad.add(opis_pola_tekstowego, 0, 1);
        uklad.add(pole_wartosci, 1, 1);
        uklad.add(przycisk, 1, 2);

        Scene scena = new Scene(uklad, 350, 100);
        stage.setTitle("Wyszukiwanie wezla");
        stage.setScene(scena);
        stage.setResizable(false);
        stage.showAndWait();

        return wartosc;
    }
}
