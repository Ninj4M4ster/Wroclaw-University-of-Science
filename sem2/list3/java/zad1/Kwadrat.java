package sem2.list3.java.zad1;

public class Kwadrat extends Czworokat {

    public Kwadrat(double bok1, double bok2, double bok3, double bok4, double kat) {
        super(bok1, bok2, bok3, bok4, kat);
    }

    public double pole() {
        return _bok1 * _bok1;
    }
}