/**
 * Klasa implementujaca torus - dwukierunkowa dwuwymiarowa zapetlona liste.
*/
class ListaDwukierunkowa {

    private ElementListy glowa = null;

    /**
     * Pusty konstruktor.
     */
    ListaDwukierunkowa() {}

    /**
     * Funkcja odpowiedzialna za dodanie do listy nowego elementu.
     * 
     * @see ElementListy
     * @see ElementListy#ustawNastepnyPoziomo
     * @see ElementListy#ustawPoprzedniPoziomo
     * @see ElementListy#ustawNastepnyPionowo
     * @see ElementListy#ustawPoprzedniPionowo
     * @see ElementListy#nastepnyPoziomo
     * @see ElementListy#poprzedniPoziomo
     * @see ElementListy#nastepnyPionowo
     * @see ElementListy#poprzedniPionowo
     * @param nowy_obiekt Pole aplikacji.
     * @param poziomo Czy nowy obiekt ma zostac dodany poziomo?
     */
    public void dodaj(PoleAplikacji nowy_obiekt, boolean poziomo) {
        // pierwszy element listy
        if(glowa == null) {
            glowa = new ElementListy(nowy_obiekt);
            glowa.ustawNastepnyPoziomo(glowa);
            glowa.ustawPoprzedniPoziomo(glowa);
            glowa.ustawNastepnyPionowo(glowa);
            glowa.ustawPoprzedniPionowo(glowa);
        }
        else {
            // dodaj element poziomo do listy
            if(poziomo) {
                ElementListy zmienna_pomocnicza_pozioma = glowa.nastepnyPionowo();
                ElementListy nowy_element = new ElementListy(nowy_obiekt);
                while(zmienna_pomocnicza_pozioma.nastepnyPionowo() != glowa) {
                    zmienna_pomocnicza_pozioma = zmienna_pomocnicza_pozioma.nastepnyPionowo();
                }
                ElementListy pierwszy_element_w_rzedzie = zmienna_pomocnicza_pozioma;
                while(zmienna_pomocnicza_pozioma.nastepnyPoziomo() != pierwszy_element_w_rzedzie) {
                    zmienna_pomocnicza_pozioma = zmienna_pomocnicza_pozioma.nastepnyPoziomo();
                }
                // aktualizacja listy w poziomie
                zmienna_pomocnicza_pozioma.ustawNastepnyPoziomo(nowy_element);
                nowy_element.ustawNastepnyPoziomo(pierwszy_element_w_rzedzie);
                nowy_element.ustawPoprzedniPoziomo(zmienna_pomocnicza_pozioma);
                pierwszy_element_w_rzedzie.ustawPoprzedniPoziomo(nowy_element);
                // sprawdz czy lista nie ma tylko jednego szeregu poziomego
                if(zmienna_pomocnicza_pozioma.poprzedniPionowo() == zmienna_pomocnicza_pozioma) {
                    nowy_element.ustawNastepnyPionowo(nowy_element);
                    nowy_element.ustawPoprzedniPionowo(nowy_element);
                }
                else {
                    ElementListy zmienna_pomocnicza_pionowa = zmienna_pomocnicza_pozioma.poprzedniPionowo();
                    while(zmienna_pomocnicza_pionowa.poprzedniPionowo() != zmienna_pomocnicza_pozioma) {
                        zmienna_pomocnicza_pionowa = zmienna_pomocnicza_pionowa.poprzedniPionowo();
                    }
                    // aktualizacja zapetlenia listy w pionie
                    zmienna_pomocnicza_pionowa = zmienna_pomocnicza_pionowa.nastepnyPoziomo();
                    zmienna_pomocnicza_pionowa.ustawPoprzedniPionowo(nowy_element);
                    nowy_element.ustawNastepnyPionowo(zmienna_pomocnicza_pionowa);

                    // aktualizacja pobliskich pionowych elementow
                    zmienna_pomocnicza_pionowa = zmienna_pomocnicza_pozioma.poprzedniPionowo().nastepnyPoziomo();
                    zmienna_pomocnicza_pionowa.ustawNastepnyPionowo(nowy_element);
                    nowy_element.ustawPoprzedniPionowo(zmienna_pomocnicza_pionowa);
                }
            }
            // dodaj element pionowo do listy
            else {
                ElementListy zmienna_pomocnicza_pionowa = glowa.nastepnyPionowo();
                ElementListy nowy_element = new ElementListy(nowy_obiekt);
                while(zmienna_pomocnicza_pionowa.nastepnyPionowo() != glowa) {
                    zmienna_pomocnicza_pionowa = zmienna_pomocnicza_pionowa.nastepnyPionowo();
                }
                // aktualizacja pionowa
                zmienna_pomocnicza_pionowa.ustawNastepnyPionowo(nowy_element);
                nowy_element.ustawPoprzedniPionowo(zmienna_pomocnicza_pionowa);
                glowa.ustawPoprzedniPionowo(nowy_element);
                nowy_element.ustawNastepnyPionowo(glowa);

                // aktualizacja pozioma
                nowy_element.ustawNastepnyPoziomo(nowy_element);
                nowy_element.ustawPoprzedniPoziomo(nowy_element);
            }
        }
    }

    /**
     * Metoda zwracajaca glowe (pierwszy element) listy.
     * 
     * @return Pierwszy element listy.
     */
    public ElementListy zwrocGlowe() {
        return this.glowa;
    }

}
