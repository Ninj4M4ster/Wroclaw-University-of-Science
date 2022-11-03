import java.util.ArrayList;
import java.util.Scanner;

/**
 * Kontroler uzytkownika.
 * Klasa ta odpowiedzialna jest za odbieranie danych od uzytkownika,
 * pakowania ich w obiekt i wysylania go do dalszej pracy.
 */
public class KontrolerFaktur {
  Scanner scanner;
  ArrayList<Faktura> listaFaktur;
  Faktura aktualnaFaktura;

  public KontrolerFaktur() {
    scanner = new Scanner(System.in);
    listaFaktur = new ArrayList<>();
  }

  public void utworzNowaFakture() {
    aktualnaFaktura = new Faktura();
    listaFaktur.add(aktualnaFaktura);
  }

  private void wczytajDaneStrony(Faktura faktura, String strona) {
    System.out.print("Podaj nazwę " + strona + ": ");
    final String nazwa = scanner.nextLine();
    System.out.print("Podaj NIP " + strona + ": ");
    final String nip = scanner.nextLine();
    System.out.print("Podaj ulice " + strona + ": ");
    final String adres = scanner.nextLine();
    System.out.print("Podaj kod pocztowy i miasto " + strona + ": ");
    final String kodPocztowyMiasto = scanner.nextLine();
    faktura.wprowadzDaneStrony(strona, nazwa, nip, adres, kodPocztowyMiasto);
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
