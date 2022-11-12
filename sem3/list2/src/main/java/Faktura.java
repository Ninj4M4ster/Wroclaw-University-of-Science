import java.text.DateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Locale;

/**
 * Klasa reprezentujaca dane na fakturze.
 */
public class Faktura {

  // dane ogolne faktury
  private String miejsceWystawienia;
  private String dataWystawienia;

  // dane sprzedawcy
  private String nazwaSprzedawcy;
  private String nipSprzedawcy;
  private String ulicaSprzedawcy;
  private String kodPocztowyMiastoSprzedawcy;

  // dane nabywcy
  private String nazwaNabywcy;
  private String nipNabywcy;
  private String ulicaNabywcy;
  private String kodPocztowyMiastoNabywcy;

  // elementy faktury
  private final ArrayList<ElementFaktury> elementyFaktury = new ArrayList<>();

  // koncowe sumy kwot
  private double sumaNetto = 0;
  private double sumaVat = 0;
  private double sumaBrutto = 0;

  // stale
  /**
   * Odleglosc informacji o nabywcy od poczatku linii.
   */
  private static final int ODLEGLOSC_NAPIS_NABYWCA = 38;
  /**
   * Szerokosc faktury w terminalu.
   */
  private static final int SZEROKOSC_FAKTURY = 106;

  /**
   * Metoda ta zapisuje informacje ogolne otrzymane od kontrolera, czyli miejsce.
   * Data jest automatycznie generowana.
   *
   * @param miejsce Miejsce wystawienia faktury.
   */
  public void wprowadzInformacjeOgolne(String miejsce) {
    this.miejsceWystawienia = miejsce;
    DateFormat df = DateFormat.getDateInstance(DateFormat.SHORT, Locale.FRANCE);
    this.dataWystawienia = df.format(new Date());
  }

  /**
   * Metoda odpowiedzialna za zapisanie danych dotyczacych sprzedawcy lub nabywcy.
   *
   * @param strona Lancuch znakow oznaczajacy strone tranzakcji.
   *               Dopuszczalne wartosci to "sprzedawcy" lub "nabywcy".
   * @param nazwa Nazwa firmy strony.
   * @param nip Nip strony.
   * @param adres Ulica na ktora zarejestrowana jest firma strony.
   * @param kodPocztowyMiasto Kod pocztowy oraz miasto, w ktorym zarejestrowana jest firma strony.
   * @throws IllegalArgumentException Podano nieprawidlowa strone faktury.
   */
  public void wprowadzDaneStrony(
      String strona,
      String nazwa,
      String nip,
      String adres,
      String kodPocztowyMiasto) {
    if (strona.equals("sprzedawcy")) {
      this.nazwaSprzedawcy = nazwa;
      this.nipSprzedawcy = nip;
      this.ulicaSprzedawcy = adres;
      this.kodPocztowyMiastoSprzedawcy = kodPocztowyMiasto;
    } else if (strona.equals("nabywcy")) {
      this.nazwaNabywcy = nazwa;
      this.nipNabywcy = nip;
      this.ulicaNabywcy = adres;
      this.kodPocztowyMiastoNabywcy = kodPocztowyMiasto;
    } else {
      throw new IllegalArgumentException("Wprowadzono nieprawidlowa strone");
    }
  }

  /**
   * Metoda ta tworzy nowy element faktury i wprowadza go do listy wszystkich elementow.
   *
   * @param nazwaTowarUsluga Nazwa towaru lub uslugi.
   * @param ilosc Ilosc towaru/uslugi.
   * @param cena Cena za sztuke.
   * @param podatek Podatek od towaru/uslugi.
   * @see ElementFaktury
   */
  public void wprowadzElement(String nazwaTowarUsluga, int ilosc, double cena, double podatek) {
    ElementFaktury element = new ElementFaktury(nazwaTowarUsluga, ilosc, cena, podatek);
    elementyFaktury.add(element);
  }

  /**
   * Metoda ta zwraca ilosc elementow wprowadzonych do tej faktury.
   *
   * @return Ilosc elementow na tej fakturze.
   */
  public int iloscElementow() {
    return elementyFaktury.size();
  }

  /**
   * Metoda ta oblicza koncowe sumy na fakturze: netto, brutto i VAT.
   */
  public void obliczSumy() {
    double sumaNetto = 0;
    double sumaBrutto = 0;
    double sumaVat = 0;
    for (ElementFaktury element : elementyFaktury) {
      double cenaNetto = element.dajNetto();
      double cenaBrutto = element.dajBrutto();
      int ilosc = element.dajIlosc();
      sumaVat += (cenaBrutto - cenaNetto) * ilosc;
      sumaNetto += cenaNetto * ilosc;
      sumaBrutto += cenaBrutto * ilosc;
    }
    this.sumaNetto = sumaNetto;
    this.sumaBrutto = sumaBrutto;
    this.sumaVat = sumaVat;
  }

