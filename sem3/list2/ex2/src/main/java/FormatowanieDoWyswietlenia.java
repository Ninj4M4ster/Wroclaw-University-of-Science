/**
 * Klasa ta odpowiedzialna jest za wspomaganiem przy formatowaniy danych w
 * taki sposob, aby byly czytelne dla czlowieka.
 * Stworzenie instancji tej klasy jest niemozliwe.
 * -------------------------------------------------------------
 * Zasada Czysty wymysl, Wysoka spojnosc:
 * Klasa ta powstala w celu wspomagania formatowania danych w czytelny sposob.
 * Nie nalezy ona do domeny systemu.
 */
public final class FormatowanieDoWyswietlenia {

  /**
   * Lista ta przedstawia odleglosc separatora komorek tabeli od poczatku linii w konsoli.
   */
  private static final int[] ODLEGLOSCI_WIERSZY_TABELI = {
      4, 32, 40, 57, 73, 81, 89
  };

  /**
   * Stala ta przedstawia przesuniecie tabeli sum od poczatku linii terminala.
   */
  private static final int ODLEGLOSC_TABELI_SUM = 61;

  /**
   * Lista ta przedstawia odleglosc separatora komorek tabeli sum od poczatku linii w konsoli.
   */
  private static final int[] ODLEGLOSCI_WIERSZY_TABELI_SUM = {
      73, 85
  };

  /**
   * Prywatny konstruktor. Ma zapobiec probie stworzenia obiektu tej klasy.
   */
  private FormatowanieDoWyswietlenia() {}

  /**
   * Metoda ta tworzy napis zlozony z dwoch lancuchow znakowych w taki sposob,
   * aby drugi napis znajdywal sie w podanej przez parametr odleglosci od poczatku linii.
   *
   * @param napis1 Pierwszy napis, znajdujacy sie na poczatku linii.
   * @param napis2 Drugi napis, znajdujacy sie w podanej odleglosci od poczatku linii.
   * @param odleglosc Odleglosci drugiego napisu od poczatku linii (ilosc znakow).
   * @return Sformatowany lancuch znakowy.
   */
  public static String ulozDwaNapisy(String napis1, String napis2, int odleglosc) {
    // znajdz wymagana liczbe spacji do pozadanej pozycji
    int odlegloscFinalna = odleglosc - napis1.length();
    napis1 = napis1 + " ".repeat(Math.max(0, odlegloscFinalna)) + napis2;
    return napis1;
  }

  /**
   * Metoda odpowiedzialna za utworzenie pierwszego wiersza tabeli sluzacej do
   * wyswietlenia informacji o elementach na fakturze.
   *
   * @return Napis z pierwszym wierszem tabeli.
   */
  public static StringBuilder stworzPierwszyWierszTabeli() {
    return new StringBuilder("Lp  |    Nazwa towaru/uslugi    | ilosc |   Cena jedn.   |"
        + " Wartosc netto | VAT % |  VAT  | Wartosc Brutto\n");
  }

  /**
   * Metoda odpowiedzialna za sformatowanie elementu z faktury w czytelny sposob.
   * Tworzy ona separatory miedzy poszczegolnymi informacjami o elemencie tak,
   * aby utworzyc tabele.
   *
   * @param indeks Indeks aktualnego elementu.
   * @param element Element do wyswietlenia w tabeli.
   * @return Napis utworzony z informacji o elemencie w formie tabeli.
   */
  public static String sformatujElementFaktury(int indeks, ElementFaktury element) {
    StringBuilder napisKoncowy = new StringBuilder(String.valueOf(indeks + 1));
    napisKoncowy.append(" ".repeat(ODLEGLOSCI_WIERSZY_TABELI[0] - napisKoncowy.length()))
        .append("| ");
    String[] wartosciDoWyswietlenia = element.toString().split(";;");
    for (int i = 0; i < wartosciDoWyswietlenia.length; i++) {
      napisKoncowy.append(wartosciDoWyswietlenia[i]);
      // jesli trzeba to dodaj spacje oraz separator komorek
      if (i < ODLEGLOSCI_WIERSZY_TABELI.length - 1) {
        int iloscSpacji = ODLEGLOSCI_WIERSZY_TABELI[i + 1] - napisKoncowy.length();
        napisKoncowy.append(" ".repeat(Math.max(1, iloscSpacji)));
        napisKoncowy.append("| ");
      }
    }
    return napisKoncowy + "\n";
  }

  /**
   * Metoda odpowiedzialna za utworzenie tabeli zawierajacej sumy kwot wszystkich
   * elementow na fakturze.
   *
   * @return Napis z tabela sum.
   */
  public static String stworzTabeleSum(String sumaNetto, String sumaVat, String sumaBrutto) {
    final String pierwszyWiersz = " ".repeat(ODLEGLOSC_TABELI_SUM)
        + "Razem netto | Razem VAT | Razem brutto\n";
    String tabela = " ".repeat(ODLEGLOSC_TABELI_SUM + 1) + sumaNetto;
    tabela += " ".repeat(Math.max(1, ODLEGLOSCI_WIERSZY_TABELI_SUM[0] - tabela.length())) + "| ";
    tabela += sumaVat;
    tabela += " ".repeat(Math.max(1, ODLEGLOSCI_WIERSZY_TABELI_SUM[1] - tabela.length())) + "| ";
    tabela += sumaBrutto;
    return pierwszyWiersz + tabela + "\n";
  }

}
