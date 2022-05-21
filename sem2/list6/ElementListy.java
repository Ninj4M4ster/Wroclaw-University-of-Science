/**
 * Klasa implementujaca poszczegolny element torusu - dwukierunkowej, dwuwymiarowej, zapetlonej listy.
 */
final class ElementListy {    
    // wskazniki na pobliskie elementy listy
    private ElementListy nastepny_poziomo = null;
    private ElementListy poprzedni_poziomo = null;
    private ElementListy nastepny_pionowo = null;
    private ElementListy poprzedni_pionowo = null;

    // zmienna przechowujaca pole aplikacji odpowiadajace elementowi listy
    private PoleAplikacji watek;

    /**
     * Konstruktor, tworzy element przechowujacy pole aplikacji.
     * 
     * @see PoleAplikacji#przekazElementListy
     * @param obiekt Watek pola aplikacji.
     */
    ElementListy(PoleAplikacji obiekt) {
        this.watek = obiekt; 
        obiekt.przekazElementListy(this);
    }

    /**
     * Metoda zwracajaca nastepny element listy w poziomie.
     * 
     * @return Element listy.
     */
    ElementListy nastepnyPoziomo() {
        return this.nastepny_poziomo;
    }

    /**
     * Metoda zwracajaca nastepny element listy w pionie.
     * 
     * @return Element listy.
     */
    ElementListy nastepnyPionowo() {
        return this.nastepny_pionowo;
    }

    /**
     * Metoda zwracajaca poprzedni element listy w poziomie.
     * 
     * @return Element listy.
     */
    ElementListy poprzedniPoziomo() {
        return this.poprzedni_poziomo;
    }

    /**
     * Metoda zwracajaca poprzedni element listy w pionie.
     * 
     * @return Element listy.
     */
    ElementListy poprzedniPionowo() {
        return this.poprzedni_pionowo;
    }

    /**
     * Metoda ustawiajaca kolejny element listy w poziomie.
     * 
     * @param element Inny element listy.
     */
    void ustawNastepnyPoziomo(ElementListy element) {
        this.nastepny_poziomo = element;
    }

    /**
     * Metoda ustawiajaca poprzedni element listy w pionie.
     * 
     * @param element Inny element listy.
     */
    void ustawNastepnyPionowo(ElementListy element) {
        this.nastepny_pionowo = element;
    }

    /**
     * Metoda ustawiajaca poprzedni element listy w pionie.
     * 
     * @param element Inny element listy.
     */
    void ustawPoprzedniPionowo(ElementListy element) {
        this.poprzedni_pionowo = element;
    }

    /**
     * Metoda ustawiajaca poprzedni element listy w poziomie.
     * 
     * @param element Inny element listy.
     */
    void ustawPoprzedniPoziomo(ElementListy element) {
        this.poprzedni_poziomo = element;
    }

    /**
     * Metoda zwracajaca pole aplikacji przechowywane przez element, na ktorym jest wywolywana.
     * 
     * @return Pole aplikacji.
     */
    PoleAplikacji podajWatek() {
        return this.watek;
    }


}