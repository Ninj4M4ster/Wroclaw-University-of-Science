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

  public KontrolerFaktur() {
    listaFaktur = new ArrayList<>();
  }

  public void utworzNowaFakture() {
    aktualnaFaktura = new Faktura();
    listaFaktur.add(aktualnaFaktura);
    Scanner scanner = new Scanner(System.in);

    // wprowadzenie ogolnych danych o fakturze
    System.out.println("-----------Nowa faktura-----------");
    System.out.println("Wprowadz miejsce wystawienia faktury: ");
    String miejsce = scanner.nextLine();
    aktualnaFaktura.wprowadzInformacjeOgolne(miejsce);

    System.out.println();
    this.wczytajDaneStrony("sprzedawcy");
    System.out.println();
    this.wczytajDaneStrony("nabywcy");
  }

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
   * Metoda ta sprawdza, czy wczesniej zostaly utworzone faktury.
   *
   * @return Czy uzytkownik stworzyl wczesniej faktury?
   */
  public boolean czyIstniejaUtworzoneFaktury() {
    return !listaFaktur.isEmpty();
  }

}
