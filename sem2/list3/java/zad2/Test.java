package sem2.list3.java.zad2;

import java.rmi.ConnectIOException;

public class Test {
    public static void main(String[] args) throws NieprawidloweArgumenty {
        if(args.length == 0)
            System.out.println("Nie wprowadzono argumentow");
        else {
            try {
                if(czyLiczba(args[0]))
                    throw new NieprawidloweArgumenty(args[0] + " - nieprawidlowe dane");
                int potrzebnaIloscArgumentow = obliczPotrzebnaIloscArgumentow(args[0]);
                if(potrzebnaIloscArgumentow + 1 > args.length)
                    throw new NieprawidlowaIloscArgumentow("Wprowadono za malo argumentow");
                else if (potrzebnaIloscArgumentow + 1 < args.length)
                    throw new NieprawidlowaIloscArgumentow("Wprowadzono za duzo argumentow");
                int indeks_argumentow = 1;
                for(char znak : args[0].toCharArray()) {
                    try {
                        Figura figura;
                        if(znak == 'c') {
                            indeks_argumentow += 5;
                            double bok1 = Double.parseDouble(args[indeks_argumentow - 5]);
                            double bok2 = Double.parseDouble(args[indeks_argumentow - 4]);
                            double bok3 = Double.parseDouble(args[indeks_argumentow - 3]);
                            double bok4 = Double.parseDouble(args[indeks_argumentow - 2]);
                            double kat = Double.parseDouble(args[indeks_argumentow - 1]);
                            figura = new Figura(znak, bok1, bok2, bok3, bok4, kat);
                        }
                        else {
                            indeks_argumentow += 1;
                            double bok = Double.parseDouble(args[indeks_argumentow - 1]);
                            figura = new Figura(znak, bok);
                        }
                        String rodzaj_figury = zacznijNapisOdWielkiejLitery(figura.rodzajFigury());
                        System.out.println(rodzaj_figury + " - obwod: " + figura.ObliczObwod());
                        System.out.println(rodzaj_figury + " - pole: " + figura.ObliczPole() + "\n");
                    } catch(NieprawidloweArgumenty e) {
                        System.out.println(e.getMessage());
                    } catch(NumberFormatException e ) {
                        if(znak == 'c') {
                            System.out.println(args[indeks_argumentow - 5] + ", " + args[indeks_argumentow - 4] 
                            + ", " + args[indeks_argumentow - 3] + ", " + args[indeks_argumentow - 2] + ", " 
                            + args[indeks_argumentow - 1] + " - wprowadzono nieprawidlowe dane");    
                        }
                        else {
                            System.out.println(args[indeks_argumentow - 1] + " - wprowadzono nieprawidlowa dane");
                        }
                    }
                }
            } catch(NieprawidlowaIloscArgumentow e) {
                System.out.println(e.getMessage());
            } catch(NieprawidloweArgumenty e) {
                System.out.println(e.getMessage());
            }
        }
    }

    private static Boolean czyLiczba(String napis) {
        try {
            Double.parseDouble(napis);
            return true;
        } catch(NumberFormatException e) {
            return false;
        }
    }

    private static String zacznijNapisOdWielkiejLitery(String napis) {
        if(napis == null || napis.isEmpty())
            return "";
        return napis.substring(0, 1).toUpperCase() + napis.substring(1);
    }

    private static int obliczPotrzebnaIloscArgumentow(String figury) {
        int potrzebnaIlosc = 0;
        for(char znak : figury.toCharArray()) {
            if(znak == 'c')
                potrzebnaIlosc += 5;
            else
                potrzebnaIlosc += 1;
        }
        return potrzebnaIlosc;
    }
}
