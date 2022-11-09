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

  /**
   * Sprawdz czy podany napis jest procentem i znajduje sie w zakresie 0-100.
   *
   * @param napis Napis do sprawdzenia.
   * @return Czy napis jest liczba z przedzialu 0-100?
   */
  public static boolean czyProcent(String napis) {
    if (napis.isEmpty()) {
      return false;
    }
    double procent;
    try {
      procent = Double.parseDouble(napis);
    } catch (NumberFormatException e) {
      return false;
    }
    return procent >= 0 && procent <= 100;
  }

  /**
   * Metoda ta zaokrogla podana liczbe do dwoch miejsc po przecinku.
   *
   * @param liczba Liczba do zaokraglenia.
   * @return Podana liczba zaokraglona do dwoch miejsc po przecinku.
   */
  public static double zaokraglDoDwoch(double liczba) {
    return Math.round(liczba * 100.0) / 100.0;
  }
}
