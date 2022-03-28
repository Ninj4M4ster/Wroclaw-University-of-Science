package list3;

public class Test {
    public static void main(String[] argv) {
        if(argv.length > 0) {
            try {
                String figury = argv[0];
                if(czyLiczba(figury))
                    System.out.println(figury + " - wprowadzono nieprawidlowe dane");
                else {
                    int potrzebnaIloscArgumentow = 0;
                    for(int i = 0 ; i < figury.length(); i++) {
                        switch(figury.charAt(i)) {
                            case 'o':
                                potrzebnaIloscArgumentow += 1;
                                break;
                            case 'p':
                                potrzebnaIloscArgumentow += 1;
                                break;
                            case 's':
                                potrzebnaIloscArgumentow += 1;
                                break;
                            case 'c':
                                potrzebnaIloscArgumentow += 5;
                                break;
                            default:
                                System.out.println(figury.charAt(i) + " - nieprawidlowa figura");
                                break;
                        }
                    }
                    if(potrzebnaIloscArgumentow + 1 != argv.length)
                        throw new ZaMaloArgumentow("Wprowadzono niepoprawna ilosc argumentow");
                    int j = 1;
                    for(int i = 0; i < figury.length(); i++) {
                        try {
                            if(figury.charAt(i) == 'c') {
                                if(!czyLiczba(argv[j]) || !czyLiczba(argv[j+1]) || 
                                                    !czyLiczba(argv[j+2]) || !czyLiczba(argv[j+3]) || !czyLiczba(argv[j+4])) {
                                    j += 5;
                                    throw new NieprawidloweArgumenty(argv[j-5] + ", " + argv[j-4] + ", " + argv[j-3] + 
                                                                    ", " + argv[j-2] + ", " + argv[j-1] + " - nieprawidlowe dane");
                                }
                                double bok1 = Double.parseDouble(argv[j]);
                                double bok2 = Double.parseDouble(argv[j+1]);
                                double bok3 = Double.parseDouble(argv[j+2]);
                                double bok4 = Double.parseDouble(argv[j+3]);
                                double kat = Double.parseDouble(argv[j+4]);
                                j += 5;
                                if(bok1 <= 0 || bok2 <= 0 || bok3 <= 0 || bok4 <= 0)
                                    throw new NieprawidloweArgumenty(bok1 + ", " + bok2 + ", " + bok3 + ", " + bok4 + " - boki czworokatow musza miec wartosci wieksze od zera");
                                if(kat == 90.0d) {
                                    if(bok1 == bok2 && bok2 == bok3 && bok3 == bok4) {
                                        Kwadrat kwadrat = new Kwadrat(bok1, bok2, bok3, bok4, kat);
                                        System.out.println("Obwod kwadratu: " + kwadrat.obwod());
                                        System.out.println("Pole kwadratu: " + kwadrat.pole());
                                        System.out.println();
                                    }
                                    else if(bok1 == bok2 && bok3 == bok4) {
                                        Prostokat prostokat = new Prostokat(bok1, bok2, bok3, bok4, kat);
                                        System.out.println("Obwod prostokata: " + prostokat.obwod());
                                        System.out.println("Pole prostokata: " + prostokat.pole());
                                        System.out.println();
                                    }
                                } else if(kat > 0.0d && kat < 180.0d && (bok1 == bok2 && bok2 == bok3 && bok3 == bok4)) {
                                    Romb romb = new Romb(bok1, bok2, bok3, bok4, kat);
                                    System.out.println("Obwod rombu: " + romb.obwod());
                                    System.out.println("Pole rombu: " + romb.pole());
                                    System.out.println();
                                }
                                else {
                                    throw new NieprawidloweArgumenty(bok1 + ", " + bok2 + ", " + bok3 + ", " + bok4 + ", " + kat + " - argumenty nie pasuja do zadnego czworokatu");
                                }
                            } else if(figury.charAt(i) == 'o') {
                                if(!czyLiczba(argv[j])) {
                                    j += 1;
                                    throw new NieprawidloweArgumenty(argv[j-1] + " - nieprawidlowa dana");
                                }
                                double bok = Double.parseDouble(argv[j]);
                                j += 1;
                                if(bok < 0)
                                    throw new NieprawidloweArgumenty(bok + " - promien kola musi miec wartosc wieksza od zera");
                                Kolo kolo = new Kolo(bok);
                                System.out.println("Obwod kola: " + kolo.obwod());
                                System.out.println("Pole kola: " + kolo.pole());
                                System.out.println();

                            } else if(figury.charAt(i) == 'p') {
                                if(!czyLiczba(argv[j])) {
                                    j += 1;
                                    throw new NieprawidloweArgumenty(argv[j-1] + " - nieprawidlowa dana");
                                }
                                double bok = Double.parseDouble(argv[j]);
                                j += 1;
                                if(bok <= 0)
                                    throw new NieprawidloweArgumenty(bok + " - bok pieciokata musi miec wartosc wieksza od zera");
                                Pieciokat pieciokat = new Pieciokat(bok);
                                System.out.println("Obwod pieciokata: " + pieciokat.obwod());
                                System.out.println("Pole pieciokata: " + pieciokat.pole());
                                System.out.println();
                            } else if(figury.charAt(i) == 's') {
                                if(!czyLiczba(argv[j])) {
                                    j += 1;
                                    throw new NieprawidloweArgumenty(argv[j-1] + " - nieprawidlowa dana");
                                }
                                double bok = Double.parseDouble(argv[j]);
                                j += 1;
                                if(bok <= 0)
                                    throw new NieprawidloweArgumenty(bok + " - bok szesciokata musi miec wartosc wieksza od zera");
                                Szesciokat szesciokat = new Szesciokat(bok);
                                System.out.println("Obwod pieciokata: " + szesciokat.obwod());
                                System.out.println("Pole szesciokata: " + szesciokat.pole());
                                System.out.println();
                            }
                        } catch(NieprawidloweArgumenty e) {
                            System.out.println(e.getMessage());
                        } 
                    }
                }
            } catch(ZaMaloArgumentow e) {
                System.out.println(e.getMessage());
            }
        }
        else {
            System.out.println("Nie wprowadzono argumentow");
        }
    } 

    public static Boolean czyLiczba(String napis) {
        if(napis == null)
            return false;
        try {
            double wartosc = Double.parseDouble(napis);
        }
        catch(NumberFormatException e) {
            return false;
        }
        return true;
    }
}