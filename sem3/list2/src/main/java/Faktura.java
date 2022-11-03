import java.util.Objects;

/**
 * Klasa reprezentujaca dane na fakturze.
 */
public class Faktura {

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
