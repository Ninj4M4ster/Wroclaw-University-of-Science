import java.util.Scanner;

/**
 * Klasa odpowiedzialna za wczytywanie i walidacje danych wprowadzanych do faktury.
 * Niemozliwe jest stworzenie jej instancji.
 */
public final class WczytDanych {

  /**
   * Prywatny konstruktor w celu uniemozliwienia utworzenia obiektu tej klasy.
   */
  private WczytDanych() {}

  /**
   * Metoda ta pobiera od uzytkownika napis.
   * Wyswietla podany przez parametr komunikat za kazdym razem
   * gdy wymagane jest ponowne wprowadzenie danych.
   * Waliduje ona, czy uzytkownik nie zostawil pola pustego.
   *
   * @param komunikat Komunikat wyswietlany przed wprowadzaniem danych.
   * @return Napis wprowadzony przez uzytkownika.
   */
  public static String wprowadzNapis(String komunikat, Scanner scanner) {
    String nazwaTowarUsluga;
    while (true) {
      System.out.println(komunikat);
      nazwaTowarUsluga = scanner.nextLine();
      if (nazwaTowarUsluga.isBlank()) {
        System.out.println("Nie wprowadzono danych.\n");
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
   * @see KontrolerDanych#czyLiczbaCalkowita
   */
  public static int wprowadzIloscElementu(Scanner scanner) {
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
        System.out.println("Wprowadzono nieprawidlowe dane.\n");
      }
    }
    return iloscLiczba;
  }

  /**
   * Metoda ta pobiera od uzytkownika cene za sztuke elementu na fakturze.
   * Waliduje ona, czy uzytkownik wprowadzil poprawne dane.
   *
   * @return Cena elementu na fakturze.
   * @see KontrolerDanych#czyLiczbaRzeczywista
   */
  public static double wprowadzCeneElementu(Scanner scanner) {
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
        System.out.println("Wprowadzono nieprawidlowe dane.\n");
      }
    }
    return cenaLiczba;
  }

  /**
   * Metoda ta pobiera od uzytkownika podatek od elementu na fakturze.
   * Waliduje ona, czy uzytkownik wprowadzil poprawne dane.
   *
   * @return Podatek od elementu na fakturze.
   * @see KontrolerDanych#czyProcent
   */
  public static double wprowadzPodatek(Scanner scanner) {
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
        System.out.println("Wprowadzono nieprawidlowe dane.\n");
      }
    }
    return podatekLiczba;
  }

  /**
   * Metoda ta wyswietla podany przez parametr komunikat oraz wczytuje od uzytkownika dane.
   * Waliduje ona czy wprowadzone przez uzytkownika dane sa dopuszczone przez program.
   *
   * @param dopuszczalneZnaki Znaki mozliwe do wprowadzenia przez uzytkownika.
   * @param komunikat Komunikat do wyswietlenia w celu poinstruowania uzytkownika co wpisac.
   * @return Znak wprowadzony przez uzytkownika.
   */
  public static String wczytajDopuszczalna(String[] dopuszczalneZnaki,
      String komunikat,
      Scanner scanner) {
    String wybor = "";
    boolean poprawnyWybor = false;
    // wczytuj dane od uzytkownika poki nie poda poprawnego wyboru
    while (!poprawnyWybor) {
      System.out.println(komunikat);
      wybor = scanner.nextLine();
      for (String znak : dopuszczalneZnaki) {
        if (wybor.equalsIgnoreCase(znak)) {
          poprawnyWybor = true;
          break;
        }
      }
      if (!poprawnyWybor) {
        System.out.println("Dokonano nieprawidlowego wyboru.\n");
      }
    }
    return wybor;
  }
}
