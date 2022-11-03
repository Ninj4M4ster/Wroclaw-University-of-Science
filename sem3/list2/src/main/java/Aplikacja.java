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
        System.out.print("""
            Wybierz porzadana czynnosc:
             1 -> utworzenie nowej faktury
             2 -> edycja faktury
             3 -> koniec dzialania programu
             ->:\s""");
      } else {
        System.out.print("""
            Wybierz porzadana czynnosc:
             1 -> utworzenie nowej faktury
             2 -> koniec dzialania programu
             ->:\s""");
      }
      wybor = Integer.parseInt(scanner.nextLine());
      if (wybor == 1) {
        kontrolerFaktur.utworzNowaFakture();
      }
      if (kontrolerFaktur.czyIstniejaUtworzoneFaktury()) {
        if (wybor == 2) {
          // TODO: dodac funkcjonalnosc edycji faktur
        } else if (wybor == 3) {
          break;
        }
      } else if (wybor == 2) {
        break;
      } else {
        System.out.println("Dokonano nieprawidlowego wyboru.\n");
      }
    }
  }
}
