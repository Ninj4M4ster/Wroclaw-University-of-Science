/**
 * Klasa reprezentujaca element faktury.
 */
public class ElementFaktury {
  private String nazwaElementu;
  private int ilosc;
  private double cenaBrutto;
  private double cenaNetto;
  private double podatek;

  /**
   * Konstruktor. Tworzy element faktury z wprowadzonymi danymi.
   *
   * @param nazwaElementu Nazwa towaru lub uslugi.
   * @param ilosc Ilosc towaru/uslugi.
   * @param cena Cena brutto za sztuke.
   * @param podatek Podatek od towaru/uslugi.
   */
  public ElementFaktury(String nazwaElementu, int ilosc, double cena, double podatek) {
    this.nazwaElementu = nazwaElementu;
    this.ilosc = ilosc;
    this.cenaBrutto = cena;
    this.podatek = podatek;
    this.cenaNetto = KontrolerDanych.zaokraglDoDwoch(cena * 100.0 / (100.0 + podatek));
  }

  /**
   * Metoda ta zwraca ilosc wprowadzona do tego elementu.
   *
   * @return Ilosc towaru/uslugi.
   */
  public int dajIlosc() {
    return this.ilosc;
  }

  /**
   * Metoda ta zwraca kwote brutto za jedna sztuke towaru podanego do tego elementu.
   *
   * @return Cena brutto za sztuke.
   */
  public double dajBrutto() {
    return this.cenaBrutto;
  }

  /**
   * Metoda ta zwraca kwote netto za jedna sztuke towaru podanego do tego elementu.
   *
   * @return Cena netto za sztuke.
   */
  public double dajNetto() {
    return this.cenaNetto;
  }

  @Override
  public String toString() {
    return this.nazwaElementu + ";;" + this.ilosc + ";;" + this.cenaNetto + ";;"
        + KontrolerDanych.zaokraglDoDwoch(this.cenaNetto * this.ilosc)
        + ";;" + this.podatek + ";;"
        + KontrolerDanych.zaokraglDoDwoch(this.cenaBrutto - this.cenaNetto) + ";;"
        + KontrolerDanych.zaokraglDoDwoch(this.cenaBrutto * this.ilosc);
  }
}
