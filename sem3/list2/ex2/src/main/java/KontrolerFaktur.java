import java.util.ArrayList;
import java.util.Scanner;

/**
 * Kontroler faktur.
 * Klasa ta odpowiedzialna jest za odbieranie danych od uzytkownika,
 * pakowania ich w obiekt i wysylania go do dalszej pracy.
 */
public class KontrolerFaktur {
  Scanner scanner;
  ArrayList<Faktura> listaFaktur;
  Faktura aktualnaFaktura;

  /**
   * Konstruktor. Tworzy tablice do przechowywania wszystkich utworzonych faktur.
   */
  public KontrolerFaktur(Scanner scanner) {
    this.scanner = scanner;
    this.listaFaktur = new ArrayList<>();
  }

  /**
   * Metoda odpowiedzialna za utworzenie nowej faktury.
   * Prosi ona uzytkownika o wszyskie potrzebne dane oraz pakuje je do obiektu Faktura.
   *
   * @see Faktura
   * @see Faktura#wprowadzInformacjeOgolne
   * @see Faktura#obliczSumy
   * @see KontrolerFaktur#wczytajDaneStrony
   * @see KontrolerFaktur#wczytajElementyFaktury
   * @see KontrolerFaktur#konczTworzycFakture
   */
  public void utworzNowaFakture() {
    aktualnaFaktura = new Faktura();
    listaFaktur.add(aktualnaFaktura);

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
   * @see WczytDanych#wprowadzNapis
   * @see Faktura#wprowadzDaneStrony
   */
  private void wczytajDaneStrony(String strona) {
    System.out.println("Wprowadz informacje o " + strona);
    System.out.println("----------------------------------");

    final String nazwa =
        WczytDanych.wprowadzNapis("Podaj nazwe " + strona + ":", scanner);
    final String nip =
        WczytDanych.wprowadzNapis("Podaj NIP " + strona + ":", scanner);
    final String adres =
        WczytDanych.wprowadzNapis("Podaj ulice " + strona + ":", scanner);
    final String kodPocztowyMiasto =
        WczytDanych.wprowadzNapis("Podaj kod pocztowy i miasto " + strona + ":", scanner);

    aktualnaFaktura.wprowadzDaneStrony(strona, nazwa, nip, adres, kodPocztowyMiasto);
  }

  /**
   * Metoda ta wczytuje od uzytkownika elementy faktury razem z kwota i iloscia.
   * Nastepnie wysyla dane do faktury.
   *
   * @see WczytDanych#wprowadzNapis
   * @see WczytDanych#wprowadzIloscElementu
   * @see WczytDanych#wprowadzCeneElementu
   * @see WczytDanych#wprowadzPodatek
   * @see Faktura#wprowadzElement
   * @see Faktura#iloscElementow
   */
  private void wczytajElementyFaktury() {
    System.out.println("---------Elementy faktury----------");
    String wybor;

    // wprowadzaj elementy poki uzytkownik nie zdecyduje inaczej
    while (true) {
      System.out.println("Czy chcesz dodac kolejny element faktury? (Y/N): ");
      wybor = scanner.nextLine();
      if (wybor.equalsIgnoreCase("y")) {
        // pobierz dane od uzytkownika
        String nazwaTowarUsluga =
            WczytDanych.wprowadzNapis("Wprowadz nazwe towaru lub uslugi:", scanner);
        int iloscLiczba = WczytDanych.wprowadzIloscElementu(scanner);
        double cenaLiczba = WczytDanych.wprowadzCeneElementu(scanner);
        double podatek = WczytDanych.wprowadzPodatek(scanner);

        // wprowadz element do faktury
        aktualnaFaktura.wprowadzElement(nazwaTowarUsluga, iloscLiczba, cenaLiczba, podatek);
      } else if (wybor.equalsIgnoreCase("n")) {
        if (aktualnaFaktura.iloscElementow() == 0) {
          System.out.println("Faktura musi posiadac chociaz jeden element.\n");
        } else {
          break;
        }
      } else {
        System.out.println("Nieprawidlowy wybor.\n");
      }
    } // end while
  }

  /**
   * Metoda majaca za zadanie wyswietlic fakture po skonczeniu jej wypelniania.
   */
  private void konczTworzycFakture() {
    System.out.println(aktualnaFaktura);
  }

  /**
   * Metoda ta sprawdza, czy wczesniej zostaly utworzone faktury.
   *
   * @return Czy uzytkownik stworzyl wczesniej faktury?
   */
  public boolean czyIstniejaUtworzoneFaktury() {
    return !listaFaktur.isEmpty();
  }

  /**
   * Metoda odpowiedzialna za wyswietlanie uzytkownikowi faktur:
   * w zaleznosci od wyboru kolejnej lub poprzedniej.
   *
   * @see WczytDanych#wczytajDopuszczalna
   */
  public void wyswietlajWczesniejUtworzoneFaktury() {
    String wybor;
    int indeks = 0;
    if (!listaFaktur.isEmpty()) {
      while (true) {
        Faktura faktura = listaFaktur.get(indeks);
        System.out.println(faktura + "\n");
        if (indeks == 0 && indeks == listaFaktur.size() - 1) {
          wybor = WczytDanych.wczytajDopuszczalna(new String[]{"e"},
              "Nacisnij 'e' aby opuscic wyswietlanie faktur.",
              scanner);
        } else if (indeks == 0) {
          wybor = WczytDanych.wczytajDopuszczalna(new String[]{"l", "e"},
              "Nacisnij 'l' aby wyswietlic kolejna fakture "
                  + "lub 'e' aby opuscic wyswietlanie faktur.",
              scanner);
        } else if (indeks == listaFaktur.size() - 1) {
          wybor = WczytDanych.wczytajDopuszczalna(new String[]{"k", "e"},
              "Nacisnij 'k' aby wyswietlic poprzednia fakture "
                  + "lub 'e' aby opuscic wyswietlanie faktur",
              scanner);
        } else {
          wybor = WczytDanych.wczytajDopuszczalna(new String[]{"l", "k", "e"},
              "Nacisnij 'k' aby wyswietlic poprzednia fakture, 'l' "
                  + "aby wyswietlic nastepna lub 'e' aby opuscic wyswietlanie faktur",
              scanner);
        }
        if (wybor.equals("l")) {
          indeks += 1;
        } else if (wybor.equals("k")) {
          indeks -= 1;
        } else {
          break;
        }
      }
    }

  }

}
