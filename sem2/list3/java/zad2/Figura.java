package sem2.list3.java.zad2;

public class Figura {
    private String figura;
    private double argument1;
    private double argument2;

    public Figura(char znak_figury, double argument1) throws NieprawidloweArgumenty {
        switch(znak_figury) {
            case 'o': {
                if(argument1 <= 0.0)
                    throw new NieprawidloweArgumenty(argument1 + " - wprowadzono nieprawidlowa dlugosc promienia");
                this.figura = "kolo";
                this.argument1 = argument1;
                break;
            } case 'p': {
                if(argument1 <= 0.0)
                    throw new NieprawidloweArgumenty(argument1 + " - wprowadzono nieprawidlowa dlugosc boku pieciokata");
                this.figura = "pieciokat";
                this.argument1 = argument1;
                break;
            } case 's': {
                if(argument1 <= 0.0)
                    throw new NieprawidloweArgumenty(argument1 + " - wprowadzono nieprawidlowa dlugosc boku szesciokata");
                this.figura = "szesciokat";
                this.argument1 = argument1;
                break;
            } default:
                throw new NieprawidloweArgumenty(znak_figury + " - nie ma takiej figury");
        }
    }

    public Figura(char znak_figury, double bok1, double bok2, double bok3, double bok4, double kat) throws NieprawidloweArgumenty{
        if(znak_figury != 'c')
            throw new NieprawidloweArgumenty(znak_figury + " - nie ma takiej figury");
        if(bok1 < 0.0 || bok2 <= 0.0 || bok3 <= 0.0 || bok4 <= 0.0)
            throw new NieprawidloweArgumenty(bok1 + ", " + bok2 + ", " + bok3 + ", " + bok4 + " - dlugosci bokow czworokata musza miec wartosci wieksze od zera");
        if(kat < 0.0 || kat > 180.0)
            throw new NieprawidloweArgumenty(kat + " - wprowadzono nieprawidlowy kat");
        if(kat == 90.0) {
            if(bok1 == bok2 && bok2 == bok3 && bok3 == bok4) {
                this.figura = "kwadrat";
                this.argument1 = bok1;
            }
            else if(bok1 == bok2 && bok3 == bok4) {
                this.figura = "prostokat";
                this.argument1 = bok1;
                this.argument2 = bok3;
            }
            else
                throw new NieprawidloweArgumenty(bok1 + ", " + bok2 + ", " + bok3 + ", " + bok4 + " - wprowadzono nieprawidlowe dlugosci bokow czworokata");
        }
        else {
            if(bok1 == bok2 && bok2 == bok3 && bok3 == bok4) {
                this.figura = "romb";
                this.argument1 = bok1;
                this.argument2 = kat;
            }
            else
                throw new NieprawidloweArgumenty(bok1 + ", " + bok2 + ", " + bok3 + ", " + bok4 + ", " + kat + " - wprowadzono nieprawidlowe dlugosci bokow czworokata");
        }
    }

    public double ObliczObwod() throws NieprawidloweArgumenty {
        switch(this.figura) {
            case("kwadrat"): 
                return JedenArgument.KWADRAT.ObliczObwod(this.argument1);
            case("prostokat"):
                return DwaArgumenty.PROSTOKAT.ObliczObwod(this.argument1, this.argument2);
            case("romb"):
                return DwaArgumenty.ROMB.ObliczObwod(this.argument1, this.argument2);
            case("kolo"):
                return JedenArgument.KOLO.ObliczObwod(this.argument1);
            case("pieciokat"):
                return JedenArgument.PIECIOKAT.ObliczObwod(this.argument1);
            case("szesciokat"):
                return JedenArgument.SZESCIOKAT.ObliczObwod(this.argument1);
            default:
                throw new NieprawidloweArgumenty(this.figura + " - nie zaimplementowano tej figury");
        }
    }

    public double ObliczPole() throws NieprawidloweArgumenty {
        switch(this.figura) {
            case("kwadrat"):
                return JedenArgument.KWADRAT.ObliczPole(this.argument1);
            case("prostokat"):
                return DwaArgumenty.PROSTOKAT.ObliczPole(this.argument1, this.argument2);
            case("romb"):
                return DwaArgumenty.ROMB.ObliczPole(this.argument1, this.argument2);
            case("kolo"):
                return JedenArgument.KOLO.ObliczPole(this.argument1);
            case("pieciokat"):
                return JedenArgument.PIECIOKAT.ObliczPole(this.argument1);
            case("szesciokat"):
                return JedenArgument.SZESCIOKAT.ObliczPole(this.argument1);
            default:
                throw new NieprawidloweArgumenty(this.figura + " - nie zaimplementowano tej figury");
        }
    }

    public String rodzajFigury() {
        return this.figura;
    }

    private enum JedenArgument implements FiguraJednoArgumentowa {
        KOLO {
            @Override
            public double ObliczObwod(double argument) {
                return Math.PI * 2 * argument;
            }
            public double ObliczPole(double argument) {
                return Math.PI * argument * argument;
            }
        }, KWADRAT {
            @Override
            public double ObliczObwod(double argument) {
                return 4.0 * argument;
            }
            @Override
            public double ObliczPole(double argument) {
                return argument * argument;
            }
        }, PIECIOKAT {
            @Override
            public double ObliczObwod(double argument) {
                return 5.0 * argument;
            }
            @Override
            public double ObliczPole(double argument) {
                return (5.0d / 4.0d) * argument * argument * (1.0 /Math.tan(36.0 * Math.PI / 180.0));
            }
        }, SZESCIOKAT {
            @Override
            public double ObliczObwod(double argument) {
                return 6.0 * argument;
            }
            @Override
            public double ObliczPole(double argument) {
                return 3.0d * argument * argument * Math.sqrt(3) / 4.0d;
            }
        };
    }

    private enum DwaArgumenty implements FiguraDwuargumentowa {
        PROSTOKAT {
            @Override
            public double ObliczPole(double argument1, double argument2) {
                return argument1 * argument2;
            }
            @Override
            public double ObliczObwod(double argument1, double argument2) {
                return (argument1 * 2) + (argument2 * 2);
            }
        }, ROMB {
            @Override
            public double ObliczObwod(double argument1, double argument2) {
                return argument1 * 4.0;
            }
            @Override
            public double ObliczPole(double argument1, double argument2) {
                if(argument2 > 90.0)
                    argument2 = 180.0 - argument2;
                return Math.sin(argument2 * Math.PI / 180) * argument1 * argument1;
            }
        };
    }

    private interface FiguraJednoArgumentowa {
        public double ObliczPole(double argument);
        public double ObliczObwod(double argument);
    }
    
    private interface FiguraDwuargumentowa {
        public double ObliczObwod(double argument1, double argument2);
        public double ObliczPole(double argument1, double argument2);
    }
}
