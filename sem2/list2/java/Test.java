package packages;

public class Test {
    public static void main(String[] argv) {
        try {
            int n = Integer.parseInt(argv[0]);
            WierszTrojkataPascala tablica = new WierszTrojkataPascala(n);
            for(int i = 1; i < argv.length; i++) {
                try {
                    System.out.println(argv[i] + " - " + tablica.wspolczynnik(Integer.parseInt(argv[i])));
                }
                catch(ArgumentMniejszyOdZera e) {
                    System.out.println(argv[i] + " - " + e.getMessage());
                }
                catch(ArgumentWiekszyOdArgumentuKonstruktora e) {
                    System.out.println(argv[i] + " - " + e.getMessage());
                }
                catch(NumberFormatException e) {
                    System.out.println(argv[i] + " - nieprawidlowa dana");
                }
            }
        }
        catch(ArgumentMniejszyOdZera e) {
            System.out.println(argv[0] + " - " + e.getMessage());
        }
        catch(ZaDuzyWierszTrojkataPascala e) {
            System.out.println(e.getMessage());
        }
    }
}