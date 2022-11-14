import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

/**
 * Klasa odpowiedzialna za obsluge polaczenia i komunikacji z baza danych.
 * -------------------------------------------------------------
 * Zasada Czysty wymysl, Wysoka spojnosc.
 */
public class ObslugaBazyDanych {
  Connection polaczenie = null;

  /**
   * Konstruktor. Tworzy polaczenie z baza danych.
   */
  public ObslugaBazyDanych() {
    try {
      // uzywamy sterownik do naszej bazy danych oraz wpisujemy poprawny adres, login i haslo
      Class.forName("com.mysql.jdbc.Driver");
      polaczenie =
          DriverManager.getConnection("baza_danych", "login", "haslo");
    } catch (Exception e) {
      System.out.println("Nie udalo sie polaczyc z baza danych.\n");
    }
  }

  /**
   * Metoda odpowiedzialna za wprowadzenie danych z faktury do bazy danych.
   *
   * @param informacjeOgolne Lista lancuchow znakowych zawierajaca informacje ogolne o fakturze.
   * @param informacjeSprzedawca Lista lancuchow znakowych zawierajaca informacje o sprzedawcy.
   * @param informacjeNabywca Lista lancuchow znakowych zawierajaca informacje o nabywcy.
   * @param informacjeElementy Lista lancuchow znakowych zawierajaca informacje o
   *                           elementach na fakturze.
   * @param informacjeSumy Lista lancuchow znakowych zawierajaca sumy z faktury.
   */
  public void wprowadzFakture(String[] informacjeOgolne,
      String[] informacjeSprzedawca,
      String[] informacjeNabywca,
      String[] informacjeElementy,
      String[] informacjeSumy) {
    // miejsce na wprowadzenie informacji do bazy danych
    if (polaczenie != null) {
      String trescZapytania = "(" + informacjeOgolne[0] + "," + informacjeOgolne[1] + ",";
      trescZapytania += informacjeSprzedawca[0] + "," + informacjeSprzedawca[1] + ","
          + informacjeSprzedawca[2] + "," + informacjeSprzedawca[3] + ",";
      trescZapytania += informacjeNabywca[0] + "," + informacjeNabywca[1] + ","
          + informacjeNabywca[2] + "," + informacjeNabywca[3];
      trescZapytania += informacjeSumy[0] + "," + informacjeSumy[1] + "," + informacjeSumy[2] + ")";
      // wprowazd fakture do systemu
      try {
        Statement zapytanie = polaczenie.createStatement();
        ResultSet wynikFaktury =
            zapytanie.executeQuery("insert into faktury values " + trescZapytania);
        String idFaktury = wynikFaktury.getString("id");

        for (int i = 0; i < informacjeElementy.length; i += 4) {
          String trescZapytaniaElement = "(" + informacjeElementy[i] + ","
              + informacjeElementy[i + 1] + "," + informacjeElementy[i + 2]
              + "," + informacjeElementy[i + 3] + "," + idFaktury + ")";

          // wprowadz element faktury razem z id faktury do systemu
          Statement zapytanieElementy = polaczenie.createStatement();
          zapytanieElementy.executeQuery("insert into elementy values "
              + trescZapytaniaElement);
        }

      } catch (SQLException e) {
        System.out.println("Nie udalo sie wprowadzic faktury do bazy danych.\n");
      }

    } else {
      System.out.println("System nie jest polaczony z baza danych.\n");
    }
  }
}
