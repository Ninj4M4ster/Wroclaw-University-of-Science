import java.util.Scanner;

/**
 * Główna klasa aplikacji.
 * Odpowiedzialna za uruchomienie aplikacji oraz utworzenie kontrolerów.
 */
public class Aplikacja {

  /**
   * Glowna metoda programu. Tworzy petle dajaca wybor porzadanego dzialania.
   *
   * @param args Argumenty z linii komend.
   */
  public static void main(String[] args) {
    KontrolerFaktur kontrolerFaktur = new KontrolerFaktur();
    Scanner scanner = new Scanner(System.in);
    // petla wyboru dzialania
    int wybor = 0;
    while (wybor != 2) {
      if (kontrolerFaktur.czyIstniejaUtworzoneFaktury()) {
        System.out.println("""
            Wybierz pozzadana czynnosc:
             1 -> utworzenie nowej faktury
             2 -> wyswietl poprzednie faktury
             3 -> koniec dzialania programu
             ->:""");
      } else {
        System.out.println("""
            Wybierz pozadana czynnosc:
             1 -> utworzenie nowej faktury
             2 -> koniec dzialania programu
             ->:\s""");
      }
      String wprowadzonaWartosc = scanner.nextLine();

      // sprawdz czy wprowadzono liczbe
      if (KontrolerDanych.czyLiczbaCalkowita(wprowadzonaWartosc)
          && !wprowadzonaWartosc.isEmpty()) {
        wybor = Integer.parseInt(wprowadzonaWartosc);
      } else {
        System.out.println("Wprowadzono nieprawidlowe dane\n");
        continue;
      }

      // wykonaj akcje zaleznie od wyboru
      if (wybor == 1) {
        System.out.println();
        kontrolerFaktur.utworzNowaFakture();
      }
      if (kontrolerFaktur.czyIstniejaUtworzoneFaktury()) {
        if (wybor == 2) {
          kontrolerFaktur.wyswietlajWczesniejUtworzoneFaktury();
        } else if (wybor == 3) {
          break;
        }
      } else if (!kontrolerFaktur.czyIstniejaUtworzoneFaktury() && wybor == 2) {
        break;
      } else {
        System.out.println("Dokonano nieprawidlowego wyboru.\n");
      }
    }  // end while
    scanner.close();
  }

}
