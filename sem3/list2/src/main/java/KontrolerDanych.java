/**
 * Klasa odpowiedzialna za walidacje danych.
 * Niemozliwe jest utworzenie jej instancji.
 */
public final class KontrolerDanych {

  /**
   * Prywatny konstruktor w celu uniemozliwienia utworzenia instancji klasy.
   */
  private KontrolerDanych() {}

  /**
   * Sprawdz czy podany napis jest liczba typu Integer.
   *
   * @param napis Napis do sprawdzenia.
   * @return Czy napis jest liczba calkowita?
   */
  public static boolean czyLiczbaCalkowita(String napis) {
    if (napis.isEmpty()) {
      return false;
    }
    try {
      Integer.parseInt(napis);
    } catch (NumberFormatException e) {
      return false;
    }
    return true;
  }

  /**
   * Sprawdz czy podany napis jest liczba typu Double.
   *
   * @param napis Napis do sprawdzenia.
   * @return Czy napis jest liczba rzeczywista?
   */
  public static boolean czyLiczbaRzeczywista(String napis) {
    if (napis.isEmpty()) {
      return false;
    }
    try {
      Double.parseDouble(napis);
    } catch (NumberFormatException e) {
      return false;
    }
    return true;
  }
}
