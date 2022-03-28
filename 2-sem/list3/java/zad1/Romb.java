package list3;
import static java.lang.Math.*;

public class Romb extends Czworokat {

    public Romb(double bok1, double bok2, double bok3, double bok4, double kat) {
        super(bok1, bok2, bok3, bok4, kat);
        if(kat > 90.0d)
            _kat = 180.0d - kat;
    }

    public double pole() {
        return sin(_kat * PI / 180) * _bok1 * _bok1;
    }
}