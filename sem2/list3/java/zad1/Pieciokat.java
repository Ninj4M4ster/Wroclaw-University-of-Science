package sem2.list3.java.zad1;
import static java.lang.Math.*;

public class Pieciokat implements Figura {
    protected double _bok;

    public Pieciokat(double bok) {
        _bok = bok;
    }

    public double obwod() {
        return _bok * 5.0d;
    }

    public double pole() {
        return (5.0d / 4.0d) * _bok * _bok * (1.0 /tan(36.0 * PI / 180.0));
    }
}