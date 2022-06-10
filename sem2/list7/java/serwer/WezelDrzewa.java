/**
 * Klasa reprezentujaca strukture pojedynczego wezla drzewa binarnego.
*/
class WezelDrzewa<T> {
    public WezelDrzewa ojciec;
    public WezelDrzewa lewy;
    public WezelDrzewa prawy;
    public T wartosc;

    public WezelDrzewa() {
        this.ojciec = null;
        this.lewy = null;
        this.prawy = null;
        this.wartosc = null;
    }

    public WezelDrzewa(WezelDrzewa<?> wezel) throws ClassCastException {
        this.ojciec = wezel.ojciec;
        this.lewy = wezel.lewy;
        this.prawy = wezel.prawy;
        this.wartosc = (T)wezel.wartosc;
    }

}
