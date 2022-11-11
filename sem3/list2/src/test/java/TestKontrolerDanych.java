import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Test klasy Kontroler Danych.
 */
public class TestKontrolerDanych {

  /**
   * Test metody czyLiczbaCalkowita.
   *
   * @see KontrolerDanych#czyLiczbaCalkowita
   */
  @Test
  public void testCzyLiczbaCalkowita() {
    assertTrue(KontrolerDanych.czyLiczbaCalkowita("5"));
    assertFalse(KontrolerDanych.czyLiczbaCalkowita("j"));
    assertTrue(KontrolerDanych.czyLiczbaCalkowita("25"));
    assertFalse(KontrolerDanych.czyLiczbaCalkowita(""));
  }

  /**
   * Test metody czyLiczbaRzeczywista.
   *
   * @see KontrolerDanych#czyLiczbaRzeczywista
   */
  @Test
  public void testCzyLiczbaRzeczywista() {
    assertTrue(KontrolerDanych.czyLiczbaRzeczywista("6"));
    assertTrue(KontrolerDanych.czyLiczbaRzeczywista("8.2"));
    assertFalse(KontrolerDanych.czyLiczbaRzeczywista("t"));
    assertFalse(KontrolerDanych.czyLiczbaRzeczywista(""));
  }

  /**
   * Test metody czyProcent.
   *
   * @see KontrolerDanych#czyProcent
   */
  @Test
  public void testCzyProcent() {
    assertTrue(KontrolerDanych.czyProcent("25"));
    assertTrue(KontrolerDanych.czyProcent("0"));
    assertTrue(KontrolerDanych.czyProcent("100"));
    assertFalse(KontrolerDanych.czyProcent("101"));
    assertFalse(KontrolerDanych.czyProcent("dfg"));
    assertFalse(KontrolerDanych.czyProcent(""));
  }

  /**
   * Test metody zaokraglDoDwoch.
   *
   * @see KontrolerDanych#zaokraglDoDwoch
   */
  @Test
  public void testZaokraglDoDwoch() {
    assertEquals(6.21, KontrolerDanych.zaokraglDoDwoch(6.2143));
    assertEquals(4.89, KontrolerDanych.zaokraglDoDwoch(4.885));
    assertEquals(2.10, KontrolerDanych.zaokraglDoDwoch(2.102));
  }
}
