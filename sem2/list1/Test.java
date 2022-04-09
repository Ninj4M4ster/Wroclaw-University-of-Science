package list1;

public class Test {
    public static void main(String[] args) {
        try {
            int zakres = Integer.parseInt(args[0]);
            if(zakres > 1) {
                LiczbyPierwsze tablica = new LiczbyPierwsze(zakres);
                for(int i=1; i < args.length; i++) {
                    try {
                        int argument = Integer.parseInt(args[i]);
                        if(argument >= tablica.ilosc || argument < 0) {
                            System.out.println(argument + " - liczba spoza zakresu");
                        } else {
                            System.out.println(argument + " - " + tablica.liczba(argument));
                        }
                    } catch(NumberFormatException e) {
                        System.out.println(args[i] + " - nieprawidlowa dana");
                    }
                }
            }
            else {
                System.out.println(args[0] + " - nieprawdilowy zakres");
            }
        } catch(NumberFormatException e) {
            System.out.println(args[0] + " - nieprawdilowa dana jako zakres");
        } catch(ArrayIndexOutOfBoundsException e) {
            System.out.println("Nie wprowadzono argumentow");
        }
    }
}