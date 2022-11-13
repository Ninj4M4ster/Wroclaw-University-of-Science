import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.Scanner;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;

/**
 * Test klasy WczytDanych.
 *
 * @see WczytDanych
 */
public class TestWczytDanych {

  /**
   * Test metody wprowadzNapis.
   * 
   * @see WczytDanych#wprowadzNapis
   */
  @Test
  public void testWprowadzNapis() {
    ByteArrayInputStream wejscie = new ByteArrayInputStream("abc".getBytes());
    System.setIn(wejscie);
    Scanner scanner = new Scanner(System.in);
    assertEquals(WczytDanych.wprowadzNapis("", scanner), "abc");

    wejscie = new ByteArrayInputStream("\n6".getBytes());
    System.setIn(wejscie);
    scanner = new Scanner(System.in);

    String komunikat = "Nie wprowadzono danych.";
    ByteArrayOutputStream wyjscie = new ByteArrayOutputStream();
    PrintStream strumienWyjscia = new PrintStream(wyjscie);
    System.setOut(strumienWyjscia);

    WczytDanych.wprowadzNapis("a", scanner);

    String[] linie = wyjscie.toString().split("\n");
    String wynik = linie[1];
    assertEquals(wynik, komunikat);
  }

  /**
   * Test metody wprowadzIloscElementu
   *
   * @see WczytDanych#wprowadzIloscElementu
   */
  @Test
  public void testWprowadzIloscElementu() {
    ByteArrayInputStream wejscie = new ByteArrayInputStream("5".getBytes());
    System.setIn(wejscie);
    Scanner scanner = new Scanner(System.in);
    assertEquals(WczytDanych.wprowadzIloscElementu(scanner), 5);

    wejscie = new ByteArrayInputStream("s\n6".getBytes());
    System.setIn(wejscie);
    scanner = new Scanner(System.in);

    String komunikat = "Wprowadzono nieprawidlowe dane.";
    ByteArrayOutputStream wyjscie = new ByteArrayOutputStream();
    PrintStream strumienWyjscia = new PrintStream(wyjscie);
    System.setOut(strumienWyjscia);

    WczytDanych.wprowadzIloscElementu(scanner);

    String[] linie = wyjscie.toString().split("\n");
    String wynik = linie[1];
    assertEquals(wynik, komunikat);
  }

  /**
   * Test metody wprowadzCeneElementu.
   *
   * @see WczytDanych#wprowadzCeneElementu
   */
  @Test
  public void testWprowadzCeneElementu() {
    ByteArrayInputStream wejscie = new ByteArrayInputStream("5".getBytes());
    System.setIn(wejscie);
    Scanner scanner = new Scanner(System.in);
    assertEquals(WczytDanych.wprowadzCeneElementu(scanner), 5);

    wejscie = new ByteArrayInputStream("s\n6".getBytes());
    System.setIn(wejscie);
    scanner = new Scanner(System.in);

    String komunikat = "Wprowadzono nieprawidlowe dane.";
    ByteArrayOutputStream wyjscie = new ByteArrayOutputStream();
    PrintStream strumienWyjscia = new PrintStream(wyjscie);
    System.setOut(strumienWyjscia);

    WczytDanych.wprowadzCeneElementu(scanner);

    String[] linie = wyjscie.toString().split("\n");
    String wynik = linie[1];
    assertEquals(wynik, komunikat);
  }

  /**
   * Test metody wprowadzPodatek.
   *
   * @see WczytDanych#wprowadzPodatek
   */
  @Test
  public void testWprowadzPodatek() {
    ByteArrayInputStream wejscie = new ByteArrayInputStream("5".getBytes());
    System.setIn(wejscie);
    Scanner scanner = new Scanner(System.in);
    assertEquals(WczytDanych.wprowadzPodatek(scanner), 5);

    wejscie = new ByteArrayInputStream("121\n6".getBytes());
    System.setIn(wejscie);
    scanner = new Scanner(System.in);

    String komunikat = "Wprowadzono nieprawidlowe dane.";
    ByteArrayOutputStream wyjscie = new ByteArrayOutputStream();
    PrintStream strumienWyjscia = new PrintStream(wyjscie);
    System.setOut(strumienWyjscia);

    WczytDanych.wprowadzPodatek(scanner);

    String[] linie = wyjscie.toString().split("\n");
    String wynik = linie[1];
    assertEquals(wynik, komunikat);
  }

  /**
   * Test metody wczytajDopuszczalna.
   *
   * @see WczytDanych#wczytajDopuszczalna
   */
  @Test
  public void testWczytajDopuszczalna() {
    String[] dopuszczalneZnaki = {"a", "b"};
    ByteArrayInputStream wejscie = new ByteArrayInputStream("a".getBytes());
    System.setIn(wejscie);
    Scanner scanner = new Scanner(System.in);
    assertEquals(WczytDanych.wczytajDopuszczalna(dopuszczalneZnaki, "", scanner), "a");

    wejscie = new ByteArrayInputStream("b".getBytes());
    System.setIn(wejscie);
    scanner = new Scanner(System.in);
    assertEquals("b", WczytDanych.wczytajDopuszczalna(dopuszczalneZnaki, "", scanner));

    wejscie = new ByteArrayInputStream("c\nb".getBytes());
    System.setIn(wejscie);
    scanner = new Scanner(System.in);

    String komunikat = "Dokonano nieprawidlowego wyboru.";
    ByteArrayOutputStream wyjscie = new ByteArrayOutputStream();
    PrintStream strumienWyjscia = new PrintStream(wyjscie);
    System.setOut(strumienWyjscia);

    WczytDanych.wczytajDopuszczalna(dopuszczalneZnaki, "komunikat", scanner);

    String[] linie = wyjscie.toString().split("\n");
    String wynik = linie[1];
    assertEquals(wynik, komunikat);
  }
}
