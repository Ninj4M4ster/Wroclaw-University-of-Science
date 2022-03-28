package list3;
import static java.lang.Math.*;

public class Szesciokat implements Figura {
    protected double _bok;

    public Szesciokat(double bok) {
        _bok = bok;
    }

    public double obwod() {
        return _bok * 6.0d;
    }

    public double pole() {
        return 3.0d * _bok * _bok * sqrt(3) / 4.0d;
    }
}