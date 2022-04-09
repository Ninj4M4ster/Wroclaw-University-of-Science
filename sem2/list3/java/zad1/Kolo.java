package sem2.list3.java.zad1;
import static java.lang.Math.*;

public class Kolo implements Figura {
    protected double _promien;

    public Kolo(double promien) {
        _promien = promien;
    }

    public double obwod() {
        return PI * 2 * _promien;
    }
    
    public double pole() {
        return PI * _promien * _promien;
    }
}