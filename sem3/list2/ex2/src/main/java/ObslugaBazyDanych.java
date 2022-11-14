import java.sql.Connection;
import java.sql.DriverManager;

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
   * @param faktura Faktura do wprowadzenia do bazy danych.
   */
  public void wprowadzFakture(Faktura faktura) {

  }
}
