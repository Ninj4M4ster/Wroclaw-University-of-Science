package list3;
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
        return (5.0d / 4.0d) * _bok * _bok * (1 /tan(36 * PI / 180));
    }
}