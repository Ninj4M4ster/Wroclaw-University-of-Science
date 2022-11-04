import java.text.DateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.Objects;

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
}
