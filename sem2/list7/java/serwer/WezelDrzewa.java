/**
 * Klasa reprezentujaca strukture pojedynczego wezla drzewa binarnego.
*/
class WezelDrzewa<T> {
    public WezelDrzewa ojciec;
    public WezelDrzewa lewy;
    public WezelDrzewa prawy;
    public T wartosc;

    /**
     * Domyslny konstruktor, tworzy pusty wezel.
     */
    public WezelDrzewa() {
        this.ojciec = null;
        this.lewy = null;
        this.prawy = null;
        this.wartosc = null;
    }

    /**
     * Konstruktor, tworzy nowy wezel z wprowadzonej przez klienta wartosci.
     * 
     * @param wezel Wezel zawierajacy wprowadzana wartosci.
     */
    @SuppressWarnings("unchecked")
    public WezelDrzewa(WezelDrzewa<?> wezel) {
        this.ojciec = wezel.ojciec;
        this.lewy = wezel.lewy;
        this.prawy = wezel.prawy;
        this.wartosc = (T)wezel.wartosc;
    }

}
