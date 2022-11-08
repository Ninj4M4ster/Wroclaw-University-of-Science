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
  private ArrayList<ElementFaktury> elementyFaktury = new ArrayList<>();

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
}
