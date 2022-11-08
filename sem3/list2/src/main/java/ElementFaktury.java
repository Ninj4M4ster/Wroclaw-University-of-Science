/**
 * Klasa reprezentujaca element faktury.
 */
public class ElementFaktury {
  private String nazwaElementu;
  private int ilosc;
  private double cena;
  private double podatek;

  /**
   * Konstruktor. Tworzy element faktury z wprowadzonymi danymi.
   *
   * @param nazwaElementu Nazwa towaru lub uslugi.
   * @param ilosc Ilosc towaru/uslugi.
   * @param cena Cena za sztuke.
   * @param podatek Podatek od towaru/uslugi.
   */
  public ElementFaktury(String nazwaElementu, int ilosc, double cena, double podatek) {
    this.nazwaElementu = nazwaElementu;
    this.ilosc = ilosc;
    this.cena = cena;
    this.podatek = podatek;
  }
}
