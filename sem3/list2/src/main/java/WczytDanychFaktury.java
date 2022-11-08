import java.util.Scanner;

/**
 * Klasa odpowiedzialna za wczytywanie i walidacje danych wprowadzanych do faktury.
 * Niemozliwe jest stworzenie jej instancji.
 */
public final class WczytDanychFaktury {

  /**
   * Prywatny konstruktor w celu uniemozliwienia utworzenia obiektu tej klasy.
   */
  private WczytDanychFaktury() {}

  /**
   * Metoda ta pobiera od uzytkownika napis.
   * Wyswietla podany przez parametr komunikat za kazdym razem
   * gdy wymagane jest ponowne wprowadzenie danych.
   * Waliduje ona, czy uzytkownik nie zostawil pola pustego.
   *
   * @param komunikat Komunikat wyswietlany przed wprowadzaniem danych.
   * @return Napis wprowadzony przez uzytkownika.
   */
  public static String wprowadzNapis(String komunikat) {
    Scanner scanner = new Scanner(System.in);
    String nazwaTowarUsluga;
    while (true) {
      System.out.println(komunikat);
      nazwaTowarUsluga = scanner.nextLine();
      if (nazwaTowarUsluga.isEmpty()) {
        System.out.println("Nie wprowadzono danych.");
        System.out.println();
      } else {
        break;
      }
    }
    return nazwaTowarUsluga;
  }

  /**
   * Metoda ta pobiera od uzytkownika ilosc elementu na fakturze.
   * Waliduje ona, czy uzytkownika wprowadzil poprawne dane.
   *
   * @return Ilosc elementu na fakturze.
   */
  public static int wprowadzIloscElementu() {
    Scanner scanner = new Scanner(System.in);
    String ilosc;
    int iloscLiczba;
    // sprawdzaj czy wprowadzona ilosc jest liczba
    while (true) {
      System.out.println("Wprowadz ilosc: ");
      ilosc = scanner.nextLine();
      if (KontrolerDanych.czyLiczbaCalkowita(ilosc)) {
        iloscLiczba = Integer.parseInt(ilosc);
        break;
      } else {
        System.out.println("Wprowadzono nieprawidlowe dane.");
        System.out.println();
      }
    }
    return iloscLiczba;
  }

  /**
   * Metoda ta pobiera od uzytkownika cene za sztuke elementu na fakturze.
   * Waliduje ona, czy uzytkownik wprowadzil poprawne dane.
   *
   * @return Cena elementu na fakturze.
   */
  public static double wprowadzCeneElementu() {
    Scanner scanner = new Scanner(System.in);
    double cenaLiczba;
    String kwota;
    // sprawdzaj czy wprowadzona kwota jest liczba
    while (true) {
      System.out.println("Wprowadz cene brutto: ");
      kwota = scanner.nextLine();
      if (KontrolerDanych.czyLiczbaRzeczywista(kwota)) {
        cenaLiczba = Double.parseDouble(kwota);
        break;
      } else {
        System.out.println("Wprowadzono nieprawidlowe dane.");
        System.out.println();
      }
    }
    return cenaLiczba;
  }

  /**
   * Metoda ta pobiera od uzytkownika podatek od elementu na fakturze.
   * Waliduje ona, czy uzytkownik wprowadzil poprawne dane.
   *
   * @return Podatek od elementu na fakturze.
   */
  public static double wprowadzPodatek() {
    Scanner scanner = new Scanner(System.in);
    double podatekLiczba;
    String podatek;
    // sprawdzaj czy wprowadzony podatek jest poprawna liczba
    while (true) {
      System.out.println("Wprowadz podatek (liczba 0-100): ");
      podatek = scanner.nextLine();
      if (KontrolerDanych.czyProcent(podatek)) {
        podatekLiczba = Double.parseDouble(podatek);
        break;
      } else {
        System.out.println("Wprowadzono nieprawidlowe dane.");
        System.out.println();
      }
    }
    return podatekLiczba;
  }
}
