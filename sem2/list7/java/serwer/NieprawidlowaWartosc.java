/**
 * Klasa bledu w przypadku, gdy podana zostanie nieprawidlowa wartosc.
 */
class NieprawidlowaWartosc extends Exception {
    public NieprawidlowaWartosc(String wiadomosc) {
        super(wiadomosc);
    }
}
