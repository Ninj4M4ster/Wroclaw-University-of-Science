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

    // skonczono wpisywac dane, wiec faktura moze obliczyc sume
    aktualnaFaktura.obliczSumy();

    // po wszystkim wyswietl fakture i zapytaj o edycje
    System.out.println();
    this.konczTworzycFakture();
  }

  /**
   * Metoda odpowiedzialna za wczytanie danych dotyczacych jednej ze stron tranzakcji,
   * dla ktorej tworzona jest faktura.
   *
   * @param strona Napis "sprzedawcy" lub "nabywcy" identyfikujacy strone tranzakcji.
   */
  private void wczytajDaneStrony(String strona) {
    System.out.println("Wprowadz informacje o " + strona);
    System.out.println("----------------------------------");

    final String nazwa =
        WczytDanychFaktury.wprowadzNapis("Podaj nazwe " + strona + ":");
    final String nip =
        WczytDanychFaktury.wprowadzNapis("Podaj NIP " + strona + ":");
    final String adres =
        WczytDanychFaktury.wprowadzNapis("Podaj ulice " + strona + ":");
    final String kodPocztowyMiasto =
        WczytDanychFaktury.wprowadzNapis("Podaj kod pocztowy i miasto " + strona + ":");

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
        String nazwaTowarUsluga =
            WczytDanychFaktury.wprowadzNapis("Wprowadz nazwe towaru lub uslugi:");
        int iloscLiczba = WczytDanychFaktury.wprowadzIloscElementu();
        double cenaLiczba = WczytDanychFaktury.wprowadzCeneElementu();
        double podatek = WczytDanychFaktury.wprowadzPodatek();

        // wprowadz element do faktury
        aktualnaFaktura.wprowadzElement(nazwaTowarUsluga, iloscLiczba, cenaLiczba, podatek);
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

  private void konczTworzycFakture() {
    System.out.println();
    System.out.println(aktualnaFaktura);
    System.out.println();
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
