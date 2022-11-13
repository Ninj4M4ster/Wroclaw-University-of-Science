/**
 * Klasa reprezentujaca element faktury.
 */
public class ElementFaktury {
  private final String nazwaElementu;
  private final int ilosc;
  private final double cenaBrutto;
  private final double cenaNetto;
  private final double podatek;

  /**
   * Konstruktor. Tworzy element faktury z wprowadzonymi danymi.
   *
   * @param nazwaElementu Nazwa towaru lub uslugi.
   * @param ilosc Ilosc towaru/uslugi.
   * @param cena Cena brutto za sztuke.
   * @param podatek Podatek od towaru/uslugi.
   * @see KontrolerDanych#zaokraglDoDwoch
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

  /**
   * Nadpisana metoda toString.
   * Jej celem jest utworzenie sformatowanego ciagu danych o
   * elemencie faktury oddzielonych za pomoca znakow ';;'.
   *
   * @return Ciag znakow zawierajacy informacje o elemencie faktury.
   * @see KontrolerDanych#zaokraglDoDwoch
   */
  @Override
  public String toString() {
    return this.nazwaElementu + ";;" + this.ilosc + ";;"
        + KontrolerDanych.zaokraglDoDwoch(this.cenaNetto) + ";;"
        + KontrolerDanych.zaokraglDoDwoch(this.cenaNetto * this.ilosc)
        + ";;" + this.podatek + ";;"
        + KontrolerDanych.zaokraglDoDwoch(this.cenaBrutto - this.cenaNetto) + ";;"
        + KontrolerDanych.zaokraglDoDwoch(this.cenaBrutto * this.ilosc);
  }
}
