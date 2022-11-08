import java.util.ArrayList;
import java.util.Scanner;

/**
 * Kontroler faktur.
 * Klasa ta odpowiedzialna jest za odbieranie danych od uzytkownika,
 * pakowania ich w obiekt i wysylania go do dalszej pracy.
 */
public class KontrolerFaktur {
  ArrayList<Faktura> listaFaktur;
  Faktura aktualnaFaktura;

  /**
   * Konstruktor. Tworzy tablice do przechowywania wszystkich utworzonych faktur.
   */
  public KontrolerFaktur() {
    listaFaktur = new ArrayList<>();
  }

  /**
   * Metoda odpowiedzialna za utworzenie nowej faktury.
   * Prosi ona uzytkownika o wszyskie potrzebne dane oraz pakuje je do obiektu Faktura.
   */
  public void utworzNowaFakture() {
    aktualnaFaktura = new Faktura();
    listaFaktur.add(aktualnaFaktura);
    Scanner scanner = new Scanner(System.in);

    // wprowadzenie ogolnych danych o fakturze
    System.out.println("-----------Nowa faktura-----------");
    System.out.println("Wprowadz miejsce wystawienia faktury: ");
    String miejsce = scanner.nextLine();
    aktualnaFaktura.wprowadzInformacjeOgolne(miejsce);

    // wczytywanie danych dotyczacych stron tranzakcji
    System.out.println();
    this.wczytajDaneStrony("sprzedawcy");
    System.out.println();
    this.wczytajDaneStrony("nabywcy");

    // wczytywanie przedmiotow faktury
    System.out.println();
    this.wczytajElementyFaktury();
  }

  /**
   * Metoda odpowiedzialna za wczytanie danych dotyczacych jednej ze stron tranzakcji,
   * dla ktorej tworzona jest faktura.
   *
   * @param strona Napis "sprzedawcy" lub "nabywcy" identyfikujacy strone tranzakcji.
   */
  private void wczytajDaneStrony(String strona) {
    Scanner scanner = new Scanner(System.in);
    System.out.println("Wprowadz informacje o " + strona);
    System.out.println("----------------------------------");

    System.out.println("Podaj nazwe " + strona + ": ");
    final String nazwa = scanner.nextLine();
    System.out.println("Podaj NIP " + strona + ": ");
    final String nip = scanner.nextLine();
    System.out.println("Podaj ulice " + strona + ": ");
    final String adres = scanner.nextLine();
    System.out.println("Podaj kod pocztowy i miasto " + strona + ": ");
    final String kodPocztowyMiasto = scanner.nextLine();

    aktualnaFaktura.wprowadzDaneStrony(strona, nazwa, nip, adres, kodPocztowyMiasto);
  }

  /**
   * Metoda ta wczytuje od uzytkownika elementy faktury razem z kwota i iloscia.
   * Nastepnie wysyla dane do faktury.
   */
  private void wczytajElementyFaktury() {
    System.out.println("---------Elementy faktury----------");
    String wybor;
    Scanner scanner = new Scanner(System.in);

    // wprowadzaj elementy poki uzytkownik nie zdecyduje inaczej
    while (true) {
      System.out.println("Czy chcesz dodac kolejny element faktury? (Y/N): ");
      wybor = scanner.nextLine();
      if (wybor.equalsIgnoreCase("y")) {
        // pobierz dane od uzytkownika
        String nazwaTowarUsluga = this.wprowadzNazweElementu();
        int iloscLiczba = this.wprowadzIloscElementu();
        double cenaLiczba = this.wprowadzCeneElementu();

        // wprowadz element do faktury
        aktualnaFaktura.wprowadzElement(nazwaTowarUsluga, iloscLiczba, cenaLiczba);
      } else if (wybor.equalsIgnoreCase("n")) {
        if (aktualnaFaktura.iloscElementow() == 0) {
          System.out.println("Faktura musi posiadac chociaz jeden element.");
          System.out.println();
        } else {
          break;
        }
      } else {
        System.out.println("Nieprawidlowy wybor.");
        System.out.println();
      }
    } // end while
  }

  /**
   * Metoda ta pobiera od uzytkownika nazwe elementu na fakturze.
   * Waliduje ona, czy uzytkownik wprowadzil poprawne dane.
   *
   * @return Nazwa elementu na fakturze.
   */
  private String wprowadzNazweElementu() {
    Scanner scanner = new Scanner(System.in);
    String nazwaTowarUsluga;
    while (true) {
      System.out.println("Wprowadz nazwe towaru lub uslugi: ");
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
  private int wprowadzIloscElementu() {
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
  private double wprowadzCeneElementu() {
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
   * Metoda ta sprawdza, czy wczesniej zostaly utworzone faktury.
   *
   * @return Czy uzytkownik stworzyl wczesniej faktury?
   */
  public boolean czyIstniejaUtworzoneFaktury() {
    return !listaFaktur.isEmpty();
  }

}
