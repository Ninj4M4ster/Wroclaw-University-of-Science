package list3;

abstract class Czworokat implements Figura {

    protected double _bok1;
    protected double _bok2;
    protected double _bok3;
    protected double _bok4;
    protected double _kat;

    public Czworokat(double bok1, double bok2, double bok3, double bok4, double kat) {
        _bok1 = bok1;
        _bok2 = bok2;
        _bok3 = bok3;
        _bok4 = bok4;
        _kat = kat;
    }

    public double obwod() {
        return _bok1 + _bok2 + _bok3 + _bok4;
    }
    public abstract double pole();
}