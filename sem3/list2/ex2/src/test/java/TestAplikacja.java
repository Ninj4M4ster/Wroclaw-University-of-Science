import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.text.DateFormat;
import java.util.Date;
import java.util.Locale;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;

/**
 * Test calej aplikacji.
 *
 * @see Aplikacja
 */
public class TestAplikacja {

  /**
   * Test metody main aplikacji.
   * Testuje ona caly proces tworzenia faktury.
   *
   * @see Aplikacja#main
   */
  @Test
  public void testMain() {
    ByteArrayInputStream wejscie = new ByteArrayInputStream(("""
        1
        miejsce
        nazwa
        nip
        adres
        kod
        nazwa
        nip
        adres
        kod
        y
        nazwa
        2
        3
        4
        n
        3""").getBytes());
    System.setIn(wejscie);

    ByteArrayOutputStream wyjscie = new ByteArrayOutputStream();
    PrintStream strumienWyjscia = new PrintStream(wyjscie);
    System.setOut(strumienWyjscia);

    Aplikacja.main(new String[]{});

    DateFormat df = DateFormat.getDateInstance(DateFormat.SHORT, Locale.FRANCE);
    String dataWystawienia = df.format(new Date());

    String[] linie = wyjscie.toString().split("\n");
    assertEquals("Data wystawienia:        " + dataWystawienia, linie[33]);
    assertEquals(linie[34], "Miejsce wystawienia:     miejsce");
    assertEquals(linie[37], "Sprzedawca                            Nabywca");
    assertEquals(linie[38], "nazwa                                 nazwa");
    assertEquals(linie[39], "nip                                   nip");
    assertEquals(linie[40], "adres                                 adres");
    assertEquals(linie[41], "kod                                   kod");
    assertEquals(linie[43], "Lp  |    Nazwa towaru/uslugi    | ilosc |   Cena jedn.   "
        + "| Wartosc netto | VAT % |  VAT  | Wartosc Brutto");
    assertEquals(linie[44], "1   | nazwa                     | 2     | 2.88           "
        + "| 5.76          | 4.0   | 0.12  | 6.0");
    assertEquals(linie[46], "                                                             "
        + "Razem netto | Razem VAT | Razem brutto");
    assertEquals(linie[47], "                                                              "
        + "5.76       | 0.24      | 6.0");
  }
}
