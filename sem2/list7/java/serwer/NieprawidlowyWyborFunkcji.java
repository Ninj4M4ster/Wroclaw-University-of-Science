/**
 * Klasa bledu w przypadku, gdy wybrana zostanie nieistniejaca funkcja.
 */
class NieprawidlowyWyborFunkcji extends Exception {
    public NieprawidlowyWyborFunkcji(String wiadomosc) {
        super(wiadomosc);
    }
}
