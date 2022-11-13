import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
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

    String[] linie = wyjscie.toString().split("\n");
    assertEquals(linie[31], "Data wystawienia:        12/11/2022");
    assertEquals(linie[32], "Miejsce wystawienia:     miejsce");
    assertEquals(linie[35], "Sprzedawca                            Nabywca");
    assertEquals(linie[36], "nazwa                                 nazwa");
    assertEquals(linie[37], "nip                                   nip");
    assertEquals(linie[38], "adres                                 adres");
    assertEquals(linie[39], "kod                                   kod");
    assertEquals(linie[41], "Lp  |    Nazwa towaru/uslugi    | ilosc |   Cena jedn.   "
        + "| Wartosc netto | VAT % |  VAT  | Wartosc Brutto");
    assertEquals(linie[42], "1   | nazwa                     | 2     | 2.88           "
        + "| 5.76          | 4.0   | 0.12  | 6.0");
    assertEquals(linie[44], "                                                             "
        + "Razem netto | Razem VAT | Razem brutto");
    assertEquals(linie[45], "                                                              "
        + "5.76       | 0.24      | 6.0");
  }
}