  /**
   * Metoda ta zwraca czytelnie sformatowane dane na tej fakturze.
   * -------------------------------------------------------------
   * Zasada Ekspert oraz Niskie sprzezenie:
   * Faktura posiada wszystkie informacje potrzebne do jej wyswietlenia, wiec
   * w wiekszosci to ona realizuje sformatowanie ich w czytelny dla czlowieka sposob.
   *
   * @return Sformatowane dane na fakturze.
   * @see Faktura#formatujInformacjeSprzedawcyNabywcy
   * @see FormatowanieDoWyswietlenia#stworzPierwszyWierszTabeli
   * @see FormatowanieDoWyswietlenia#sformatujElementFaktury
   * @see FormatowanieDoWyswietlenia#stworzTabeleSum
   * @see KontrolerDanych#zaokraglDoDwoch
   */
  @Override
  public String toString() {
    // przygotuj napis przedstawiajacy ogolne informacje o fakturze
    String poczatek = "-".repeat(SZEROKOSC_FAKTURY) + "\n";
    poczatek += """
    Data wystawienia:        %s
    Miejsce wystawienia:     %s
    
        """.formatted(
        this.dataWystawienia,
        this.miejsceWystawienia);
    poczatek += "-".repeat(SZEROKOSC_FAKTURY) + "\n";
    poczatek += this.formatujInformacjeSprzedawcyNabywcy();

    // przygotuj napis przedstawiajacy wszystkie elementy faktury, sformatowany w tabele
    StringBuilder produkty = FormatowanieDoWyswietlenia.stworzPierwszyWierszTabeli();
    for (int i = 0; i < elementyFaktury.size(); i++) {
      produkty.append(
          FormatowanieDoWyswietlenia.sformatujElementFaktury(i, elementyFaktury.get(i)));
    }
    produkty.append("-".repeat(SZEROKOSC_FAKTURY)).append("\n");

    // przygotuj sumy kwot wszystkich produktow
    String koniec = FormatowanieDoWyswietlenia.stworzTabeleSum(
        String.valueOf(KontrolerDanych.zaokraglDoDwoch(this.sumaNetto)),
        String.valueOf(KontrolerDanych.zaokraglDoDwoch(this.sumaVat)),
        String.valueOf(KontrolerDanych.zaokraglDoDwoch(this.sumaBrutto)));
    koniec += "-".repeat(SZEROKOSC_FAKTURY);
    return poczatek + produkty + koniec;
  }

  /**
   * Metoda ta tworzy odpowiednio sformatowany lancuch
   * znakow z informacjami o sprzedawcy i nabywcy.
   * -------------------------------------------------------------
   * Zasada Ekspert oraz Niskie sprzezenie:
   * Ze wzgledu na duza ilosc informacji przechowywanych
   * w fakturze, jest ona odpowiedzialna za czesciowe formatowanie.
   *
   * @return Lancuch znakow z informacjami o sprzedawcy i nabywcy.
   * @see FormatowanieDoWyswietlenia#ulozDwaNapisy
   */
  private String formatujInformacjeSprzedawcyNabywcy() {
    String napis = """
    Sprzedawca                            Nabywca
        """;
    napis += FormatowanieDoWyswietlenia.ulozDwaNapisy(this.nazwaSprzedawcy,
        this.nazwaNabywcy,
        ODLEGLOSC_NAPIS_NABYWCA) + "\n";
    napis += FormatowanieDoWyswietlenia.ulozDwaNapisy(this.nipSprzedawcy,
        this.nipNabywcy,
        ODLEGLOSC_NAPIS_NABYWCA) + "\n";
    napis += FormatowanieDoWyswietlenia.ulozDwaNapisy(this.ulicaSprzedawcy,
        this.ulicaNabywcy,
        ODLEGLOSC_NAPIS_NABYWCA) + "\n";
    napis += FormatowanieDoWyswietlenia.ulozDwaNapisy(this.kodPocztowyMiastoSprzedawcy,
        this.kodPocztowyMiastoNabywcy,
        ODLEGLOSC_NAPIS_NABYWCA) + "\n";
    napis += "-".repeat(SZEROKOSC_FAKTURY) + "\n";
    return napis;
  }

}
